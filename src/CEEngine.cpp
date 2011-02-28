#include "CEEngine.h"
#include <PGNPly.h>

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

	std::cout<<"Make:\n"<<(*pl)<<std::endl;
	if( pl->isShortCastle() )
		return true;
	
	if ( pl->isLongCastle() )
		return true;
	if ( (pl->piece()) == pgn::Piece::Pawn() )
	{
		return makePawnPly(pl, isWhite);
	}
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

bool ChEngn::Engine::makePawnPly( const  pgn::Ply* ply, bool isWhite)
{
	short coef = (isWhite? 1 : -1);
	if(ply->isCapture())
	{
	}
	else
	{
		pgn::Square destination = ply->toSquare();
		int row = destination.row() - (coef);
		ChEngn::Piece* movedItem = m_table.pieceAt(row, ply->toSquare().col() );
		if ( movedItem != 0 )
		{
			if( movedItem->color() == ( isWhite? white: black) )
			{
				// make move
				Piece *dest = m_table.pieceAt( ply->toSquare().row(), ply->toSquare().col() );
				if ( dest != 0 )
					if( dest->type() == ChEngn::unknown)
					{
						movedItem->setMoved();
						ChEngn::Piece *tmp = movedItem;
						movedItem = dest;
						dest = movedItem;
						return true;
					}
			}
		}

		movedItem = m_table.pieceAt(row - coef, ply->toSquare().col() );
		if ( movedItem != 0 )
		{
			std::cout<<"OK!";
			if( movedItem->moveFlag() != ChEngn::moved )
			{
				if( movedItem->color() == ( isWhite? white: black) )
				{
					// make move
					Piece *dest = m_table.pieceAt( ply->toSquare().row(), ply->toSquare().col() );
					if ( dest != 0 )
						if( dest->type() == ChEngn::unknown)
						{
							movedItem->setMoved();
							ChEngn::Piece *tmp = movedItem;
							movedItem = dest;
							dest = movedItem;
							return true;
						}
				}
			}
		}
	}
	return false;
}

namespace ChEngn

{
	std::ostream& operator << ( std::ostream& out, const Engine& engn)
	{
		return out<<engn.getVirtualTable();
	}
};
