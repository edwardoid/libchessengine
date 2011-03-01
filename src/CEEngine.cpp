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
			if( makePly( it->white(), true) && makePly( it->black(), false) )
			{
				it++;
				return true;
			}
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
	if ( (pl->piece()) == pgn::Piece::Knight() )
		return true;

	if ( (pl->piece()) == pgn::Piece::Bishop() )
		return true;

	if ( (pl->piece()) == pgn::Piece::Rook() )
		return true;

	if ( (pl->piece()) == pgn::Piece::Queen() )
		return true;

	if ( (pl->piece()) == pgn::Piece::King() )
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
		int coef = ( isWhite? 1: -1);
		pgn::Square newPos = ply->toSquare();
		pgn::Square oldPos(newPos.col(), newPos.row() - coef);
		Piece* movedPiece = m_table.pieceAtC(oldPos.col(), oldPos.row());
		if( (movedPiece == 0) || (movedPiece->type() != pawn))
		{
			oldPos = pgn::Square(newPos.col(), newPos.row() - 2*coef);
			movedPiece = m_table.pieceAtC(oldPos.col(), oldPos.row());
		}
		if( movedPiece != 0 )
		{
			if( (movedPiece->type() == pawn ) && (movedPiece->isWhite() == isWhite) )
			{
				Piece *dest = m_table.pieceAtC(newPos.col(), newPos.row() );
				if( dest != 0 )
					if( dest->type() == unknown )
					{
						dest->setType( pawn );
						if( isWhite )
							dest->setWhite();
						else
							dest->setBlack();
						movedPiece->setType ( unknown );
						return true;
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
