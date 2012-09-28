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

#ifndef PGNSquare_h
#define PGNSquare_h

#include "PGNMGlobals.h"
#include <string>

namespace pgn 
{
	class PGNM_EXPORT Square 
	{
		public:
		
			Square();
			Square(char col, char row);
			Square(const Square& src);

			virtual ~Square();

			Square& operator = (const Square& src);
			bool operator == (const Square& src) const;
			bool operator != (const Square& src) const;
	
			char col() const;
			char row() const;
			int colIndex() const;
			int rowIndex() const;

		private:
	
			char col_;
			char row_;

	};
};

#endif 
