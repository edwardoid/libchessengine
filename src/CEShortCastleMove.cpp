#include "CEShortCastleMove.h"
#include "CETable.h"

#include <PGNPly.h>


CE::ShortCastleMove::ShortCastleMove(bool isWhite)
    : Move(NULL, isWhite)
{
}

CE::ShortCastleMove::~ShortCastleMove()
{
}

bool CE::ShortCastleMove::make(const Table* table) const
{
    char kingCol = 'e';
	char row = (m_isWhite? '1': '8');
	char rookCol = 'h';

	Piece *kingPiece = table->pieceAtC( kingCol, row);
	Piece *rookPiece = table->pieceAtC( rookCol, row);
	Piece *newKingPiece = table->pieceAtC('g', row);
	Piece *newRookPiece = table->pieceAtC('f', row);

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
