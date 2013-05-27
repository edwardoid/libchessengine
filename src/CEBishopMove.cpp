#include "CEBishopMove.h"
#include "CEException.h"
#include "CETable.h"
#include <stdlib.h>

CE::BishopMove::BishopMove( const pgn::Ply* ply, const bool isWhite )
    : CE::Move( ply, isWhite )
{
}

CE::BishopMove::~BishopMove()
{
}

bool CE::BishopMove::make( const CE::Table* table ) const
{
   	pgn::Square newPos = m_ply->toSquare();
    
    Piece* movedPiece = findMovedPiece(m_ply, table, m_isWhite);

		
	Piece* tmp = table->pieceAtC( newPos.col() , newPos.row() );

	if ( m_ply->isCapture() )
	{
		if ( tmp == 0 ) 
			throw BadMove( *m_ply, DEST_OUT_OF_RANGE );

		if ( tmp->isWhite() == m_isWhite )
			throw BadMove( *m_ply, SAME_COLOR );

		if ( tmp->type() == unknown )
			throw BadMove( *m_ply, UNKNOWN_CAPTURE );
	}

	if ( ( movedPiece != 0 ) && (tmp != 0 ) )
	{
		m_movedPieceEx = table->detailed(movedPiece);
		tmp->setType ( bishop );
		if( m_isWhite )
			tmp->setWhite();
		else
			tmp->setBlack();
		movedPiece->setType( unknown );
		return true;
	}
	throw BadMove(*m_ply, CAN_T_FIND_MOVED_PIECE);
    return false;
}

CE::Piece* CE::BishopMove::findMovedPiece( const pgn::Ply* ply, const CE::Table* table, bool isWhite )
{
    Piece *movedPiece = 0;
   	pgn::Square newPos = ply->toSquare();
    const char fromSquare = ply->fromSquare();
	for( char  i = 'a'; i <= 'h'; i++ )
		for ( char j = '1'; j <= '8'; j++)
		{
			Piece *tmp = table->pieceAtC(i, j);
			if( ( tmp != 0 ) && ( tmp->type() == bishop) &&
				( tmp->isWhite() == isWhite) &&
				( abs( i - newPos.col()) == abs( j - newPos.row() ) ) )
			{
				if(!checkEmptynessDiagonal(i , j, ply->toSquare().col(), ply->toSquare().row(), table) && !ply->isCapture())
					continue;
				if( fromSquare == '-' )
				{
					movedPiece = tmp;
				}
				else
				{
					if( (fromSquare >= 'a') && (fromSquare <= 'h') && ( i == fromSquare ) )
						movedPiece = tmp;
					if( (fromSquare >= '1') && (fromSquare <= '8') && ( i == fromSquare ) )
						movedPiece = tmp;
				}
			}
		}
   return movedPiece;
}

bool CE::BishopMove::checkEmptynessDiagonal( char fromColumn, char fromRow, char toColumn, char toRow, const Table* table)
{
	if(abs(fromColumn - toColumn) != abs(fromRow - toRow))
		return false;
	if(abs(fromColumn - toColumn) == 1)
		return true;

	if(fromColumn > toColumn)
	{
		char tmpColumn = toColumn;
		char tmpRow	= toRow;
		toColumn = fromColumn;
		toRow = fromRow;
		fromColumn = tmpColumn;
		fromRow = tmpRow;
	}

	char coef = (fromRow < toRow ? 1 : -1);
	char rowEnd = (fromRow < toRow ? toRow : fromRow);

	for(char r = fromRow, c = fromColumn; c < toColumn && r != rowEnd; ++c, r += coef)
	{
		Piece* p = table->pieceAtC(c, r);
		if(p == NULL)
			continue;
		CE::piece_type t = p->type();
		if(t != CE::unknown)
		{
			if(((r == fromRow && c == fromColumn) ||
				(r == rowEnd && c == toColumn))	&&
				(t == CE::bishop || t == CE::queen))
				continue;
			return false;
		}
	}
	return true;
}
