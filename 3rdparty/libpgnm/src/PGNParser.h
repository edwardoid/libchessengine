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

#ifndef PGNParser_h
#define PGNParser_h

#include "PGNM.h"
#include <string>

/**
class PGNM_EXPORT pgn::CommentText;
class PGNM_EXPORT pgn::Game;
class PGNM_EXPORT pgn::GameCollection;
class PGNM_EXPORT pgn::GameResult;
class PGNM_EXPORT pgn::Move;
class PGNM_EXPORT pgn::MoveList;
class PGNM_EXPORT pgn::Piece;
class PGNM_EXPORT pgn::Ply;
class PGNM_EXPORT pgn::Square;
class PGNM_EXPORT pgn::Tag;
class PGNM_EXPORT pgn::TagList;

*/

namespace pgn
{
	class PGNM_EXPORT Parser
	{
		public:

			Parser():plyCount_(0),moveCount_(0),gameCount_(0) {}

			bool getGameCollection(std::string::const_iterator &itr1, 
											const std::string::const_iterator &itr2, pgn::GameCollection &out);
			pgn::Game* getGame(std::string::const_iterator &itr1, 
											const std::string::const_iterator &itr2);
			bool getMoveList(std::string::const_iterator &itr1, 
											const std::string::const_iterator &itr2, pgn::MoveList &out);
			pgn::Move* getMove(std::string::const_iterator &itr1, 
											const std::string::const_iterator &itr2);
			pgn::Ply* getPly(std::string::const_iterator &itr1, 
											const std::string::const_iterator &itr2);
			bool getTagList(std::string::const_iterator &itr1, 
											const std::string::const_iterator &itr2, pgn::TagList &out);
			bool getTag(std::string::const_iterator &itr1, 
											const std::string::const_iterator &itr2, pgn::Tag &out);
			bool getGameResult(std::string::const_iterator &itr1, 
											const std::string::const_iterator &itr2, pgn::GameResult &out);
			bool getComment(std::string::const_iterator &itr1, 
											const std::string::const_iterator &itr2, pgn::CommentText &out);
			bool getMoveNumber(std::string::const_iterator &itr1, 
											const std::string::const_iterator &itr2, std::string &out, int &dotsCount);
			// TODO: temporanee per segnalare opportunamente l'errore di parsing
			// dovuto al mancato supporto delle varianti e dei glyphs.
			void checkForVariations(std::string::const_iterator &itr1, const std::string::const_iterator &itr2);
			void checkForGlyphs(std::string::const_iterator &itr1, const std::string::const_iterator &itr2);

			unsigned long plyCount() const { return plyCount_; }
			unsigned long moveCount() const { return moveCount_; }
			unsigned long gameCount() const { return gameCount_; }

		private:

			static void skipBlanks(std::string::const_iterator &itr1);

			unsigned long plyCount_;
			unsigned long moveCount_;
			unsigned long gameCount_;

	};
}
#endif // PGNParser_h
