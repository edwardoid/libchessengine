#include "CEEnumerator.h"

CE::Enumerator::Enumerator()
{
}

CE::Enumerator::Enumerator( const CE::Table &table, EnumerationSide enumSide, unsigned short deep )
{
}

void CE::Enumerator::setDeep( unsigned short deep)
{
	m_deep = deep;
}

void CE::Enumerator::setTable( const CE::Table &table)
{
}

void CE::Enumerator::setSide( EnumerationSide enumSide)
{
	m_side = enumSide;
}

unsigned short CE::Enumerator::deepness() const
{
	return m_deep;
}

CE::Table* CE::Enumerator::startPosition() const
{
	return m_table;
}

CE::EnumerationSide CE::Enumerator::side() const
{
	return m_side;
}
