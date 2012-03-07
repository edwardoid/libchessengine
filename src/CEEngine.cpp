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

ChEngn::Engine::Engine()
{
	m_currentMoveIt = m_moves.begin();
}

ChEngn::Engine::Engine(const ChEngn::Engine &other)
{
	m_halfMove = false;
	m_currentMoveIt = m_moves.begin();
}

ChEngn::Engine::Engine(const pgn::Game &gm)
{
	m_moves = gm.moves();
	m_currentMoveIt = m_moves.begin();
	m_halfMove = false;
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
	try
	{
		bool whitePlyRes = makeNextHalfMove();
		bool blackPlyRes = makeNextHalfMove();
		return ( whitePlyRes && blackPlyRes );
	}
	catch( BadMove e )
	{
		if( ( m_currentMoveIt == m_moves.end() ) && m_halfMove )
			return false;
		else
			throw e;
	}
	
	return false;
}

bool ChEngn::Engine::makeNextHalfMove()
{
	if ( m_currentMoveIt != m_moves.end() )
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

bool ChEngn::Engine::makeMove( pgn::Move& move)
{
	return ( makePly( move.white(), true ) && makePly( move.black(), false ) );
}

bool ChEngn::Engine::makePly( const pgn::Ply* pl, bool isWhite )
{

	if ( pl == 0 )
	{
		std::cerr << "Engine: can't make move: given ply is NULL. Color: "
				  << ( isWhite? "white" : "black" ) << std::endl;
		return false;
	}
	
	if ( pl->isShortCastle() )
		makeShortCastling(isWhite);
	
	else if ( pl->isLongCastle() )
		makeLongCastling(isWhite);

	else if ( (pl->piece()) == pgn::Piece::Pawn() )
		makePawnPly(pl, isWhite);

	else if ( (pl->piece()) == pgn::Piece::Knight() )
		makeKnightPly(pl, isWhite);

	else if ( (pl->piece()) == pgn::Piece::Bishop() )
		makeBishopPly(pl, isWhite);

	else if ( (pl->piece()) == pgn::Piece::Rook() )
		makeRookPly(pl, isWhite);

	else if ( (pl->piece()) == pgn::Piece::Queen() )
		makeQueenPly(pl, isWhite);

	else if ( (pl->piece()) == pgn::Piece::King() )
		makeKingPly(pl, isWhite);

	return true;
}

void ChEngn::Engine::makePawnPly( const  pgn::Ply* ply, bool isWhite)
{
	PawnMove pM(ply, isWhite);
	if(!pM.make(&m_table))
	{
		throw BadMove( *ply, CAN_T_FIND_MOVED_PIECE);
	}
}

void ChEngn::Engine::makeKnightPly( const pgn::Ply* ply, bool isWhite)
{
	KnightMove kM(ply, isWhite);	
	if(!kM.make(&m_table))
	{
		throw BadMove( *ply, CAN_T_FIND_MOVED_PIECE);
	}
}

void ChEngn::Engine::makeBishopPly( const pgn::Ply *ply, bool isWhite)
{
    BishopMove bM(ply, isWhite);
    if(!bM.make(&m_table))
    {
		throw BadMove( *ply, CAN_T_FIND_MOVED_PIECE);
    }
    return;
}


void ChEngn::Engine::makeRookPly( const pgn::Ply* ply, bool isWhite)
{
	RookMove rM(ply, isWhite);
    if(!rM.make(&m_table))
    {
		throw BadMove( *ply, CAN_T_FIND_MOVED_PIECE);
    }
    return;
}

void ChEngn::Engine::makeQueenPly( const pgn::Ply* ply, bool isWhite)
{
    QueenMove qM(ply, isWhite);
    if(!qM.make(&m_table))
    {
		throw BadMove( *ply, CAN_T_FIND_MOVED_PIECE);
    }
    return;
}

void ChEngn::Engine::makeKingPly( const pgn::Ply* ply, bool isWhite)
{
    KingMove kM(ply, isWhite);
    if(!kM.make(&m_table))
    {
		throw BadMove( *ply, CAN_T_FIND_MOVED_PIECE);
    }
    return;

}

void ChEngn::Engine::makeShortCastling( bool isWhite)
{
	ShortCastleMove scM(isWhite);
    if(!scM.make(&m_table))
    {
		throw BadMove( pgn::Ply("O-O"), CAN_T_FIND_MOVED_PIECE);
    }
    return;


	throw BadMove( pgn::Ply("O-O"), UNKNOWN_ERROR );
}

void ChEngn::Engine::makeLongCastling( bool isWhite)
{
    LongCastleMove lcM(isWhite);
    if(!lcM.make(&m_table))
    {
		throw BadMove( pgn::Ply("O-O-O"), CAN_T_FIND_MOVED_PIECE);
    }
    return;
}

namespace ChEngn
{
	std::ostream& operator << ( std::ostream& out, const Engine& engn)
	{
		return out<<engn.getVirtualTable();
	}
};
