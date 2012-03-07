#include "CEKingMove.h"
#include "CETable.h"
#include "CEException.h"


ChEngn::KingMove::KingMove(const pgn::Ply* ply, bool isWhite)
    : Move(ply, isWhite)
{
}

ChEngn::KingMove::~KingMove()
{
}


bool ChEngn::KingMove::make(const ChEngn::Table* table) const
{
 	pgn::Square newPos = m_ply->toSquare();
	char beginR = newPos.row() - 1;
	char beginC = newPos.col() - 1;
	char endR   = newPos.row() + 1;
	char endC   = newPos.col() + 1;

	Piece *dest = table->pieceAtC( newPos.col() , newPos.row() );
	
	if ( dest == 0 )
		throw BadMove( *m_ply, DEST_OUT_OF_RANGE );
	if ( dest->type() == king )
		throw BadMove( *m_ply, "King can't make move to other king" );
		

	for ( char c = beginC; c <= endC; c++) 
		for ( char r = beginR; r<= endR; r++ )
		{
			Piece *movedPiece = table->pieceAtC( c, r );
			if ( ( movedPiece != 0 ) &&
				 ( movedPiece->type() == king ) &&
				 ( movedPiece->isWhite() == m_isWhite )
				 )
			{
				( *dest ) = ( *movedPiece );
				movedPiece->setType( unknown );
				return true;
			}
		}
    return false;
}
