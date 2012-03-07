#include "CEQueenMove.h"
#include "CETable.h"
#include "CEException.h"
#include <PGNPly.h>


ChEngn::QueenMove::QueenMove(const pgn::Ply* ply, bool isWhite)
    : Move(ply, isWhite)
{
}

ChEngn::QueenMove::~QueenMove()
{
}

bool ChEngn::QueenMove::make(const ChEngn::Table* table) const
{
 	pgn::Square newPos = m_ply->toSquare();

	Piece *dest = table->pieceAtC( newPos.col() , newPos.row() );

	if(dest == 0 )
		throw BadMove( *m_ply, DEST_OUT_OF_RANGE );

	if ( m_ply->isCapture())
		if ( dest->type() == unknown)
			throw BadMove( *m_ply, UNKNOWN_CAPTURE );
	Piece *movedPiece = 0;


	for ( char c = 'a'; c <= 'h'; c++ )
		for ( char r = '1'; r<= '8'; r++)
		{
			Piece *tmp = table->pieceAtC( c, r );
			if ( (movedPiece == 0) &&
				 ( tmp != 0 ) &&
				 (tmp->type() == queen )
				 &&
				 (tmp->isWhite() == m_isWhite) ) 
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
