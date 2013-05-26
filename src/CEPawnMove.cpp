#include "CEPawnMove.h"
#include "CETable.h"
#include "CEException.h"
#include <PGNPly.h>

ChEngn::PawnMove::PawnMove(const pgn::Ply* ply, const bool isWhite)
	: ChEngn::Move(ply, isWhite)
{
	m_newPos = ply->toSquare();
}

ChEngn::PawnMove::~PawnMove()
{
}

bool ChEngn::PawnMove::make( const ChEngn::Table* table) const
{
	if(m_ply->isCapture())
		return makeCaptureMove(table);
	return makeSimpleMove(table);
}

bool ChEngn::PawnMove::makeCaptureMove( const ChEngn::Table* table) const
{
	short coef = (m_isWhite? 1 : -1);
	Piece *movedPiece = 0;
	Piece *dest = table->pieceAtC( m_newPos.col() , m_newPos.row() );

	if ( dest == 0 )
		throw BadMove( *m_ply, DEST_OUT_OF_RANGE );

	char specifiedCol = m_ply->fromSquare();
	if ( specifiedCol != '-')
	{
		pgn::Square oldPos(specifiedCol, m_newPos.row() - coef);
		if(oldPos)
		{
			movedPiece = table->pieceAtC(oldPos.col(), oldPos.row());
			if ( movedPiece->type() != pawn )
				throw BadMove( *m_ply, "Specified piece is not pawn");
			if ( movedPiece->isWhite() != m_isWhite )
				throw BadMove( *m_ply, "Specified piece's color and moving piece's color are not same");
		}
	}
	else
	{
		Piece *tmp = table->pieceAtC ( m_newPos.col() - 1, m_newPos.row() - coef );
		
		if ( ( tmp != 0 ) && (tmp->type() == pawn) && (tmp->isWhite() == m_isWhite) )
			movedPiece = tmp;
		else
		{
			tmp = table->pieceAtC ( m_newPos.col() + 1, m_newPos.row() - coef );
			if ( ( tmp != 0 ) && (tmp->type() == pawn) && (tmp->isWhite() == m_isWhite) )
				movedPiece = tmp;
		}
	}

	if ( movedPiece != 0 && dest != NULL)
	{
		m_movedPieceEx = table->detailed(movedPiece);
		if ( dest->type() == unknown )
		{
			Piece *longDest = table->pieceAtC(m_newPos.col(), m_newPos.row() - coef);
			if ( ( longDest != 0 ) &&
				 ( longDest->isWhite() != m_isWhite) &&
				 ( longDest->type() == pawn ) )
				 longDest->setType( unknown );
		}
		(*dest) = (*movedPiece);
		movedPiece->setType(unknown);
		if( 0 != m_ply->promoted() )
		{
			piece_type tmpType = guessTypeByChar( m_ply->promoted()->id() ); 
			if ( ( tmpType != pawn ) && ( tmpType != king ) )
				dest->setType( tmpType );				
		}
		return true;
	}
	return false;
}



bool ChEngn::PawnMove::makeSimpleMove( const ChEngn::Table* table) const
{
	short coef = (m_isWhite? 1 : -1);
	pgn::Square oldPos(m_newPos.col(), m_newPos.row() - coef);
	Piece* movedPiece = table->pieceAtC(oldPos.col(), oldPos.row());
	if( (movedPiece == 0) || 
	    (movedPiece->type() != pawn) || 
	    (movedPiece->isWhite() != m_isWhite) )
	{
		oldPos = pgn::Square(m_newPos.col(), m_newPos.row() - 2 * coef);
		movedPiece = table->pieceAtC(oldPos.col(), oldPos.row());
	}
	if( movedPiece != 0 )
	{
		m_movedPieceEx = table->detailed(movedPiece);
		if( (movedPiece->type() == pawn ) && 
			(movedPiece->isWhite() == m_isWhite) )
		{
			Piece *dest = table->pieceAtC(m_newPos.col(), m_newPos.row() );
			if( dest != 0 )
				if( dest->type() == unknown )
				{
					dest->setType( pawn );
					if( m_isWhite )
						dest->setWhite();
					else
						dest->setBlack();
					movedPiece->setType ( unknown );
					if( 0 != m_ply->promoted() )
					{
						piece_type tmpType = guessTypeByChar( m_ply->promoted()->id() ); 
						if ( ( tmpType != pawn ) && ( tmpType != king ) )
							dest->setType( tmpType );
					}
					return true;
				}
				else
					throw BadMove( *m_ply, DEST_OUT_OF_RANGE );
			else
				throw BadMove( *m_ply, DEST_OUT_OF_RANGE );

		}
		else
			throw BadMove( *m_ply, NO_SUITABLE_PIECE );
	}
	return false;
}
