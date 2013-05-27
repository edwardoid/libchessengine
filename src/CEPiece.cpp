//
// Copyright (C) 2002 Edward Sarkisyan <edward.sarkisyan@gmail.com>
//
//     This file is part of libchessengine.
//
//     libchessengine is free software; you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation; either version 2 of the License, or
//     (at your option) any later version.     
// 
//     libchessengine is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
// 
//     See the GNU General Public License for more details. 
// 
//     You should have received a copy of the GNU General Public License
//     along with pgnlib; if not, write to the Free Software Foundation, 
//     Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

#include "CEPiece.h"



CE::Piece::Piece(piece_type tpe, piece_color col)
{
	m_piece = tpe | col;
}

CE::Piece::Piece(const Piece &other)
{
	m_piece = other.color() | other.type() | other.moveFlag();
}

CE::Piece::~Piece()
{
}


CE::piece_type CE::Piece::type() const
{
	return ( m_piece & unknown );
}

CE::piece_color CE::Piece::color() const
{
	return ( m_piece & white );
}

bool CE::Piece::isWhite() const
{
	return ( color() == white );
}

bool CE::Piece::isBlack() const
{
	return ( color() == black );
}

bool CE::Piece::isUnknown() const
{
	return ( type() == unknown );
}

CE::piece_movement_flag CE::Piece::moveFlag() const
{
	return ( m_piece & moved );
}

void CE::Piece::setType(CE::piece_type tpe)
{
	m_piece = color() | moveFlag() | tpe;
}

void CE::Piece::setWhite()
{
	m_piece = m_piece | white;
}

void CE::Piece::setBlack()
{
	m_piece = type() | moveFlag();
}

void CE::Piece::setMoved()
{
	m_piece = m_piece | moved;
}

void CE::Piece::operator = ( const CE::Piece& other )
{
	m_piece = other.type() | other.color() | other.moveFlag();
}

bool CE::Piece::operator == ( const CE::Piece& other ) const
{
	if( m_piece == other.m_piece )
		return true;
	return false;
}

bool CE::Piece::operator != ( const CE::Piece& other ) const
{
	return !(operator==(other));
}

namespace CE
{
	std::ostream & operator << (std::ostream &out, const Piece &pce)
	{
		char symbol = '.';
		switch (pce.type())
		{
			case pawn:
				symbol = 'p';
				break;

			case knight:
				symbol = 'n';
				break;

			case bishop:
				symbol = 'b';
				break;
		
			case rook:
				symbol = 'r';
				break;
			case queen:
				symbol = 'q';
				break;

			case king:
				symbol = 'k';
				break;

			default:
				symbol = '.';
		}
		if(pce.isWhite() && ( !pce.isUnknown()))
			symbol -= 32;

		return out<<symbol;
	}
};
