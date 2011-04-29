//
// Copyright (C) 2002 Edward Sarkisyan <edward.sarkisyan@gmail.com>
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
#include <PGNPly.h>
#include <stdlib.h>
#include <iostream>

ChEngn::Engine::Engine()
{
	m_currentMoveIt = m_moves.begin();
}

ChEngn::Engine::Engine(const Engine &other)
{
	m_halfMove = false;
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
	if( m_currentMoveIt != m_moves.end() )
		if( makePly( m_currentMoveIt->white(), true) && makePly( m_currentMoveIt->black(), false) )
		{
			m_currentMoveIt++;
				return true;
		}
	return false;
}

bool ChEngn::Engine::makeNextHalfMove()
{
	if ( m_currentMoveIt != m_moves.end() )
	if ( m_halfMove)
	{
		m_halfMove = false;
		bool res = makePly( m_currentMoveIt->black() , false);
		m_currentMoveIt++;
		return res;
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
	
	if ( pl->isLongCastle() )
		makeLongCastling(isWhite);

	if ( (pl->piece()) == pgn::Piece::Pawn() )
		makePawnPly(pl, isWhite);

	if ( (pl->piece()) == pgn::Piece::Knight() )
		makeKnightPly(pl, isWhite);

	if ( (pl->piece()) == pgn::Piece::Bishop() )
		makeBishopPly(pl, isWhite);

	if ( (pl->piece()) == pgn::Piece::Rook() )
		makeRookPly(pl, isWhite);

	if ( (pl->piece()) == pgn::Piece::Queen() )
		makeQueenPly(pl, isWhite);

	if ( (pl->piece()) == pgn::Piece::King() )
		makeKingPly(pl, isWhite);

	return true;
}

void ChEngn::Engine::makePawnPly( const  pgn::Ply* ply, bool isWhite)
{
	short coef = (isWhite? 1 : -1);
	pgn::Square newPos = ply->toSquare();
	if(ply->isCapture())
	{
		Piece *movedPiece = 0;
		Piece *dest = m_table.pieceAtC( newPos.col() , newPos.row() );

		if ( ( dest == 0 ) )
			throw BadMove( *ply, DEST_OUT_OF_RANGE );

		char specifiedCol = ply->fromSquare();
		if ( specifiedCol != '-')
		{
			pgn::Square oldPos(specifiedCol, newPos.row() - coef);
			movedPiece = m_table.pieceAtC(oldPos.col(), oldPos.row());
			if ( movedPiece->type() != pawn )
				throw BadMove( *ply, "Specified piece is not pawn");
			if ( movedPiece->isWhite() != isWhite )
				throw BadMove( *ply, "Specified piece's color and movind piece's color are not same");
		}
		else
		{
			Piece *tmp = m_table.pieceAtC ( newPos.col() - 1, newPos.row() - coef );
			
			if ( ( tmp != 0 ) && (tmp->type() == pawn) && (tmp->isWhite() == isWhite) )
				movedPiece == tmp;
			else
			{
				tmp = m_table.pieceAtC ( newPos.col() + 1, newPos.row() - coef );
				if ( ( tmp != 0 ) && (tmp->type() == pawn) && (tmp->isWhite() == isWhite) )
					movedPiece == tmp;
			}
		}

		if ( movedPiece != 0 )
		{
			if ( dest->type() == unknown )
			{
				Piece *longDest = m_table.pieceAtC(newPos.col(), newPos.row() - coef);
				if ( ( longDest != 0 ) &&
					 ( longDest->isWhite() != isWhite) &&
					 ( longDest->type() == pawn ) )
					 longDest->setType( unknown );
			}
			(*dest) = (*movedPiece);
			movedPiece->setType(unknown);
			if( ply->promoted() != 0 )
			{
				piece_type tmpType = guessTypeByChar( ply->promoted()->id() ); 
				if ( ( tmpType != pawn ) && ( tmpType != king ) )
					dest->setType( tmpType );				
			}
			return;
		}
	}
	else 
	{
		pgn::Square oldPos(newPos.col(), newPos.row() - coef);
		Piece* movedPiece = m_table.pieceAtC(oldPos.col(), oldPos.row());
		if( (movedPiece == 0) || 
		    (movedPiece->type() != pawn) || 
		    (movedPiece->isWhite() != isWhite) )
		{
			oldPos = pgn::Square(newPos.col(), newPos.row() - 2 * coef);
			movedPiece = m_table.pieceAtC(oldPos.col(), oldPos.row());
		}
		if( movedPiece != 0 )
		{
			if( (movedPiece->type() == pawn ) && 
				(movedPiece->isWhite() == isWhite) )
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
						if( ply->promoted() != 0 )
						{
							piece_type tmpType = guessTypeByChar( ply->promoted()->id() ); 
							if ( ( tmpType != pawn ) && ( tmpType != king ) )
								dest->setType( tmpType );
						}
						return;
					}
					else
						throw BadMove( *ply, DEST_OUT_OF_RANGE );
				else
					throw BadMove( *ply, DEST_OUT_OF_RANGE );

			}
			else
				throw BadMove( *ply, UNKNOWN_ERROR );
		}
	}
}

void ChEngn::Engine::makeKnightPly( const pgn::Ply* ply, bool isWhite)
{
	
	pgn::Square newPos = ply->toSquare();
	char row = 0;
	char column = 0;
	if ( ply->fromSquare() == '-');
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
		if ( ( (ply->isCapture()) && (dest->type() != unknown) )
			|| 
		 ( (dest->type() == unknown) && (! ply->isCapture() )  ) )
		 {
			dest->setType ( knight );
			if( isWhite )
				dest->setWhite();
			else
				dest->setBlack();
			movedPiece->setType( unknown );
			return;
		}
	}
	throw BadMove( *ply, UNKNOWN_ERROR );
}

void ChEngn::Engine::makeBishopPly( const pgn::Ply *ply, bool isWhite)
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
	{
		if ( tmp == 0 ) 
			throw BadMove( *ply, DEST_OUT_OF_RANGE );

		if ( tmp->isWhite() == isWhite )
			throw BadMove( *ply, SAME_COLOR );

		if ( tmp->type() == unknown )
			throw BadMove( *ply, UNKNOWN_CAPTURE );
	}

	if ( ( movedPiece != 0 ) && (tmp != 0 ) )
	{
		tmp->setType ( bishop );
		if( isWhite )
			tmp->setWhite();
		else
			tmp->setBlack();
		movedPiece->setType( unknown );
		return;
	}
	throw BadMove( *ply, UNKNOWN_ERROR );
}


void ChEngn::Engine::makeRookPly( const pgn::Ply* ply, bool isWhite)
{
	pgn::Square newPos = ply->toSquare();
	Piece *dest = m_table.pieceAtC( newPos.col() , newPos.row() );
	Piece *movedPiece = 0;

	char end='h';

	if ( ( ply->fromSquare() >= 'a') && ( ply->fromSquare() <= 'h') )
		end = ply->fromSquare();

	char tmpRow = newPos.row();
	for (char i = 'a'; i<= end ; i++)
	{
		Piece* tmp = m_table.pieceAtC(i, newPos.row() );
		if( ( tmp != 0 ) &&
			( tmp->type() == rook ) &&
			( tmp->isWhite() == isWhite )  &&
			checkForEmptynessH( i,
								newPos.col(),
								newPos.row() ,
								&m_table) )
		{
			movedPiece = tmp;
		}
	}

	end='8';

	char tmpCol = newPos.col();
	if ( ( ply->fromSquare() >= '1') && ( ply->fromSquare() <= '8') )
		end = ply->fromSquare();
	
	for (char i = '1'; i<= end ; i++)
	{
		Piece* tmp = m_table.pieceAtC(newPos.col(), i );
		if( ( tmp != 0 ) &&
			( tmp->type() == rook ) && 
			( tmp->isWhite() == isWhite ) &&
			( movedPiece == 0 ) &&
			checkForEmptynessV( i,
								newPos.row() ,
		  						newPos.col(),
								&m_table) ) 
		{
			movedPiece = tmp;
		}
	}

	if ( ( movedPiece != 0 ) && (dest != 0 ) )
	{
		if ( ply->isCapture() && ( dest->type() == unknown ) )
			throw BadMove( *ply, UNKNOWN_CAPTURE );
		(*dest) = (*movedPiece);
		dest->setMoved();
		movedPiece->setType(unknown);
		return;
		
	}
	throw BadMove( *ply, UNKNOWN_ERROR );
}

void ChEngn::Engine::makeQueenPly( const pgn::Ply* ply, bool isWhite)
{
	pgn::Square newPos = ply->toSquare();

	Piece *dest = m_table.pieceAtC( newPos.col() , newPos.row() );

	if(dest == 0 )
		throw BadMove( *ply, DEST_OUT_OF_RANGE );

	if ( ply->isCapture())
		if ( dest->type() == unknown)
			throw BadMove( *ply, UNKNOWN_CAPTURE );
	Piece *movedPiece = 0;


	for ( char c = 'a'; c <= 'h'; c++ )
		for ( char r = '1'; r<= '8'; r++)
		{
			Piece *tmp = m_table.pieceAtC( c, r );
			if ( (movedPiece == 0) && ( tmp != 0 ) && (tmp->type() == queen ) && (tmp->isWhite() == isWhite) )
			{
				movedPiece = tmp;
				break;
			}
		}

		if ( movedPiece != 0 )
		{
			(*dest) = (*movedPiece);
			movedPiece->setType( unknown );
			return;
		}
	throw BadMove( *ply, UNKNOWN_ERROR );
}

void ChEngn::Engine::makeLongCastling( bool isWhite)
{
	char kingCol = 'e';
	char row = (isWhite? '1': '8');
	char rookCol = 'a';

	Piece *kingPiece = m_table.pieceAtC( kingCol, row);
	Piece *rookPiece = m_table.pieceAtC( rookCol, row);
	
	Piece *newKingPiece = m_table.pieceAtC('c', row);
	Piece *newRookPiece = m_table.pieceAtC('d', row);

	if ( ( newRookPiece != 0 ) && ( newKingPiece != 0 ) )
	{
		(*newKingPiece) = (*kingPiece);
		(*newRookPiece) = (*rookPiece);
		newKingPiece->setMoved();
		newRookPiece->setMoved();
		kingPiece->setType( unknown );
		rookPiece->setType( unknown );
		return;
	}
	throw BadMove( pgn::Ply("O-O-O") , UNKNOWN_ERROR );
		 
}

void ChEngn::Engine::makeKingPly( const pgn::Ply* ply, bool isWhite)
{
	pgn::Square newPos = ply->toSquare();
	char beginR = newPos.row() - 1;
	char beginC = newPos.col() - 1;
	char endR   = newPos.row() + 1;
	char endC   = newPos.col() + 1;

	Piece *dest = m_table.pieceAtC( newPos.col() , newPos.row() );
	
	if ( dest == 0 )
		throw BadMove( *ply, DEST_OUT_OF_RANGE );
	if ( dest->type() == king )
		throw BadMove( *ply, "King can't make move to other king" );
		

	for ( char c = beginC; c <= endC; c++) 
		for ( char r = beginR; r<= endR; r++ )
		{
			Piece *movedPiece = m_table.pieceAtC( c, r );
			if ( ( movedPiece != 0 ) &&
				 ( movedPiece->type() == king ) &&
				 ( movedPiece->isWhite() == isWhite )
				 )
			{
				( *dest ) = ( *movedPiece );
				movedPiece->setType( unknown );
				return;
			}
		}
	throw BadMove( *ply, UNKNOWN_ERROR );
}

void ChEngn::Engine::makeShortCastling( bool isWhite)
{
	char kingCol = 'e';
	char row = (isWhite? '1': '8');
	char rookCol = 'h';

	Piece *kingPiece = m_table.pieceAtC( kingCol, row);
	Piece *rookPiece = m_table.pieceAtC( rookCol, row);
	Piece *newKingPiece = m_table.pieceAtC('g', row);
	Piece *newRookPiece = m_table.pieceAtC('f', row);

	if ( ( newRookPiece != 0 ) && ( newKingPiece != 0 ) )
	{
		(*newKingPiece) = (*kingPiece);
		(*newRookPiece) = (*rookPiece);
		newKingPiece->setMoved();
		newRookPiece->setMoved();
		kingPiece->setType( unknown );
		rookPiece->setType( unknown );
		return;
	}
	throw BadMove( pgn::Ply("O-O"), UNKNOWN_ERROR );
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
	if ( ( from < ( default_table_width - 'a') ) && 
		 ( to < ( default_table_width - 'a') ) && 
		 ( row < ( default_table_height - '1' ) ) &&
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
	if ( ( from < ( default_table_width - '1') ) &&
			( to < ( default_table_width - '1') ) &&
			( column< ( default_table_height - 'a' ) ) &&
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

ChEngn::piece_type ChEngn::Engine::guessTypeByChar( const char character )
{
	if( ( character == 'P') || ( character == '-') || ( character == 'p' ) )
		return pawn;

	if ( ( character == 'N' ) || ( character == 'n' ) )
		 return knight;

	if ( ( character == 'B' ) || ( character == 'b' ) )
		 return bishop;

	if ( ( character == 'R' ) || ( character == 'r' ) )
		 return rook;

	if ( ( character == 'Q' ) || ( character == 'q' ) )
		 return queen;

	if ( ( character == 'k' ) || ( character == 'K' ) )
		 return king;
	
	return unknown;
}
