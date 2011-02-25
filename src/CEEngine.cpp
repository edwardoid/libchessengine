#include "CEEngine.h"

ChEngn::Engine::Engine()
{
	m_currentMoveIt = m_moves.begin();
}

ChEngn::Engine::Engine(const Engine &other)
{
}

ChEngn::Engine::Engine(const pgn::Game &gm)
{
	m_moves = gm.moves();
	m_currentMoveIt = m_moves.begin();
}

ChEngn::Engine::~Engine()
{
}

pgn::MoveList* ChEngn::Engine::moves()
{
	return &m_moves;
}

ChEngn::VirtualTable ChEngn::Engine::getVirtualTable() const
{
	return m_table;
}

pgn::MoveList::iterator ChEngn::Engine::nextMove()
{
	return m_currentMoveIt;
}

namespace ChEngn
{
	std::ostream& operator << ( std::ostream& out, const Engine& engn)
	{
		return out<<engn.getVirtualTable();
	}
};
