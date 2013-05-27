//
// Copyright (C) 2011 Edward Sarkisyan <edward.sarkisyan@gmail.com>
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

#include "CEEngine.h"
#include "CEException.h"
#include "CEPawnMove.h"
#include "CEKnightMove.h"
#include "CEBishopMove.h"
#include "CERookMove.h"
#include "CEQueenMove.h"
#include "CEKingMove.h"
#include "CEShortCastleMove.h"
#include "CELongCastleMove.h"
#include <PGNPly.h>
#include <stdlib.h>
#include <iostream>
#include <assert.h>

CE::Engine::Engine()
{
	m_currentMoveIt = m_moves.begin();
}

CE::Engine::Engine(const CE::Engine &other)
{
	m_halfMove = false;
	m_currentMoveIt = m_moves.begin();
}

CE::Engine::Engine(const pgn::Game &gm)
{
	m_moves = gm.moves();
	m_currentMoveIt = m_moves.begin();
	m_halfMove = false;
}

CE::Engine::~Engine()
{
}

pgn::MoveList* CE::Engine::moves()
{
	return &m_moves;
}

CE::VirtualTable CE::Engine::getVirtualTable() const
{
	return m_table;
}

pgn::MoveList::iterator CE::Engine::nextMove()
{
	return m_currentMoveIt;
}

bool CE::Engine::makeNextMove()
{
	if (!(m_currentMoveIt < m_moves.end())) return false;
	
	try
	{
		bool whitePlyRes = makeNextHalfMove();
		if(!(m_currentMoveIt < m_moves.end()))
			return true;
		bool blackPlyRes = makeNextHalfMove();
		return ( whitePlyRes && blackPlyRes );
	}
	catch( BadMove e )
	{
		if( !(m_currentMoveIt < m_moves.end()) && m_halfMove )
			return false;
		else
			throw e;
	}
	
	return false;
}

bool CE::Engine::makeNextHalfMove()
{
	if ( m_currentMoveIt < m_moves.end())
		if ( m_halfMove)
		{
			m_halfMove = false;
			if( 0 ==  m_currentMoveIt->black() )
				return false;
			bool res = makePly( m_currentMoveIt->black() , false);
			m_currentMoveIt++;
			return ( res && ( m_currentMoveIt != m_moves.end() ) );
		}
		else
		{	
			m_halfMove = true;
			return makePly( m_currentMoveIt->white() , true);
		}
	return false;
}

bool CE::Engine::makeMove( pgn::Move& move)
{
	return ( makePly( move.white(), true ) && makePly( move.black(), false ) );
}

bool CE::Engine::makePly( const pgn::Ply* pl, bool isWhite )
{

	if ( pl == 0 )
	{
		std::cerr << "Engine: can't make move: given ply is NULL. Color: "
				  << ( isWhite? "white" : "black" ) << std::endl;
		return false;
	}

    Move* m = NULL;
	
	if ( pl->isShortCastle() )
        m = new ShortCastleMove(isWhite);
	
	else if ( pl->isLongCastle() )
        m = new LongCastleMove(isWhite);

	else if ( (pl->piece()) == pgn::Piece::Pawn() )
        m = new PawnMove(pl, isWhite);

	else if ( (pl->piece()) == pgn::Piece::Knight() )
		m = new KnightMove(pl, isWhite);

	else if ( (pl->piece()) == pgn::Piece::Bishop() )
		m = new BishopMove(pl, isWhite);

	else if ( (pl->piece()) == pgn::Piece::Rook() )
		m = new RookMove(pl, isWhite);

	else if ( (pl->piece()) == pgn::Piece::Queen() )
		m = new QueenMove(pl, isWhite);

	else if ( (pl->piece()) == pgn::Piece::King() )
		m = new KingMove(pl, isWhite);

    if( NULL == m )
    {
        throw BadMove(*pl, NO_SUITABLE_PIECE);
    }

    if(!m->make(&m_table))
    {
        delete m;
		throw BadMove(*pl, CAN_T_FIND_MOVED_PIECE);
    }
    delete m;
	return true;
}

namespace CE
{
	std::ostream& operator << ( std::ostream& out, const Engine& engn)
	{
		return out << engn.getVirtualTable();
	}
};
