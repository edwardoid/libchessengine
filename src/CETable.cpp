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

#include "CETable.h"
#include <assert.h>

ChEngn::Table::Table()
{
	m_table = 0;
	getMemoryForTable();
	resetComplect();
}

ChEngn::Table::Table(const Table &other)
{
	m_table = 0;
	getMemoryForTable();
	assert( 0 != m_table );
	for (unsigned int i = 0; i < default_table_height; i++ )
		for (unsigned int j = 0; j< default_table_width; j++)
		{
			Piece* tmp = other.pieceAt( i, j );
			if ( 0 != tmp )
				m_table[i][j] = *tmp;
			else
				std::cerr << "Got invalid pointer to piece in copy-constructor" << std::endl;
		}
}

ChEngn::Table::~Table()
{
}

ChEngn::Piece** ChEngn::Table::table()
{
	return m_table;
}

ChEngn::Piece* ChEngn::Table::pieceAt(unsigned int column, unsigned int row) const
{
	assert( 0 != m_table );
	if( (row < default_table_height) && (column < default_table_width) )
		return &m_table[row][column];
	return 0;
}

ChEngn::Piece* ChEngn::Table::pieceAtC(char column, char row) const
{
	return pieceAt( column -'a', row - '1');
}
void ChEngn::Table::getMemoryForTable()
{
	if( 0 != m_table )
		return;
	m_table = new Piece*[default_table_height];
	for ( unsigned int i = 0; i < default_table_height; i++ )
		m_table[i] = new Piece[default_table_width];
}

void ChEngn::Table::fillDefault()
{
	assert( 0 != m_table );
	for ( unsigned int i = 0; i < default_table_height; i++ )
	{
		for (unsigned int  j = 0; j < default_table_width; j++ )
			m_table[i][j] = Piece();
	}
}

void ChEngn::Table::cleanMemory()
{
	assert( 0 != m_table );
	for ( unsigned int i = 0; i < default_table_height; i++ )
		delete m_table[i];
	delete []m_table;
}

void ChEngn::Table::resetComplect()
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

void ChEngn::Table::operator = (const ChEngn::Table &other)
{
//	cleanMemory();
	getMemoryForTable();
	for ( unsigned int i = 0; i < default_table_height; i++ )
		for (unsigned int j = 0; j < default_table_width; j++)
			m_table[i][j] = *other.pieceAt(i, j);
}

namespace ChEngn
{
	std::ostream& operator << (std::ostream &out, const Table& tbl)
	{
		for ( unsigned int i = default_table_height -1 ; i != -1; i-- )
		{
			out<<std::endl<< i + 1<< " ";
			for (unsigned int  j = 0; j < default_table_width; j++ )
				out<< (*tbl.pieceAt(i, j));
		}
		out<<std::endl<<"  ";
		for ( unsigned int i = 0; i < default_table_width; i++)
			out<<char('a'+i);
		return out;
	}
};
