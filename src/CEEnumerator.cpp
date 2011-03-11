#include <CEEnumerator.h>

ChEngn::Enumerator::Enumerator()
{
}

ChEngn::Enumerator::Enumerator( const ChEngn::Table &table, EnumerationSide enumSide, unsigned short deep )
{
}

void ChEngn::Enumerator::Enumerator::setDeep( unsigned short deep)
{
	m_deep = deep;
}

void ChEngn::Enumerator::setTable( const ChEngn::Table &table)
{
}

void ChEngn::Enumerator::setSide( EnumerationSide enumSide)
{
	m_side = enumSide;
}

unsigned short ChEngn::Enumerator::deepness() const
{
	return m_deep;
}

ChEngn::Table* ChEngn::Enumerator::Enumerator::startPosition() const
{
	return m_table;
}

ChEngn::EnumerationSide ChEngn::Enumerator::Enumerator::side() const
{
	return m_side;
}
