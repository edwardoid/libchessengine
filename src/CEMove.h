/* Copyright (C) 
* 2012 - Edward Sarkisyanr <edward.sarkisyan@gmail.com>
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
* 
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
* 
*/

#ifndef CHESS_ENGINE_MOVE
#define CHESS_ENGINE_MOVE

#include "CEPiece.h"
#include <PGNSquare.h>
#include <deque>

namespace pgn
{
	class Ply;
};

namespace ChEngn
{
	class Table;

	class Move
	{
	public:

        /**
        * @brief 
        *
        * @param pgn::Ply
        * @param bool
        */
		Move(const pgn::Ply*, const bool);
		
        /**
        * @brief 
        */
        virtual ~Move() {};
		
        /**
        * @brief 
        *
        * @param table
        *
        * @return 
        */
        virtual bool make(const Table* table) const = 0;
		
        /**
        * @brief 
        *
        * @param character
        *
        * @return 
        */
        static piece_type guessTypeByChar( const char character );
		
		/**
		 * @brief Moves piece for current table, and check for check.
		 * Tries to move piece form current table, is piece on given
		 * square is no ChEngn::king and checks is new position check
		 * position for given player
		 * @param oldPos - Position from piece will be moved
		 * @param newPos - Position where piece will be moved
		 * @param isWhite - Player color. True if player's color is white,
		 * false in other case.
		 * @return true if new check found
		 * @warning only ChEngn::queen, ChEngn::rook and ChEngn::bishop will
		 * be checked!
		 */
		bool moveAndCheckForCheck(	const Table* table,
									const pgn::Square oldPos,
									const pgn::Square newPos,
									const bool isWhite ) const;
		/** Tries to found check in given table for given color's player.
		 * @brief Checks for check on table.
		 * @param tbl - Source table
		 * @param isWhite - Player color. True if player's color white,
		 * false in other case.
		 * @return true if check position found.
		 */
		static bool isCheck( const Table& tbl, bool isWhite );

		PieceEx movedPiece() const { return m_movedPieceEx; }
		friend class PawnMove;
		friend class KnightMove;
		friend class BishopMove;
		friend class RookMove;
	protected:
		mutable PieceEx m_movedPieceEx;
		bool m_isWhite;
		const pgn::Ply *m_ply;
	};

    typedef std::deque<Move*> MovesDeque;
}

#endif // CHESS_ENGINE_MOVE 
