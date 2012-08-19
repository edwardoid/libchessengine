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

#ifndef PGNPiece_h
#define PGNPiece_h
#include <string>
#include "PGNM.h"

namespace pgn
{
	class PGNM_EXPORT Piece 
	{
		public:

			static const Piece Pawn() { return 'p'; }
			static const Piece Knight() { return 'N'; }
			static const Piece Bishop() { return 'B'; }
			static const Piece Rook() { return 'R'; }
			static const Piece Queen() { return 'Q'; }
			static const Piece King() { return 'K'; }

			Piece();
			Piece(const Piece &src);
			Piece(const char id);

			Piece& operator = (const Piece& src);
			bool operator == (const Piece& src) const;
			bool operator != (const Piece& src) const; 

			char id() const;
			std::string toStdString();
			friend std::ostream& operator << ( std::ostream& os, const pgn::Piece& src);

		private:
	
			char id_;
	};
};

#endif 

