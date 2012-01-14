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

#include <cstdio>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <PGNPly.h>
#include <PGNCommentText.h>
#include <PGNException.h>

#include <iostream>

namespace pgn 
{
	const char longCastleFlag  = 0x01;
	const char shortCastleFlag = 0x02;
	const char captureFlag     = 0x04;
	const char checkFlag       = 0x08;
	const char checkmateFlag   = 0x10;
	struct PlyData 
	{
		pgn::Piece piece;
		pgn::Piece *promoted;
		char fromSquare;
		pgn::Square toSquare;
		char flags;
		pgn::CommentText *comment;
	};
};

pgn::Ply::Ply(const pgn::Ply& src) 
{
	hdata = new PlyData;

	hdata->piece = src.hdata->piece;
	hdata->fromSquare = src.hdata->fromSquare;
	hdata->toSquare = src.hdata->toSquare;
	hdata->flags = src.hdata->flags;
	if ( 0 != src.hdata->promoted)
		hdata->promoted = new pgn::Piece(*(src.hdata->promoted));
	else
		hdata->promoted = 0;
	if ( 0 != src.hdata->comment)
		hdata->comment = new pgn::CommentText(*(src.hdata->comment));
	else
		hdata->comment = 0;
//	std::cout << "new PlyData " << sizeof(*hdata) << std::endl; 
}

pgn::Ply::Ply(const std::string& ply_text)
{
	hdata = new PlyData;
	hdata->flags = 0;
	hdata->fromSquare = '-';
	hdata->comment = 0;
	hdata->promoted = 0;
	std::string ptext = ply_text;

	char piece_char = '-';
	char col_coor = '-';
	char row_coor = '-';
	std::string extra_signs;
	std::string::const_iterator pitr = ptext.begin();
	char promoted_piece = '-';
	for (pitr = ply_text.begin(); pitr != ply_text.end(); pitr++)
	{
		switch (*pitr)
		{
			case 'R':
			case 'K':
			case 'Q':
			case 'B':
			case 'N':
				if (*(pitr-1) == '=')
					promoted_piece = *pitr;
				else
					piece_char = *pitr;
				break;
			case 'x':
				hdata->flags |= captureFlag; 
				break;
			case '#':
				hdata->flags |= checkmateFlag; 
				break;
			case '+':
				hdata->flags |= checkFlag; 
				break;
			case 'O':
			case '-':
			case '=':
				break;
			case 'a':
			case 'b':
			case 'c':
			case 'd':
			case 'e':
			case 'f':
			case 'g':
			case 'h':
				if (col_coor == '-')
				{
					col_coor = *pitr;
				}
				else
				{
					hdata->fromSquare = col_coor;
					col_coor = *pitr;
				}
				break;
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
				if (row_coor == '-')
				{
					row_coor = *pitr;
				}
				else
				{
					hdata->fromSquare = row_coor;
					row_coor = *pitr;
				}
				break;
			case '0':
				throw pgn::invalid_castle_string();
				break;
			default:
				{
//					std::ostringstream err;
//					err << "Invalid character " << static_cast<char>(*pitr) << " in ply " << ptext;
					throw pgn::invalid_ply_text(ptext);
//					throw std::runtime_error(err.str());
				}
				break;
		}
	}
	if (ptext.find("O-O-O") != std::string::npos)
	{
		hdata->flags |= longCastleFlag; 
	}
	else if (ptext.find("O-O") != std::string::npos)
	{
		hdata->flags |= shortCastleFlag; 
	}
	else
	{
		if (piece_char == '-')
			hdata->piece = pgn::Piece();
		else
			hdata->piece = pgn::Piece(piece_char);
		if (promoted_piece != '-')
			hdata->promoted = new pgn::Piece(promoted_piece);
		hdata->toSquare = pgn::Square(col_coor,row_coor);
	}
}

pgn::Ply::~Ply() 
{
//	if( hdata->comment != 0 )
		delete hdata->comment;

	if( hdata->promoted != 0 )
		delete hdata->promoted;
	delete hdata;
}

pgn::Ply& pgn::Ply::operator = (const pgn::Ply& src) 
{
	hdata->piece = src.hdata->piece;
	hdata->fromSquare = src.hdata->fromSquare;
	hdata->toSquare = src.hdata->toSquare;
	hdata->flags = src.hdata->flags;

	if (src.hdata->promoted)
	{
		if ( 0 != hdata->promoted )
			delete hdata->promoted;
		hdata->promoted = new pgn::Piece(*(src.hdata->promoted));
	}
	else
		hdata->promoted = 0;

	if ( 0 != hdata->comment )
			delete hdata->comment;

	if ( 0  != src.hdata->comment)
		hdata->comment = new pgn::CommentText(*(src.hdata->comment));
	else
		hdata->comment = 0;

	return *this;
}

bool pgn::Ply::operator == (const pgn::Ply& src) const
{
	if (hdata->piece != src.hdata->piece)
		return false;
	if (hdata->fromSquare != src.hdata->fromSquare)
		return false;
	if (hdata->toSquare != src.hdata->toSquare)
		return false;
	if (hdata->flags != src.hdata->flags)
		return false;

	if ((hdata->promoted != 0) && (src.hdata->promoted != 0) &&
			*(hdata->promoted) != *(src.hdata->promoted))
		return false;

	if (((hdata->promoted == 0) && (src.hdata->promoted != 0)) ||
		((hdata->promoted != 0) && (src.hdata->promoted == 0)))
		return false;

	if ((hdata->comment != 0) && (src.hdata->comment != 0) &&
			*(hdata->comment) != *(src.hdata->comment))
		return false;

	if (((hdata->comment == 0) && (src.hdata->comment != 0)) ||
		((hdata->comment != 0) && (src.hdata->comment == 0)))
		return false;

	return true;
}

std::string pgn::Ply::toStdString() const
{
	std::string res;
	if (isLongCastle())
	{
		res += "O-O-O";
		if (isCheckMate())
			res +=  "#";
		else if (isCheck())
			res += "+";
	}
	else if (isShortCastle())
	{
		res += "O-O";
		if (isCheckMate())
			res +=  "#";
		else if (isCheck())
			res += "+";
	}
	else
	{
		res +=  hdata->piece.toStdString();
		if (hdata->fromSquare != '-')
			res +=  hdata->fromSquare;
		if (isCapture())
			res += "x";
 		res += hdata->toSquare.col();
 		res += hdata->toSquare.row();
		if (hdata->promoted)
		{
			res += "=";
			res += hdata->promoted->toStdString();
		}
		if (isCheckMate())
			res += "#";
		else if (isCheck())
			res += "+";
	}

	if (hdata->comment)
		res += hdata->comment->toStdString();

	return res;
}

std::ostream& pgn::operator << ( std::ostream& os, const pgn::Ply& src ) 
{
	if (src.isLongCastle())
	{
		os << "O-O-O";
		if (src.isCheckMate())
			os << "#";
		else if (src.isCheck())
			os << "+";
	}
	else if (src.isShortCastle())
	{
		os << "O-O";
		if (src.isCheckMate())
			os << "#";
		else if (src.isCheck())
			os << "+";
	}
	else
	{
		os << src.hdata->piece;
		if (src.hdata->fromSquare != '-')
			os << src.hdata->fromSquare;
		if (src.isCapture())
			os << "x";
 		os << src.hdata->toSquare.col() << src.hdata->toSquare.row();
		if (src.hdata->promoted)
			os << "=" << *(src.hdata->promoted);
		if (src.isCheckMate())
			os << "#";
		else if (src.isCheck())
			os << "+";
	}

	if (src.hdata->comment)
		os << *(src.hdata->comment);

	return os;
}

bool pgn::Ply::operator != (const pgn::Ply& src) const 
{
	return !(src == *this);
}

bool pgn::Ply::isLongCastle() const 
{ 
	return hdata->flags & longCastleFlag; 
}

bool pgn::Ply::isShortCastle() const 
{ 
	return hdata->flags & shortCastleFlag; 
}

bool pgn::Ply::isCapture() const 
{ 
	return hdata->flags & captureFlag; 
}

bool pgn::Ply::isCheck() const 
{ 
	return hdata->flags & checkFlag; 
}

bool pgn::Ply::isCheckMate() const 
{ 
	return hdata->flags & checkmateFlag; 
}

char pgn::Ply::fromSquare() const 
{ 
	return hdata->fromSquare; 
}

pgn::Square pgn::Ply::toSquare() const 
{ 
	return hdata->toSquare; 
}

pgn::Piece pgn::Ply::piece() const 
{ 
	return hdata->piece; 
}

pgn::Piece* pgn::Ply::promoted() const 
{ 
	return hdata->promoted; 
}

void pgn::Ply::bindComment(const CommentText &comment)
{
	delete hdata->comment;
	hdata->comment = new pgn::CommentText(comment);
}

void pgn::Ply::unbindComment()
{
	delete hdata->comment;
	hdata->comment = 0;
}

