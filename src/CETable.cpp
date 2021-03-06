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

#include "CEGlobal.h"
#include "CETable.h"
#include <assert.h>

CE::Table::Table()
{
	m_table = 0;
	getMemoryForTable();
	resetComplect();
}

CE::Table::Table(const Table &other)
{
	m_table = 0;
	*this = other;
}

CE::Table::~Table()
{
	cleanMemory();
}

CE::Piece** CE::Table::table()
{
	return m_table;
}

void CE::Table::cleanTable()
{
	if( 0 == m_table )
		getMemoryForTable();
	assert( 0 != m_table );

	for( int i = 0; i < default_table_height; i++ )
		for( int j = 0; j < default_table_width; j++ )
			m_table[i][j].setType( unknown );
}

CE::Piece* CE::Table::pieceAt(unsigned int column, unsigned int row) const
{
	assert( 0 != m_table );
	if( (row < default_table_height) && (column < default_table_width) )
		return &m_table[row][column];
	return 0;
}

CE::Piece* CE::Table::pieceAtC(char column, char row) const
{
	return pieceAt( column -'a', row - '1');
}
void CE::Table::getMemoryForTable()
{
	if( 0 != m_table )
		return;
	m_table = new Piece*[default_table_height];
	for ( unsigned int i = 0; i < default_table_height; i++ )
		m_table[i] = new Piece[default_table_width];
}

void CE::Table::fillDefault()
{
	assert( 0 != m_table );
	for ( unsigned int i = 0; i < default_table_height; i++ )
	{
		for (unsigned int  j = 0; j < default_table_width; j++ )
			m_table[i][j] = Piece();
	}
}

void CE::Table::cleanMemory()
{
	if ( 0 == m_table )
		return;
	for ( unsigned int i = 0; i < default_table_height; i++ )
		delete []m_table[i];
	delete []m_table;
	m_table = 0;
}

void CE::Table::resetComplect()
{
	if ( m_table == 0 )
		getMemoryForTable();
	// Set white player's complect
	// Pawns first of all
	for ( unsigned int i = 0; i < default_table_width; i++ )
		m_table[1][i] = Piece( pawn, white );
	m_table[0][0] = Piece ( rook, white );
	m_table[0][7] = Piece ( rook, white );
    m_table[0][1] = Piece ( knight, white );
	m_table[0][6] = Piece ( knight, white );
	m_table[0][2] = Piece ( bishop, white );
	m_table[0][5] = Piece ( bishop, white );
	m_table[0][3] = Piece ( queen, white );
	m_table[0][4] = Piece ( king, white );

	// Time to blacks!
	//
	for ( unsigned int i = 0; i <default_table_width; i++ )
		m_table[6][i] = Piece ( pawn, black);
	m_table[7][0] = Piece ( rook, black );
	m_table[7][7] = Piece ( rook, black );
    m_table[7][1] = Piece ( knight, black );
	m_table[7][6] = Piece ( knight, black );
	m_table[7][2] = Piece ( bishop, black );
	m_table[7][5] = Piece ( bishop, black );
	m_table[7][3] = Piece ( queen, black );
	m_table[7][4] = Piece ( king, black );
}

void CE::Table::operator = (const CE::Table &other)
{
//	cleanMemory();
	getMemoryForTable();
	for (unsigned int i = 0; i < default_table_height; i++ )
		for (unsigned int j = 0; j< default_table_width; j++)
		{
			Piece* tmp = other.pieceAt( i, j );
			if ( 0 != tmp )
				m_table[j][i] = *tmp;
			else
				std::cerr << "Got invalid pointer to piece in copy-constructor" << std::endl;
		};
}

CE::PieceEx CE::Table::detailed( Piece* piece ) const
{
	for(int r = 0; r < default_table_height; ++r)
	{
		for(int c = 0; c < default_table_height; ++c)
		{
			if(piece == pieceAt(c, r))
				return PieceEx(	*piece,
								r, 
								c); 
		}
	}
	return CE::PieceEx(*piece, -1, -1);
}


namespace CE
{
	std::ostream& operator << (std::ostream &out, const Table& tbl)
	{
		for ( unsigned int i = default_table_height -1 ; i != -1; i-- )
		{
			out<<std::endl<< i + 1<< " ";
			for (unsigned int  j = 0; j < default_table_width; j++ )
				out<< *tbl.pieceAt(i,j);
		}
		out<<std::endl<<"  ";
		for ( unsigned int i = 0; i < default_table_width; i++)
			out<<char('a'+i);
		return out;
	}
};
