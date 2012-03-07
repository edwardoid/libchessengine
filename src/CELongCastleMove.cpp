#include "CELongCastleMove.h"
#include "CETable.h"

#include <PGNPly.h>

ChEngn::LongCastleMove::LongCastleMove(bool isWhite)
    : Move(NULL, isWhite)
{
}

ChEngn::LongCastleMove::~LongCastleMove()
{
}

bool ChEngn::LongCastleMove::make(const Table* table) const
{
    char kingCol = 'e';
	char row = (m_isWhite? '1': '8');
	char rookCol = 'a';

	Piece *kingPiece = table->pieceAtC( kingCol, row);
	Piece *rookPiece = table->pieceAtC( rookCol, row);
	
	Piece *newKingPiece = table->pieceAtC('c', row);
	Piece *newRookPiece = table->pieceAtC('d', row);

	if ( ( newRookPiece != 0 ) && ( newKingPiece != 0 ) )
	{
		(*newKingPiece) = (*kingPiece);
		(*newRookPiece) = (*rookPiece);
		newKingPiece->setMoved();
		newRookPiece->setMoved();
		kingPiece->setType( unknown );
		rookPiece->setType( unknown );
		return true;
	}

    return false;
}
