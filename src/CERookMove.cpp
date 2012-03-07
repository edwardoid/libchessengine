#include "CERookMove.h"
#include "CETable.h"
#include "CEException.h"
#include <PGNPly.h>



ChEngn::RookMove::RookMove(const pgn::Ply* ply, bool isWhite)
    : Move(ply, isWhite)
{
}

ChEngn::RookMove::~RookMove()
{
}

bool ChEngn::RookMove::make(const Table* table) const
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
        if ( ( tmp != 0 ) &&
                ( tmp->type() == rook ) &&
                ( tmp->isWhite() == m_isWhite ) &&
                ( movedPiece == 0 ) &&
                checkForEmptynessV( row,
                                    newPos.row() ,
                                    specCol ,
                                    table) &&
                ( !moveAndCheckForCheck(table, pgn::Square( specCol, row ), newPos,  m_isWhite ) ) )
		{
            movedPiece = tmp;
        }
	}

	if ( 0 == movedPiece )
		for( char col = 'a'; ( ( col <= 'h' ) && ( !isFromColSpecified ) ) ; col++ )
		{
			Piece* tmp = table->pieceAtC( col, specRow );
            if ( ( tmp != 0 ) &&
                    ( tmp->type() == rook ) &&
                    ( tmp->isWhite() == m_isWhite )  &&
                    checkForEmptynessH( col,
                                        newPos.col(),
                                        specRow ,
                                        table) &&
                   ( !moveAndCheckForCheck(table, pgn::Square( col, specRow ), newPos,  m_isWhite ) ) )
            {
                movedPiece = tmp;
            }	
		}

	if ( ( movedPiece != 0 ) && (dest != 0 ) )
	{
		if ( m_ply->isCapture() && ( dest->type() == unknown ) )
			throw BadMove( *m_ply, UNKNOWN_CAPTURE );
		(*dest) = (*movedPiece);
		dest->setMoved();
		movedPiece->setType(unknown);
		return true;
	}
    return false;
}


bool ChEngn::RookMove::checkForEmptynessH(char from, char to, char row, const Table *table) const
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

bool ChEngn::RookMove::checkForEmptynessV(char from, char to, char column, const Table *table) const
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


