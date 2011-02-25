#include "CETable.h"

ChEngn::Table::Table()
{
	m_size.height = default_table_height;
	m_size.width  = default_table_width;
	getMemoryForTable();
}

ChEngn::Table::Table(const Table &other)
{
	m_size.height = other.height();
	m_size.width  = other.width();
	getMemoryForTable();
	for (unsigned int i = 0; i < m_size.height; i++ )
		for (unsigned int j = 0; j< m_size.width; j++)
				m_table[i][j] = other.pieceAt(i, j);
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

ChEngn::Piece ChEngn::Table::pieceAt(unsigned int row, unsigned int column) const
{
	if( (row < m_size.width) && (column < m_size.height) )
		return m_table[row][column];
	return Piece();
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
}


namespace ChEngn
{
	std::ostream& operator << (std::ostream &out, const Table& tbl)
	{
		for ( unsigned int i = 0; i < tbl.height(); i++ )
		{
			out<<std::endl;
			for (unsigned int  j = 0; j < tbl.width(); j++ )
				out<<tbl.pieceAt(i, j);
		}
		return out;
	}
};
