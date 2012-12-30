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


#ifndef CHESS_ENGINE_KNIGHT_MOVE
#define CHESS_ENGINE_KNIGHT_MOVE

#include "CEGlobal.h"
#include "CEMove.h"
#include <PGNSquare.h>

namespace pgn
{
	class Ply;
};

namespace ChEngn
{
	class CE_EXPORT KnightMove: public Move
	{
	public:

        /**
        * @brief 
        *
        * @param ply
        * @param isWhite
        */
		KnightMove( const pgn::Ply* ply, const bool isWhite );
		
        /**
        * @brief 
        */
        ~KnightMove();
		
        /**
        * @brief 
        *
        * @param table
        *
        * @return 
        */
        bool  make( const Table* table ) const;
	private:
		
        /**
        * @brief 
        *
        * @param table
        * @param newPos
        *
        * @return 
        */
        pgn::Square try2Top1Right( const Table* table, const pgn::Square& newPos ) const;

        /**
        * @brief 
        *
        * @param table
        * @param newPos
        *
        * @return 
        */
		pgn::Square try2Right1Top( const Table* table, const pgn::Square& newPos ) const;	
		
        /**
        * @brief 
        *
        * @param table
        * @param newPos
        *
        * @return 
        */
        pgn::Square try2Right1Bottom( const Table* table, const pgn::Square& newPos ) const;
		
        /**
        * @brief 
        *
        * @param table
        * @param newPos
        *
        * @return 
        */
        pgn::Square try2Bottom1Right( const Table* table, const pgn::Square& newPos ) const;
		
        /**
        * @brief 
        *
        * @param table
        * @param newPos
        *
        * @return 
        */
        pgn::Square try2Bottom1Left( const Table* table, const pgn::Square& newPos ) const;

        /**
        * @brief 
        *
        * @param table
        * @param newPos
        *
        * @return 
        */
		pgn::Square try2Left1Bottom( const Table* table, const pgn::Square& newPos ) const;

        /**
        * @brief 
        *
        * @param table
        * @param newPos
        *
        * @return 
        */
		pgn::Square try2Left1Top( const Table* table, const pgn::Square& newPos ) const;

        /**
        * @brief 
        *
        * @param table
        * @param newPos
        *
        * @return 
        */
		pgn::Square try2Top1Left( const Table* table, const pgn::Square& newPos ) const;

        /**
        * @brief 
        *
        * @param table
        * @param oldPos
        * @param newPos
        *
        * @return 
        */
		bool tryToFindKnight(  const Table* table,
				       const pgn::Square& oldPos,
				       const pgn::Square& newPos ) const;
	private:
		mutable Piece *m_movedPiece;
		mutable char m_row;
		mutable char m_column;
	};
}

#endif // CHESS_ENGINE_KNIGHT_MOVE
