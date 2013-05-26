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

#include <sstream>
#include <iostream>
#include "PGNSquare.h"

pgn::Square::Square()
{
	col_ = 0;
	row_ = 0;
//	std::cout << "new Square " << sizeof(*this) << std::endl; 
}

pgn::Square::Square(char col, char row)
:col_(col),row_(row)
{
//	std::cout << "new Square " << sizeof(*this) << std::endl; 
}

pgn::Square::Square(const pgn::Square& src)
:col_(src.col_),row_(src.row_)
{
//	std::cout << "new Square " << sizeof(*this) << std::endl; 
}

pgn::Square::~Square()
{ 
//	std::cout << "deleting Square " << sizeof(*this) << std::endl; 
}

pgn::Square& pgn::Square::operator = (const pgn::Square& src)
{
	if (&src == this)
		return (*this);

	col_ = src.col_;
	row_ = src.row_;

	return(*this);
}

bool pgn::Square::operator == (const pgn::Square& src) const
{
	return (col_ == src.col_) && (row_ == src.row_);
}

char pgn::Square::col() const
{
	return col_;
}

char pgn::Square::row() const
{
	return row_;
}

bool pgn::Square::operator != (const pgn::Square& src) const 
{
	return !(src == *this);
}

//
// these methods remap board coordinates as follows
//
// 8  . . . . . . . .     ---->      7  . . . . . . . . 
// 7  . . . . . . . .                6  . . . . . . . . 
// 6  . . . . . . . .                5  . . . . . . . . 
// 5  . . . . . . . .     ---->      4  . . . . . . . . 
// 4  . . . . . . . .     ---->      3  . . . . . . . . 
// 3  . . . . . . . .                2  . . . . . . . . 
// 2  . . . . . . . .                1  . . . . . . . . 
// 1  . . . . . . . .     ---->      0  . . . . . . . . 
//                                 
//    a b c d e f g h                   0 1 2 3 4 5 6 7
//
int pgn::Square::colIndex() const
{
	return (col_ - 'a');
}
int pgn::Square::rowIndex() const
{
	return (row_ - '1');
}

pgn::Square::operator bool () const
{
	return isValid(*this);
}

bool pgn::Square::isValid(const pgn::Square& sq)
{
	return sq.colIndex() > -1 && sq.colIndex() < 8 && sq.rowIndex() > -1 && sq.rowIndex() < 8;
}