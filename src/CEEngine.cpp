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

bool ChEngn::Engine::makeNextMove()
{
	pgn::MoveList::iterator it = nextMove();
	if( it != m_moves.end() )
			return ( makePly( it->white(), true) && makePly( it->black(), false) );
	return false;
}


bool ChEngn::Engine::makeMove( pgn::Move& move)
{
	return ( makePly( move.white(), true ) && makePly( move.black(), false ) );
}

bool ChEngn::Engine::makePly( const pgn::Ply* pl, bool isWhite )
{
	if( pl->isShortCastle() )
		return true;
	
	if ( pl->isLongCastle() )
		return true;

	if ( (*(pl->promoted())) == pgn::Piece::Pawn() )
		return true;

	if ( (*(pl->promoted())) == pgn::Piece::Knight() )
		return true;

	if ( (*(pl->promoted())) == pgn::Piece::Bishop() )
		return true;

	if ( (*(pl->promoted())) == pgn::Piece::Rook() )
		return true;

	if ( (*(pl->promoted())) == pgn::Piece::Queen() )
		return true;

	if ( (*(pl->promoted())) == pgn::Piece::King() )
		return true;

	return false;
}

namespace ChEngn
{
	std::ostream& operator << ( std::ostream& out, const Engine& engn)
	{
		return out<<engn.getVirtualTable();
	}
};
