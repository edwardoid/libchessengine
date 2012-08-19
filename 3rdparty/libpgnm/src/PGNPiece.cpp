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

#include <cstdio>
#include <cassert>
#include <sstream>
#include <iostream>
#include "PGNPiece.h"

pgn::Piece::Piece()
{
	id_='p';
//	std::cout << "new Piece " << sizeof(*this) << std::endl; 
}

pgn::Piece::Piece(const pgn::Piece &src)
{
	id_ = src.id_;
//	std::cout << "new Piece " << sizeof(*this) << std::endl; 
}

pgn::Piece& pgn::Piece::operator = (const pgn::Piece& src) 
{
	id_ = src.id_;

	return *this;
}

pgn::Piece::Piece(const char id)
:id_(id)
{
//	std::cout << "new Piece " << sizeof(*this) << std::endl; 
}

bool pgn::Piece::operator == (const pgn::Piece& src) const
{
	return id_ == src.id_;
}

bool pgn::Piece::operator != (const pgn::Piece& src) const 
{
	return !(src == *this);
}

char pgn::Piece::id() const 
{ 
	return id_; 
}

std::string pgn::Piece::toStdString()
{
	std::string res="";
	if (id_ != 'p')
		res += id_;
	return res;
}

namespace pgn
{
	std::ostream& operator << ( std::ostream& os, const pgn::Piece& src ) 
	{
		if (src.id_ != 'p')
			os << src.id_;
		return os;
	}
}

