#include "CETable.h"

ChEngn::Table::Table()
{
	m_size.height = default_table_height;
	m_size.width  = default_table_width;
	getMemoryForTable();
	resetComplect();
}

ChEngn::Table::Table(const Table &other)
{
	m_size.height = other.height();
	m_size.width  = other.width();
	getMemoryForTable();
	for (unsigned int i = 0; i < m_size.height; i++ )
		for (unsigned int j = 0; j< m_size.width; j++)
				m_table[i][j] = *other.pieceAt(i, j);
}

ChEngn::Table::~Table()
{
	cleanMemory();
}

const ChEngn::table_size ChEngn::Table::size() const
{
	return m_size;
}

const unsigned int ChEngn::Table::height() const
{
	return m_size.height;
}

const unsigned int ChEngn::Table::width() const
{
	return m_size.width;
}

ChEngn::Piece** ChEngn::Table::table()
{
	return m_table;
}

ChEngn::Piece* ChEngn::Table::pieceAt(unsigned int column, unsigned int row) const
{
	if( (row < m_size.width) && (column < m_size.height) )
		return &m_table[row][column];
	return 0;
}

ChEngn::Piece* ChEngn::Table::pieceAtC(char column, char row) const
{

	return pieceAt( column -'a', row - '1');
}
void ChEngn::Table::getMemoryForTable()
{
	m_table = new Piece*[m_size.height];
	for ( unsigned int i = 0; i < m_size.height; i++ )
		m_table[i] = new Piece[m_size.width];
}

void ChEngn::Table::fillDefault()
{
	for ( unsigned int i = 0; i < m_size.height; i++ )
	{
		for (unsigned int  j = 0; j < m_size.width; j++ )
			m_table[i][j] = Piece();
	}
}

void ChEngn::Table::cleanMemory()
{
	for ( unsigned int i = 0; i < m_size.height; i++ )
		delete []m_table[i];
	delete []m_table;
}

void ChEngn::Table::resetComplect()
{
	if ( ( m_size.height != default_table_height )
			||
		 ( m_size.width != default_table_width ) )
		 return;
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
	cleanMemory();
	m_size.height = other.height();
	m_size.width  = other.width();
	getMemoryForTable();
	for ( unsigned int i = 0; i < m_size.height; i++ )
		for (unsigned int j = 0; j < m_size.width; j++)
			m_table[i][j] = *other.pieceAt(i, j);
}

namespace ChEngn
{
	std::ostream& operator << (std::ostream &out, const Table& tbl)
	{
		for ( unsigned int i = tbl.height() -1 ; i != -1; i-- )
		{
			out<<std::endl<< i + 1<< " ";
			for (unsigned int  j = 0; j < tbl.width(); j++ )
				out<< (*tbl.pieceAt(i, j));
		}
		out<<std::endl<<"  ";
		for ( unsigned int i = 0; i < tbl.width(); i++)
			out<<char('a'+i);
		return out;
	}
};
