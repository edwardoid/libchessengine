#include "CEKingMove.h"
#include "CETable.h"
#include "CEException.h"


CE::KingMove::KingMove(const pgn::Ply* ply, bool isWhite)
    : Move(ply, isWhite)
{
}

CE::KingMove::~KingMove()
{
}


bool CE::KingMove::make(const CE::Table* table) const
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
				m_movedPieceEx = table->detailed(movedPiece);
				( *dest ) = ( *movedPiece );
				movedPiece->setType( unknown );
				return true;
			}
		}
    return false;
}

pgn::ListOfSquares CE::KingMove::kingPositions( const pgn::Square& sqRelative )
{
	pgn::ListOfSquares res;
	pgn::Square sq1(sqRelative.col() + 1, sqRelative.row());
	pgn::Square sq2(sqRelative.col() - 1, sqRelative.row());
	pgn::Square sq3(sqRelative.col(), sqRelative.row() - 1);
	pgn::Square sq4(sqRelative.col(), sqRelative.row() + 1);
	pgn::Square sq5(sqRelative.col() + 1, sqRelative.row() + 1);
	pgn::Square sq6(sqRelative.col() + 1, sqRelative.row() - 1);
	pgn::Square sq7(sqRelative.col() - 1, sqRelative.row() + 1);
	pgn::Square sq8(sqRelative.col() - 1, sqRelative.row() - 1);

	if(sq1) res.push_front(sq1);
	if(sq2) res.push_front(sq2);
	if(sq3) res.push_front(sq3);
	if(sq4) res.push_front(sq4);
	if(sq5) res.push_front(sq5);
	if(sq6) res.push_front(sq6);
	if(sq7) res.push_front(sq7);
	if(sq8) res.push_front(sq8);

	return res;
}
