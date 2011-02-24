#include "CETable.h"

ChEngn::Table::Table()
{
	m_size.height = default_table_height;
	m_size.width  = default_table_width;
	setComplectNull();
}

ChEngn::Table::Table(const Table &other)
{
}

ChEngn::Table::~Table()
{
	for ( unsigned int i = 0; i < m_size.height; i++ )
		for (unsigned int  j = 0; j < m_size.width; j++ )
			delete m_table[i];
	delete m_table;
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

void ChEngn::Table::setComplectNull()
{
	for ( unsigned int i = 0; i < m_size.height; i++ )
		for (unsigned int  j = 0; j < m_size.width; j++ )
			m_table[i][j] = Piece();
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
				out<<tbl.pieceAt(i, j)<<std::endl;
		}
		return out;
	}
};
