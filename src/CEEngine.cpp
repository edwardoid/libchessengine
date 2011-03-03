#include "CEEngine.h"
#include <PGNPly.h>
#include <stdlib.h>

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
		return makeBishopPly(pl, isWhite);

	if ( (pl->piece()) == pgn::Piece::Rook() )
		return makeRookPly(pl, isWhite);

	if ( (pl->piece()) == pgn::Piece::Queen() )
		return makeQueenPly(pl, isWhite);

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

bool ChEngn::Engine::makeBishopPly( const pgn::Ply *ply, bool isWhite)
{
	pgn::Square newPos = ply->toSquare();
	Piece *movedPiece = 0;
	for( char  i = 'a'; i <= 'h'; i++ )
		for ( char j = '1'; j <= '8'; j++)
		{
			Piece *tmp = m_table.pieceAtC(i, j);
			if( ( tmp != 0 ) && ( tmp->type() == bishop) &&
				( tmp->isWhite() == isWhite) &&
				( abs( i - newPos.col()) == abs( j - newPos.row() ) ) )
				  if( ply->fromSquare() == '-' )
				  {
				  		movedPiece = tmp;
				  }
				  else
				  {
				  	if( (ply->fromSquare() >= 'a') && (ply->fromSquare() <= 'h') && ( i == ply->fromSquare() ) )
				  		movedPiece = tmp;
				  	if( (ply->fromSquare() >= '1') && (ply->fromSquare() <= '8') && ( i == ply->fromSquare() ) )
				  		movedPiece = tmp;
				  }
		}

		
	Piece* tmp = m_table.pieceAtC( newPos.col() , newPos.row() );

	if ( ply->isCapture() )
		if( (tmp == 0) || (tmp->isWhite() == isWhite) || (tmp->type() == unknown) )
			return false;
	if ( ( movedPiece != 0 ) && (tmp != 0 ) )
	{
		tmp->setType ( bishop );
		if( isWhite )
			tmp->setWhite();
		else
			tmp->setBlack();
		movedPiece->setType( unknown );
		return true;
	}
	return false;
}


bool ChEngn::Engine::makeRookPly( const pgn::Ply* ply, bool isWhite)
{
	pgn::Square newPos = ply->toSquare();
	Piece *dest = m_table.pieceAtC( newPos.col() , newPos.row() );
	Piece *movedPiece = 0;

	char end='h';

	if ( ( ply->fromSquare() >= 'a') && ( ply->fromSquare() <= 'h') )
		end = ply->fromSquare();
	
	for (int i = 'a'; i<= end ; i++)
	{
		Piece* tmp = m_table.pieceAtC(i, newPos.row() );
		if( ( movedPiece != 0 ) && ( movedPiece->type() == rook ) && ( movedPiece->isWhite() == isWhite ) )
		{
			movedPiece = tmp;
		}
	}

	end='8';

	if ( ( ply->fromSquare() >= '1') && ( ply->fromSquare() <= '8') )
		end = ply->fromSquare();
	
	for (int i = '1'; i<= end ; i++)
	{
		Piece* tmp = m_table.pieceAtC(i, newPos.col() );
		if( ( movedPiece != 0 ) && ( movedPiece->type() == rook ) && ( movedPiece->isWhite() == isWhite ) ) 
		{
			movedPiece = tmp;
		}
	}

	if ( ( movedPiece != 0 ) && (dest != 0 ) )
	{
		if ( ply->isCapture() && ( dest->type() == unknown ) )
			return false;
		(*dest) = (*movedPiece);
		dest->setMoved();
		movedPiece->setType(unknown);
		return true;
		
	}
	return false;
}

bool ChEngn::Engine::makeQueenPly( const pgn::Ply* ply, bool isWhite)
{
	pgn::Square newPos = ply->toSquare();

	Piece *dest = m_table.pieceAtC( newPos.col() , newPos.row() );

	if(dest == 0 )
		return false;

	if ( ply->isCapture())
		if ( dest->type() == unknown)
			return false;
	Piece *movedPiece = 0;


	for ( char c = 'a'; c <= 'h'; c++ )
		for ( char r = '1'; r<= '8'; r++)
		{
			Piece *tmp = m_table.pieceAtC( c, r );
			if ( ( tmp != 0 ) && (tmp->type() == queen ) && (tmp->isWhite() == isWhite) )
			{
				movedPiece = tmp;
				break;
			}
		}

		if ( movedPiece != 0 )
		{
			(*dest) = (*movedPiece);
			movedPiece->setType( unknown );
			return true;
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


bool ChEngn::Engine::checkForEmptynessH(char from, char to, char row, VirtualTable *table)
{
	if ( table == 0 )
		return false;
	if ( from > to)
	{
		char tmp = from;
		from = to;
		to = tmp;
	}
	if ( ( from < ( table->width() - 'a') ) && 
		 ( to < ( table->width() - 'a') ) && 
		 ( row < ( table->height() - '1' ) ) &&
		 ( from > 0) &&
		 ( to > 0 ))
	{
		for ( char i = from + 1; i < to; i++)
		{
			if ( table->pieceAtC(i, row)->type() != unknown)
				return false;
		}
	}
	else
		return false;
	return true;
}

bool ChEngn::Engine::checkForEmptynessV(char from, char to, char column, VirtualTable *table)
{
	if ( table == 0 )
		return false;
	if ( from > to)
	{
		char tmp = from;
		from = to;
		to = tmp;
	}
	if ( ( from < ( table->width() - '1') ) &&
			( to < ( table->width() - '1') ) &&
			( column< ( table->height() - 'a' ) ) &&
			( to > 0) &&
			(from > 0 ))
	{
		for ( char i = from + 1; i < to; i++)
		{
			if ( table->pieceAtC(column, i)->type() != unknown)
				return false;
		}
	}
	else
		return false;
	return true;
}

bool ChEngn::Engine::checkForEmptynessDiagonal(char fromC, char fromR, char toC, char toR, VirtualTable *table)
{
	char stepC = 1;
	char stepR = 1;

	if ( fromC > toC )
		stepC = -1;

	if ( fromR > toR )
		stepR = -1;

	char incC = 0;
	char incR = 0;
	for ( int r = fromR + stepR; r < toR; r+= stepR )
	{
		incR++;
		for ( int c = fromC + stepC; c < toC; c+=stepC)
		{
			incC++;
			if( incR == incC)
			{
				Piece* tmp = table->pieceAtC(c, r);
				if ( (tmp == 0) || (tmp->type() != unknown) )
					return false;
			}
		}
	}

	return true;
}
