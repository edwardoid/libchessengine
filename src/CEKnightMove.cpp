#include "CEKnightMove.h"
#include "CETable.h"
#include "CEException.h"
#include "CEDebugUtils.h"
#include <PGNPly.h>
#include <assert.h>

ChEngn::KnightMove::KnightMove(const pgn::Ply* ply, const bool isWhite)
	: ChEngn::Move(ply,isWhite),
	  m_movedPiece(NULL)
{
	m_column = 0;
	m_row = 0;
	if ( (ply->fromSquare() >= 'a') && (ply->fromSquare() <= 'h') )
		m_column = ply->fromSquare();
	else if ( (ply->fromSquare() >= '1') && (ply->fromSquare() <= '8') )
		m_row = ply->fromSquare();
}

ChEngn::KnightMove::~KnightMove()
{
}

bool ChEngn::KnightMove::make(const ChEngn::Table* table) const
{
	m_movedPiece = NULL;
	pgn::Square newPos = m_ply->toSquare();
	try2Top1Right(table, newPos);

	if(NULL == m_movedPiece)
		try2Right1Top( table, newPos);
	if(NULL == m_movedPiece)
        try2Right1Bottom( table, newPos);
	if(NULL == m_movedPiece)
        try2Bottom1Right( table, newPos);
	if(NULL == m_movedPiece)
        try2Bottom1Left( table, newPos);
	if(NULL == m_movedPiece)
		try2Left1Bottom( table, newPos );
	if(NULL == m_movedPiece)
                try2Left1Top( table, newPos);
	if(NULL == m_movedPiece)
                try2Top1Left( table, newPos );
	if(NULL == m_movedPiece)
	{
		throw BadMove(*m_ply, CAN_T_FIND_MOVED_PIECE);
	}

	Piece *dest = table->pieceAtC( newPos.col(), newPos.row() );

	if ( ( m_movedPiece != 0) && ( dest != 0 ) )
	{
		if ( ( (m_ply->isCapture()) && (dest->type() != unknown) )
			|| 
		 ( (dest->type() == unknown) && (! m_ply->isCapture() )  ) )
		 {
			 m_movedPieceEx = table->detailed(m_movedPiece);
			 dest->setType ( knight );
			 if( m_isWhite )
				 dest->setWhite();
			else
				dest->setBlack();
			 m_movedPiece->setType( unknown );
			 return true;
		}
	}
	return true;
}

pgn::Square ChEngn::KnightMove::try2Top1Right( const Table* table, const pgn::Square& newPos ) const
{
	pgn::Square oldPos = pgn::Square(newPos.col() + 1, newPos.row() + 2);
	tryToFindKnight(table, oldPos, newPos );
	return newPos;
}    
pgn::Square ChEngn::KnightMove::try2Right1Bottom( const Table* table, const pgn::Square& newPos ) const
{
	pgn::Square oldPos = pgn::Square(newPos.col() + 2, newPos.row() - 1);
	tryToFindKnight(table, oldPos, newPos );
	return newPos;
}

pgn::Square ChEngn::KnightMove::try2Right1Top( const Table* table, const pgn::Square& newPos ) const
{
	pgn::Square oldPos = pgn::Square(newPos.col() + 2, newPos.row() + 1);
	tryToFindKnight(table, oldPos, newPos );
	return newPos;
}

pgn::Square ChEngn::KnightMove::try2Bottom1Right( const Table* table, const pgn::Square& newPos ) const
{
	pgn::Square oldPos = pgn::Square(newPos.col() + 1, newPos.row() - 2);
	tryToFindKnight(table, oldPos, newPos );
	return newPos;
}

pgn::Square ChEngn::KnightMove::try2Bottom1Left( const Table* table, const pgn::Square& newPos ) const
{
	pgn::Square oldPos = pgn::Square(newPos.col() - 1, newPos.row() - 2);
	tryToFindKnight(table, oldPos, newPos );
	return newPos;
}

pgn::Square ChEngn::KnightMove::try2Left1Bottom( const Table* table, const pgn::Square& newPos ) const
{
	pgn::Square oldPos = pgn::Square(newPos.col() - 2, newPos.row() - 1);
	tryToFindKnight(table, oldPos, newPos );
	return newPos;
}

pgn::Square ChEngn::KnightMove::try2Left1Top( const Table* table, const pgn::Square& newPos ) const
{
	pgn::Square oldPos = pgn::Square(newPos.col() - 2, newPos.row() + 1);
	tryToFindKnight(table, oldPos, newPos );
	return newPos;
}

pgn::Square ChEngn::KnightMove::try2Top1Left( const Table* table, const pgn::Square& newPos ) const
{
	pgn::Square oldPos = pgn::Square(newPos.col() - 1, newPos.row() + 2);
	tryToFindKnight(table, oldPos, newPos );
	return newPos;
}


bool ChEngn::KnightMove::tryToFindKnight(  const Table* table, const pgn::Square& oldPos, const pgn::Square& newPos ) const
{
	Piece* tmp = table->pieceAtC( oldPos.col()  , oldPos.row());
	if ( ( 0 != tmp ) &&
	     ( tmp->isWhite() == m_isWhite ) &&
	     ( knight == tmp->type() ) && 
	     ( !moveAndCheckForCheck( table, oldPos, newPos, m_isWhite ) ) )
	{
		if ( ( ( 0 == m_column ) && ( 0 == m_row ) ) ^
		     ( ( 0 == m_column ) && ( oldPos.row() == m_row ) ) ^
		     ( ( 0 == m_row    ) && ( oldPos.col() == m_column ) ) )
	       {
		CHECK_PTR(tmp);
		m_movedPiece = tmp;
	       	return true;				
	       }
	}
	return false;
}



