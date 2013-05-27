#include "CEQueenMove.h"
#include "CETable.h"
#include "CEException.h"
#include "CERookMove.h"
#include "CEBishopMove.h"
#include <PGNPly.h>


CE::QueenMove::QueenMove(const pgn::Ply* ply, bool isWhite)
    : Move(ply, isWhite)
{
}

CE::QueenMove::~QueenMove()
{
}

bool CE::QueenMove::make(const CE::Table* table) const
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
	{
		for ( char r = '1'; r<= '8'; r++)
		{
			Piece *tmp = table->pieceAtC( c, r );
			if ( (movedPiece == 0) &&
				 ( tmp != 0 ) &&
				 (tmp->type() == queen )
				 &&
				 (tmp->isWhite() == m_isWhite)) 
			{
				bool canMove = false;

				if(c == newPos.col())
					canMove = RookMove::checkForEmptynessRow(c, newPos.col(), newPos.row(), table);
				else if(r == newPos.row())
					canMove = RookMove::checkForEmptynessColumn(r, newPos.row(), newPos.col(), table);
				else if(abs(newPos.row() - r) == abs(newPos.col() - c))
					canMove = BishopMove::checkEmptynessDiagonal(c, r, newPos.col(), newPos.row(), table);
				
				if(canMove)
				{
					movedPiece = tmp;
					break;
				}
			}
		}
		if(movedPiece != 0)
			break;
	}

	if ( movedPiece != 0 )
	{
		m_movedPieceEx = table->detailed(movedPiece);
		(*dest) = (*movedPiece);
		movedPiece->setType( unknown );
		return true;
    }
    return false;
}
