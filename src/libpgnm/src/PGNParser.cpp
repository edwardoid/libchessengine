//
// Copyright (C) 2002 Andrea Vinzoni <vinzoni@users.sourceforge.net>
//
//     This file is part of pgnlib.
//
//     pgnlib is free software; you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation; either version 2 of the License, or
//     (at your option) any later version.     
// 
//     pgnlib is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
// 
//     See the GNU General Public License for more details. 
// 
//     You should have received a copy of the GNU General Public License
//     along with pgnlib; if not, write to the Free Software Foundation, 
//     Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
// 

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <stdlib.h>

#include "PGNCommentText.h"
#include "PGNGame.h"
#include "PGNGameCollection.h"
#include "PGNGameResult.h"
#include "PGNMove.h"
#include "PGNMoveList.h"
#include "PGNPiece.h"
#include "PGNPly.h"
#include "PGNSquare.h"
#include "PGNTag.h"
#include "PGNTagList.h"
#include "PGNParser.h"
#include "PGNException.h"

void pgn::Parser::skipBlanks(std::string::const_iterator &itr1)
{
	while (isspace(*itr1)) itr1++;
}

bool pgn::Parser::getGameCollection(std::string::const_iterator &itr1, const std::string::const_iterator &itr2, pgn::GameCollection &out)
{
	std::string::const_iterator local_itr = itr1;

	pgn::Game *game;

	while (game = getGame(local_itr, itr2))
	{
		itr1 = local_itr;
		out.insert(*game);
		delete game;
		gameCount_++;
//		std::cout << "\rgames parsed: " << gameCount_;
//		std::cout.flush();
	}
//	std::cout << std::endl;

	return true;
}

pgn::Game* pgn::Parser::getGame(std::string::const_iterator &itr1, const std::string::const_iterator &itr2)
{
	std::string::const_iterator start_game_itr = itr1;
	std::string::const_iterator local_itr = itr1;

	try
	{
		pgn::TagList taglist;
		if (!getTagList(local_itr, itr2, taglist))
			return 0;

		itr1 = local_itr;

		skipBlanks(local_itr);	
		pgn::CommentText bgComment;
		bool hasBgComment = false;
		if (getComment(local_itr, itr2, bgComment))
		{
			hasBgComment = true;
			itr1 = local_itr;
		}
	
		skipBlanks(local_itr);	
		pgn::MoveList  movelist;
		if (!getMoveList(local_itr, itr2, movelist))
			throw std::runtime_error("Error parsing movelist"); 

		itr1 = local_itr;

		pgn::GameResult gameResult;
		if (!getGameResult(local_itr, itr2, gameResult))
			return 0;

		itr1 = local_itr;

		pgn::Game *g = new pgn::Game(taglist, movelist, gameResult);

		skipBlanks(local_itr);	
		pgn::CommentText agComment;
		bool hasAgComment = false;
		if (getComment(local_itr, itr2, agComment))
		{
			hasAgComment = true;
			itr1 = local_itr;
		}

		if (hasBgComment) g->bindBeforeGameComment(bgComment);
		if (hasAgComment) g->bindAfterGameComment(agComment);
		return g;
	}
	catch (pgn::parse_exception &pe)
	{
		pe.bindParsingText(std::string(start_game_itr, local_itr));
		throw;
	}
	catch (std::exception &e)
	{
		std::ostringstream err;
		err << e.what() << ". I was parsing this game:" << std::string(start_game_itr, local_itr);
		throw std::runtime_error(err.str());
	}
	return 0;
}

bool pgn::Parser::getTagList(std::string::const_iterator &itr1, const std::string::const_iterator &itr2, pgn::TagList &out)
{
	std::string::const_iterator local_itr = itr1;

	pgn::TagList taglist;
	pgn::Tag tag;
	while (getTag(local_itr, itr2, tag))
	{
		itr1 = local_itr;
		taglist.insert(tag);
	}
	if (taglist.size() == 0)
		return false;

	out = taglist;
	return true;
}

bool pgn::Parser::getTag(std::string::const_iterator &itr1, const std::string::const_iterator &itr2, pgn::Tag &out)
{
	std::string::const_iterator local_itr = itr1;
	std::string::const_iterator start_tag = itr1;

	// cerco '['
	skipBlanks(local_itr);	
	if (*local_itr != '[')
	{
		return false;
	}
	local_itr++;

	// cerco '<tagname>'
	skipBlanks(local_itr);	
	std::string tagname;

	while ((local_itr != itr2) && (isalnum(*local_itr)))
	{
		tagname += *local_itr++;
	}
	itr1 = local_itr;

	// cerco '"<tagvalue>"'
	skipBlanks(local_itr);	
	std::string tagvalue;

	if (*local_itr != '"')
	{
		pgn::invalid_tag e;
		e.bindParsingText(std::string(start_tag, local_itr)); 
		throw e;
	}
	local_itr++;

	while ((local_itr != itr2) && (*local_itr != '"'))
	{
		tagvalue += *local_itr++;
	}

	if (*local_itr != '"')
	{
		pgn::invalid_tag e;
		e.bindParsingText(std::string(start_tag, local_itr)); 
		throw e;
	}
	local_itr++;
	itr1 = local_itr;

	// cerco ']'
	skipBlanks(local_itr);	
	if (*local_itr != ']')
	{
		pgn::invalid_tag e;
		e.bindParsingText(std::string(start_tag, local_itr)); 
		throw e;
	}
	local_itr++;
	out = pgn::Tag(tagname, tagvalue);
	itr1 = local_itr;
	return true;
}

bool pgn::Parser::getMoveList(std::string::const_iterator &itr1, const std::string::const_iterator &itr2, pgn::MoveList &out)
{
	std::string::const_iterator local_itr = itr1;
	pgn::MoveList ml;

	skipBlanks(local_itr);	
	pgn::Move *move;
 	while (move = getMove(local_itr, itr2))
	{
		itr1 = local_itr;
		ml.insert(*move);
		delete move;
	}
	itr1 = local_itr;
	out = ml; 

	return true;
}

pgn::Move* pgn::Parser::getMove(std::string::const_iterator &itr1, const std::string::const_iterator &itr2)
{
	std::string::const_iterator local_itr = itr1;

	// looking for move number 
	std::string movenumber;
	int dotsCount;
	if (! getMoveNumber(local_itr, itr2, movenumber, dotsCount))
		return 0;
	itr1 = local_itr;

	// possibilita`:
	//
	// <move_number><dots> <ply> <result>
	// <move_number><dots> <ply> <move_number>
	// <move_number><dots> <ply> <ply> <result>
	// <move_number><dots> <ply> <ply> <move_number>
 
	// looking for first ply (mandatory)
	skipBlanks(local_itr);	
	pgn::Ply *firstPly=0;
	if ((firstPly = getPly(local_itr, itr2)) == 0)
		throw std::runtime_error("Error parsing move"); 

	skipBlanks(local_itr);	

	pgn::Ply *secondPly=0;
	
	// second ply, game result or another move number?
	// a ply always begins with an uppercase or lowercase alphabetic char.
	// digits and '*' have lesser ascii values. 
	// if we meet a "[" that's owned by the next game, so game result is
	// missing
	if (*local_itr > '9' && *local_itr != '[')
	{
		// looking for second ply (optional)
		secondPly = getPly(local_itr, itr2);
		skipBlanks(local_itr);	
	}
	itr1 = local_itr;

	pgn::Move *m = new pgn::Move(firstPly, secondPly, atoi(movenumber.c_str()));

	delete firstPly;
	delete secondPly;
	moveCount_++;
	return m;
}

bool pgn::Parser::getGameResult(std::string::const_iterator &itr1, const std::string::const_iterator &itr2, pgn::GameResult &out)
{
	std::string::const_iterator local_itr = itr1;

	std::string result;
	while (!isspace(*local_itr) && local_itr != itr2)
	{
		result += *local_itr++;
	}

	if (result[0] == '[')
	{
		throw pgn::missing_result(); 
	}
	else if ( (result != "1-0") &&
		 	(result != "0-1") &&
		 	(result != "1/2-1/2") &&
		 	(result != "*"))
	{
		throw pgn::invalid_result(); 
	}

	out = result;
	itr1 = local_itr;
	return true;
}

bool pgn::Parser::getMoveNumber(std::string::const_iterator &itr1, const std::string::const_iterator &itr2, std::string &out, int &dotsCount)
{
	std::string::const_iterator local_itr = itr1;

	if (!isdigit(*local_itr))
		return false;

	// looking for number 
	std::string movenumber;
	while (isdigit(*local_itr) && local_itr != itr2)
	{
		movenumber += *local_itr++;
	}
	skipBlanks(local_itr);	

	if (*local_itr != '.')
	{
		// maybe reading game result '1-0'.
		return false;
	}

	// skipping and counting dots
	dotsCount=0;	
	while ((*local_itr == '.') && (local_itr != itr2))
	{
		local_itr++;
		dotsCount++;
	}
	itr1 = local_itr;
	out = movenumber;
	return true;
}

pgn::Ply* pgn::Parser::getPly(std::string::const_iterator &itr1, const std::string::const_iterator &itr2)
{
	std::string::const_iterator local_itr = itr1;

	skipBlanks(local_itr);	
	while (!isspace(*local_itr)) local_itr++;
	pgn::Ply *p = new pgn::Ply(std::string(itr1, local_itr));

	skipBlanks(local_itr);	
	itr1 = local_itr;

	pgn::CommentText comment;
	if (getComment(local_itr, itr2, comment))
	{
		skipBlanks(local_itr);	
		itr1 = local_itr;
		p->bindComment(comment);
	}

	checkForVariations(local_itr, itr2);
	itr1 = local_itr;

	checkForGlyphs(local_itr, itr2);
	itr1 = local_itr;

	plyCount_++;
	return p;
}

bool pgn::Parser::getComment(std::string::const_iterator &itr1, const std::string::const_iterator &itr2, pgn::CommentText &out)
{
	std::string::const_iterator local_itr = itr1;
	std::string comment;
	if (*local_itr != '{')
		return false;
	local_itr++; // skipping '{'

	while ((*local_itr != '}') && (local_itr != itr2))
	{
		comment += *local_itr++;
	}
	local_itr++; // skipping '}'
	skipBlanks(local_itr);	
	itr1 = local_itr;
	out = pgn::CommentText(comment);
	return true;
}

void pgn::Parser::checkForVariations(std::string::const_iterator &itr1, const std::string::const_iterator &itr2)
{
	if (*itr1 == '(')
		throw unsupported_variations();
}

void pgn::Parser::checkForGlyphs(std::string::const_iterator &itr1, const std::string::const_iterator &itr2)
{
	if (*itr1 == '$')
		throw unsupported_glyphs();
}

