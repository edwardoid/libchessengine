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

#ifndef CHESS_ENGINE_ROOK_MOVE
#define CHESS_ENGINE_ROOK_MOVE

#include "CEGlobal.h"
#include "CEMove.h"

namespace CE
{
    /**
    * @class RookMove
    * @brief 
    */
    class CE_EXPORT RookMove: public Move
    {
    public:
        
        /**
        * @brief 
        *
        * @param pgn::Ply
        * @param bool
        */
        RookMove(const pgn::Ply*, const bool);

        /**
        * @brief 
        */
        virtual ~RookMove();
        
        /**
        * @brief 
        *
        * @param table
        *
        * @return 
        */
        virtual bool make(const Table* table) const;

	    static bool checkForEmptynessColumn(char fromRow, char toRow, char onColumn, const Table *table);
        static bool checkForEmptynessRow(char fromColumn, char toColumn, char onRow, const Table *table);
    };
}

#endif
