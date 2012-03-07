#include "CEBishopMove.h"
#include "CEException.h"
#include "CETable.h"
#include <stdlib.h>

ChEngn::BishopMove::BishopMove( const pgn::Ply* ply, const bool isWhite )
    : ChEngn::Move( ply, isWhite )
{
}

ChEngn::BishopMove::~BishopMove()
{
}

bool ChEngn::BishopMove::make( const ChEngn::Table* table ) const
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
		tmp->setType ( bishop );
		if( m_isWhite )
			tmp->setWhite();
		else
			tmp->setBlack();
		movedPiece->setType( unknown );
		return true;
	}
	throw BadMove( *m_ply, UNKNOWN_ERROR );
    return false;
}

ChEngn::Piece* ChEngn::BishopMove::findMovedPiece( const pgn::Ply* ply, const ChEngn::Table* table, bool isWhite )
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
   return movedPiece;
}
