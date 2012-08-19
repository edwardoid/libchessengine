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

#ifndef PGNGame_h
#define PGNGame_h

#include <fstream>
#include "PGNGameResult.h"
#include "PGNTagList.h"
#include "PGNMoveList.h"
#include "PGNM.h"

/**
 * @brief global namespace for libpgnm
 * @namespace pgn
 */
namespace pgn
{

	/**
	 * @class PGNM_EXPORT Game
	 * @brief Represents information about game.
	 */
	class PGNM_EXPORT Game 
	{
		public:
			
			/**
			 * @brief Constructs game with given tags, moves and result.
			 * @param tl A Set of tags and values for current game.
			 * @param ml list of moves for game.
			 * @param gr Result of a game.
			 */
			Game(const TagList &tl, const MoveList &ml, const GameResult &gr);

			/**
			 * @brief Copy-constructor.
			 * @param src Source game.
			 */
			Game(const Game& src);

			/**
			 * @brief Destructor.
			 */
			virtual ~Game();

			/**
			 * @brief Copy given game to current.
			 * @param src Source game.
			 * @return Reference to changed game.
			 */
			Game& operator = (const Game& src);

			/**
			 * 2 games are equal if is equal their tags, moves, and result.
			 * @brief Compares 2 games.
			 * @param src Source game.
			 * @return true if games are equal.
			 */
			bool operator == (const Game& src) const;

			/**
			 * @brief Negotive version of operator==().
			 */
			bool operator != (const Game& src) const;
		
			/**
			 * Returns tags with values associated to the game.
			 * @brief Returns tags and values.
			 * @return Set of tags.
			 */
			TagList& tags() const;

			/**
			 * @brief Returns game's move list.
			 * @return Game moves.
			 */
			MoveList& moves() const;

			/**
			 * @brief Get time when game was/is 
			 * finished/going.
			 * @return Value of tag "Date".
			 */
			std::string date() const;

			/**
			 * @brief Get white player's name.
			 * @return Value of tag "White".
			 */
			std::string white() const;
			
			/**
			 * @brief Get black player's name.
			 * @return Value of tag "Black".
			 */
			std::string black() const;
			
			/**
			 * @brief Get game's result.
			 * @return Value of tag "Result".
			 */
			GameResult result() const;

			/**
			 * @brief Sets pre-game comment.
			 * @param ct Comment.
			 */
			void bindBeforeGameComment(const CommentText &ct);

			/**
			 * @brief Sets post-game comment.
			 * @param ct Comment.
			 */
			void bindAfterGameComment(const CommentText &ct);

			/**
			 * @brief Prints game to stream.
			 * @param os Stream to print.
			 * @param src Game to print.
			 *
			 *	Prints tags by one to line, then prints moves, and then game
			 *	result.
			 */
			friend std::ostream& operator << ( std::ostream& os, const Game& src);

		private:

			struct GameData *hdata;
	};
};

#endif 

