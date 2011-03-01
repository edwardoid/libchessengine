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
	if( m_currentMoveIt != m_moves.end() )
			if( makePly( m_currentMoveIt->white(), true) && makePly( m_currentMoveIt->black(), false) )
			{
				m_currentMoveIt++;
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
		return makeKnightPly(pl, isWhite);

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
	pgn::Square newPos = ply->toSquare();
	if(ply->isCapture())
	{
		char specifiedCol = ply->toSquare().col() -1 ;

		if ( ply->fromSquare() != '-' )
			specifiedCol = ply->fromSquare();

		pgn::Square oldPos(	specifiedCol, ply->toSquare().row() );
		Piece *movedPiece = m_table.pieceAtC( oldPos.col(), oldPos.row() );

		if( (movedPiece == 0 ) || (movedPiece->type() != pawn) )
		{
			oldPos = pgn::Square( char (ply->toSquare().col() + 1) , newPos.row());
			movedPiece = m_table.pieceAtC( oldPos.col(), oldPos.row() );
		}
		if ( movedPiece != 0 )
		{
			Piece *dest = m_table.pieceAtC(newPos.col(), newPos.row() );
			if( dest != 0 )
				if( dest->type() != unknown )
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
	else
	{
		pgn::Square oldPos(newPos.col(), newPos.row() - coef);
		Piece* movedPiece = m_table.pieceAtC(oldPos.col(), oldPos.row());
		if( (movedPiece == 0) || (movedPiece->type() != pawn) || (movedPiece->isWhite() != isWhite) )
		{
			oldPos = pgn::Square(newPos.col(), newPos.row() - 2*coef);
			movedPiece = m_table.pieceAtC(oldPos.col(), oldPos.row());
		}
		if( movedPiece != 0 )
		{
			if( (movedPiece->type() == pawn ) && (movedPiece->isWhite() == isWhite) && (movedPiece->isWhite() == isWhite) )
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

bool ChEngn::Engine::makeKnightPly( const pgn::Ply* ply, bool isWhite)
{
	
	pgn::Square newPos = ply->toSquare();
	char row = 0;
	char column = 0;
	if ( ply->fromSquare() != '-');
	else if ( (ply->fromSquare() >= 'a') && (ply->fromSquare() <= 'h') )
		column = ply->fromSquare();
	else if ( (ply->fromSquare() >= '1') && (ply->fromSquare() <= '8') )
		row = ply->fromSquare();
	pgn::Square oldPos;
	
	oldPos = pgn::Square(newPos.col() - 1, newPos.row() -2);
	if ( column != 0 )
		oldPos = pgn::Square(column, newPos.row() -2);
	else if ( row != 0 )
		oldPos = pgn::Square( newPos.col() -1 , row);

	pgn::Square oldPosS, oldPosT;

	Piece *movedPieceS, *movedPieceT;
	Piece *tmp = m_table.pieceAtC( oldPos.col(), oldPos.row());
	if( ( tmp != 0 ) && ( tmp->type() == knight ) && ( tmp->isWhite() == isWhite ) )
	{
		if ( ( column == oldPos.col() ) || ( row = oldPos.row() ) )
		{
			movedPieceS = tmp;
			oldPosS = oldPos;
		}
		else
		{
			movedPieceT = tmp;
			oldPosT = oldPos;
		}
	}

	oldPos = pgn::Square(newPos.col() - 1, newPos.row() +2);
	if ( column != 0 )
		oldPos = pgn::Square(column, newPos.row() +2);
	else if ( row != 0 )
		oldPos = pgn::Square( newPos.col() -1 , row);

	tmp = m_table.pieceAtC( oldPos.col(), oldPos.row());
	if( ( tmp != 0 ) && ( tmp->type() == knight ) && ( tmp->isWhite() == isWhite ) )
	{
		if ( ( column == oldPos.col() ) || ( row = oldPos.row() ) )
		{
			movedPieceS = tmp;
			oldPosS = oldPos;
		}
		else
		{
			movedPieceT = tmp;
			oldPosT = oldPos;
		}	
	}


	oldPos = pgn::Square(newPos.col() + 1, newPos.row() -2);
	if ( column != 0 )
		oldPos = pgn::Square(column, newPos.row() -2);
	else if ( row != 0 )
		oldPos = pgn::Square( newPos.col() +1 , row);

	tmp = m_table.pieceAtC( oldPos.col(), oldPos.row());
	if( ( tmp != 0 ) && ( tmp->type() == knight ) && ( tmp->isWhite() == isWhite ) )
	{
		if ( ( column == oldPos.col() ) || ( row = oldPos.row() ) )
		{
			movedPieceS = tmp;
			oldPosS = oldPos;
		}
		else
		{
			movedPieceT = tmp;
			oldPosT = oldPos;
		}
			
	}

	oldPos = pgn::Square(newPos.col() + 1, newPos.row() +2);
	if ( column != 0 )
		oldPos = pgn::Square(column, newPos.row() +2);
	else if ( row != 0 )
		oldPos = pgn::Square( newPos.col() +1 , row);

	tmp = m_table.pieceAtC( oldPos.col(), oldPos.row());
	if( ( tmp != 0 ) && ( tmp->type() == knight ) && ( tmp->isWhite() == isWhite ) )
	{
		if ( ( column == oldPos.col() ) || ( row = oldPos.row() ) )
		{
			movedPieceS = tmp;
			oldPosS = oldPos;
		}
		else
		{
			movedPieceT = tmp;
			oldPosT = oldPos;
		}
			
	}	

	oldPos = pgn::Square(newPos.col() - 2, newPos.row() -1);
	if ( column != 0 )
		oldPos = pgn::Square(column, newPos.row() -1);
	else if ( row != 0 )
		oldPos = pgn::Square( newPos.col() -2 , row);

	tmp = m_table.pieceAtC( oldPos.col(), oldPos.row());
	if( ( tmp != 0 ) && ( tmp->type() == knight ) && ( tmp->isWhite() == isWhite ) )
	{
		if ( ( column == oldPos.col() ) || ( row = oldPos.row() ) )
		{
			movedPieceS = tmp;
			oldPosS = oldPos;
		}
		else
		{
			movedPieceT = tmp;
			oldPosT = oldPos;
		}
	}

	oldPos = pgn::Square(newPos.col() - 2, newPos.row() +1);
	if ( column != 0 )
		oldPos = pgn::Square(column, newPos.row() +1);
	else if ( row != 0 )
		oldPos = pgn::Square( newPos.col() -2 , row);

	tmp = m_table.pieceAtC( oldPos.col(), oldPos.row());
	if( ( tmp != 0 ) && ( tmp->type() == knight ) && ( tmp->isWhite() == isWhite ) )
	{
		if ( ( column == oldPos.col() ) || ( row = oldPos.row() ) )
		{
			movedPieceS = tmp;
			oldPosS = oldPos;
		}
		else
		{
			movedPieceT = tmp;
			oldPosT = oldPos;
		}	
	}


	oldPos = pgn::Square(newPos.col() + 2, newPos.row() -1);
	if ( column != 0 )
		oldPos = pgn::Square(column, newPos.row() -1);
	else if ( row != 0 )
		oldPos = pgn::Square( newPos.col() +2 , row);

	tmp = m_table.pieceAtC( oldPos.col(), oldPos.row());
	if( ( tmp != 0 ) && ( tmp->type() == knight ) && ( tmp->isWhite() == isWhite ) )
	{
		if ( ( column == oldPos.col() ) || ( row = oldPos.row() ) )
		{
			movedPieceS = tmp;
			oldPosS = oldPos;
		}
		else
		{
			movedPieceT = tmp;
			oldPosT = oldPos;
		}
			
	}

	oldPos = pgn::Square(newPos.col() + 2, newPos.row() +1);
	if ( column != 0 )
		oldPos = pgn::Square(column, newPos.row() +1);
	else if ( row != 0 )
		oldPos = pgn::Square( newPos.col() +2 , row);

	tmp = m_table.pieceAtC( oldPos.col(), oldPos.row());
	if( ( tmp != 0 ) && ( tmp->type() == knight ) && ( tmp->isWhite() == isWhite ) )
	{
		if ( ( column == oldPos.col() ) || ( row = oldPos.row() ) )
		{
			movedPieceS = tmp;
			oldPosS = oldPos;
		}
		else
		{
			movedPieceT = tmp;
			oldPosT = oldPos;
		}
			
	}

	
	Piece* movedPiece;
	if ( ( column != 0 ) || ( row != 0 ) )
	{
		movedPiece = movedPieceS;
		oldPos = oldPosS;
	}
	else
	{
		movedPiece = movedPieceT;
		oldPos = oldPosT;
	}

	Piece *dest = m_table.pieceAtC( newPos.col(), newPos.row() );

	if ( ( movedPiece != 0) && ( dest != 0 ) )
	{
		if ( ( (ply->isCapture()) && (dest->type() != unknown) && (dest->isWhite() == isWhite) )
			|| 
		 ( (dest->type() == unknown) && (! ply->isCapture() )  ) )
		 {
			dest->setType ( knight );
			if( isWhite )
				dest->setWhite();
			else
				dest->setBlack();
			movedPiece->setType( unknown );
			return true;
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
