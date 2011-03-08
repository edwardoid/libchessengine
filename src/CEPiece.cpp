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



ChEngn::Piece::Piece(piece_type tpe, piece_color col)
{
	m_piece = tpe | col;
}

ChEngn::Piece::Piece(const Piece &other)
{
	m_piece = other.color() | other.type() | other.moveFlag();
}

ChEngn::Piece::~Piece()
{
}


ChEngn::piece_type ChEngn::Piece::type() const
{
	return ( m_piece & unknown );
}

ChEngn::piece_color ChEngn::Piece::color() const
{
	return ( m_piece & white );
}

bool ChEngn::Piece::isWhite() const
{
	return ( color() == white );
}

bool ChEngn::Piece::isBlack() const
{
	return ( color() == black );
}

bool ChEngn::Piece::isUnknown() const
{
	return ( type() == unknown );
}

ChEngn::piece_movement_flag ChEngn::Piece::moveFlag() const
{
	return ( m_piece & moved );
}

void ChEngn::Piece::setType(ChEngn::piece_type tpe)
{
	m_piece = color() | moveFlag() | tpe;
}

void ChEngn::Piece::setWhite()
{
	m_piece = m_piece | white;
}

void ChEngn::Piece::setBlack()
{
	m_piece = type() | moveFlag();
}

void ChEngn::Piece::setMoved()
{
	m_piece = m_piece | moved;
}

void ChEngn::Piece::operator = (const ChEngn::Piece& other)
{
	m_piece = other.type() | other.color() | other.moveFlag();
}

bool ChEngn::Piece::operator == (const ChEngn::Piece& other) const
{
	if( m_piece == ( other.type() | other.color() | other.moveFlag() ) )
		return true;
	return false;
}

namespace ChEngn
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
