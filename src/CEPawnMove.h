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


#ifndef CHESS_ENGINE_PAWN_MOVE
#define CHESS_ENGINE_PAWN_MOVE

#include "CEMove.h"
#include <PGNSquare.h>

namespace pgn
{
	class Ply;
};

namespace ChEngn
{
	class Table;

	class PawnMove: public Move
	{
	public:
		
        /**
        * @brief 
        *
        * @param ply
        * @param isWhite
        */
        PawnMove( const pgn::Ply* ply, const bool isWhite);

        /**
        * @brief 
        */
		~PawnMove();

        /**
        * @brief 
        *
        * @param table
        *
        * @return 
        */
		virtual bool make( const Table* table) const;
	private:

        /**
        * @brief 
        *
        * @param table
        *
        * @return 
        */
		bool makeCaptureMove(const Table* table) const;

        /**
        * @brief 
        *
        * @param table
        *
        * @return 
        */
		bool makeSimpleMove(const Table* table) const;
	private:
		pgn::Ply* m_ply;
		pgn::Square m_newPos;
	};
};

#endif // CHESS_ENGINE_PAWN_MOVE
