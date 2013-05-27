#include "CERookMove.h"
#include "CETable.h"
#include "CEException.h"
#include <PGNPly.h>



CE::RookMove::RookMove(const pgn::Ply* ply, bool isWhite)
    : Move(ply, isWhite)
{
}

CE::RookMove::~RookMove()
{
}

bool CE::RookMove::make(const Table* table) const
{
    pgn::Square newPos = m_ply->toSquare();
	Piece *dest = table->pieceAtC( newPos.col() , newPos.row() );
	Piece *movedPiece = 0;

	char specCol = newPos.col();
	char specRow = newPos.row();
	
	bool isFromColSpecified = false;
	bool isFromRowSpecified = false;
	
	if( ( 'a' <= m_ply->fromSquare() ) && ( 'h' >= m_ply->fromSquare() ) )
	{
		specCol = m_ply->fromSquare();
		isFromColSpecified = true;
	}
	if( ( '1' <= m_ply->fromSquare() ) && ( '8' >= m_ply->fromSquare() ) )
	{
		specRow = m_ply->fromSquare();
		isFromRowSpecified = true;
	}

	for( char row = '1'; ( ( row <= '8') && ( !isFromRowSpecified ) ); row++ )
	{
		Piece* tmp = table->pieceAtC( specCol, row );
		if(tmp == 0 || tmp->type() != rook || (tmp->isWhite() != m_isWhite))
			continue;
        if ( ( movedPiece == 0 ) &&
			 checkForEmptynessColumn( newPos.row(), row, newPos.col(), table) &&
			 !moveAndCheckForCheck(table, pgn::Square( specCol, row ), newPos,  m_isWhite) )
		{
            movedPiece = tmp;
        }
	}

	if ( 0 == movedPiece )
		for( char col = 'a'; ( ( col <= 'h' ) && ( !isFromColSpecified ) ) ; col++ )
		{
			Piece* tmp = table->pieceAtC( col, specRow );
            if( tmp == 0 || tmp->type() != rook || (tmp->isWhite() != m_isWhite))
				continue;
			if ( checkForEmptynessRow(col, newPos.col(), specRow, table) &&
                 !moveAndCheckForCheck(table, pgn::Square( col, specRow ), newPos,  m_isWhite) )
            {
                movedPiece = tmp;
            }	
		}

	if ( ( movedPiece != 0 ) && (dest != 0 ) )
	{
		if ( m_ply->isCapture() && ( dest->type() == unknown ) )
			throw BadMove( *m_ply, UNKNOWN_CAPTURE );
		m_movedPieceEx = table->detailed(movedPiece);
		(*dest) = (*movedPiece);
		dest->setMoved();
		movedPiece->setType(unknown);
		return true;
	}
    return false;
}


bool CE::RookMove::checkForEmptynessRow(char fromColumn, char toColumn, char row, const Table *table)
{
	if ( table == 0 )
		return false;
	if ( fromColumn > toColumn)
	{
		char tmp	= fromColumn;
		fromColumn	= toColumn;
		toColumn	= tmp;
	}
	if (( fromColumn	< 'i' )	&& 
		( toColumn		< 'i' )		&& 
		( row			< '9')			&&
		( fromColumn	>= 'a')	&&
		( toColumn		>= 'a' )	&&
		( row			> '0'))
	{
		for ( char column = fromColumn + 1; column < toColumn; column++)
		{
			if ( table->pieceAtC(column, row)->type() != unknown)
				return false;
		}
	}
	else
		return false;
	return true;
}

bool CE::RookMove::checkForEmptynessColumn(char fromRow, char toRow, char column, const Table *table)
{
	if ( table == 0 )
		return false;
	if ( fromRow > toRow)
	{
		char tmp = fromRow;
		fromRow = toRow;
		toRow = tmp;
	}
	if (( fromRow	< '9' ) &&
		( toRow		< '9' ) &&
		( column	< 'i' ) &&
		( toRow		> '0' ) &&
		( fromRow	> '0' ) &&
		( column		>= 'a'))
	{
		for ( char row = fromRow + 1; row < toRow; ++row)
		{
			if ( table->pieceAtC(column, row)->type() != unknown)
				return false;
		}
	}
	else
		return false;
	return true;
}
