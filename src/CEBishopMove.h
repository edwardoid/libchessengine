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

#ifndef CHESS_ENGINE_BISHOP_MOVE
#define CHESS_ENGINE_BISHOP_MOVE

#include "CEGlobal.h"
#include "CEMove.h"
#include <PGNSquare.h>

namespace pgn
{
	class Ply;
};

namespace CE
{
    /**
    * @brief 
    */
	class CE_EXPORT BishopMove: public Move
	{
	public:

        /**
        * @brief 
        *
        * @param ply
        * @param isWhite
        */
		BishopMove( const pgn::Ply* ply, const bool isWhite );
		
        /**
        * @brief 
        */
        ~BishopMove();
		
        /**
        * @brief 
        *
        * @param table
        *
        * @return 
        */
        bool  make( const Table* table ) const;

		static bool checkEmptynessDiagonal(char fromColumn, char fromRow, char toColumn, char toRow, const Table* table);
	private:
        
        /**
        * @brief 
        *
        * @param ply
        * @param table
        * @param isWhite
        *
        * @return 
        */
        static CE::Piece* findMovedPiece( const pgn::Ply* ply, const Table* table, const bool isWhite);
	};
}
#endif // CHESS_ENGINE_BISHOP_MOVE
