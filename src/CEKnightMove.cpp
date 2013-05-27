#include "CEKnightMove.h"
#include "CETable.h"
#include "CEException.h"
#include "CEDebugUtils.h"
#include <PGNPly.h>
#include <assert.h>

CE::KnightMove::KnightMove(const pgn::Ply* ply, const bool isWhite)
	: CE::Move(ply,isWhite),
	  m_movedPiece(NULL)
{
	m_column = 0;
	m_row = 0;
	if ( (ply->fromSquare() >= 'a') && (ply->fromSquare() <= 'h') )
		m_column = ply->fromSquare();
	else if ( (ply->fromSquare() >= '1') && (ply->fromSquare() <= '8') )
		m_row = ply->fromSquare();
}

CE::KnightMove::~KnightMove()
{
}

bool CE::KnightMove::make(const CE::Table* table) const
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

pgn::Square CE::KnightMove::try2Top1Right( const Table* table, const pgn::Square& newPos ) const
{
	pgn::Square oldPos = pgn::Square(newPos.col() + 1, newPos.row() + 2);
	tryToFindKnight(table, oldPos, newPos );
	return newPos;
}    
pgn::Square CE::KnightMove::try2Right1Bottom( const Table* table, const pgn::Square& newPos ) const
{
	pgn::Square oldPos = pgn::Square(newPos.col() + 2, newPos.row() - 1);
	tryToFindKnight(table, oldPos, newPos );
	return newPos;
}

pgn::Square CE::KnightMove::try2Right1Top( const Table* table, const pgn::Square& newPos ) const
{
	pgn::Square oldPos = pgn::Square(newPos.col() + 2, newPos.row() + 1);
	tryToFindKnight(table, oldPos, newPos );
	return newPos;
}

pgn::Square CE::KnightMove::try2Bottom1Right( const Table* table, const pgn::Square& newPos ) const
{
	pgn::Square oldPos = pgn::Square(newPos.col() + 1, newPos.row() - 2);
	tryToFindKnight(table, oldPos, newPos );
	return newPos;
}

pgn::Square CE::KnightMove::try2Bottom1Left( const Table* table, const pgn::Square& newPos ) const
{
	pgn::Square oldPos = pgn::Square(newPos.col() - 1, newPos.row() - 2);
	tryToFindKnight(table, oldPos, newPos );
	return newPos;
}

pgn::Square CE::KnightMove::try2Left1Bottom( const Table* table, const pgn::Square& newPos ) const
{
	pgn::Square oldPos = pgn::Square(newPos.col() - 2, newPos.row() - 1);
	tryToFindKnight(table, oldPos, newPos );
	return newPos;
}

pgn::Square CE::KnightMove::try2Left1Top( const Table* table, const pgn::Square& newPos ) const
{
	pgn::Square oldPos = pgn::Square(newPos.col() - 2, newPos.row() + 1);
	tryToFindKnight(table, oldPos, newPos );
	return newPos;
}

pgn::Square CE::KnightMove::try2Top1Left( const Table* table, const pgn::Square& newPos ) const
{
	pgn::Square oldPos = pgn::Square(newPos.col() - 1, newPos.row() + 2);
	tryToFindKnight(table, oldPos, newPos );
	return newPos;
}


bool CE::KnightMove::tryToFindKnight(  const Table* table, const pgn::Square& oldPos, const pgn::Square& newPos ) const
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

pgn::ListOfSquares CE::KnightMove::knightPositions( const pgn::Square& sqRelative )
{
	pgn::ListOfSquares res;

	/*
		x x 
		x
		O
	*/
	pgn::Square sq1(sqRelative.col() + 1, sqRelative.row() + 2);
	
	/*
		x x 
		  x
		  O
	*/
	pgn::Square sq2(sqRelative.col() - 1, sqRelative.row() + 2);


	/*
		O x x
		    x
	*/
	pgn::Square sq3(sqRelative.col() + 2, sqRelative.row() - 1);
	
	
	/*
		    x
		O x x
	*/
	pgn::Square sq4(sqRelative.col() + 2, sqRelative.row() + 1);
	
	
	/*
		O
		x
		x x
	*/
	pgn::Square sq5(sqRelative.col()  + 1, sqRelative.row() - 2);


	/*
		  O
		  x
		x x
	*/
	pgn::Square sq6(sqRelative.col() - 1, sqRelative.row() - 2);


	/*
		x x O
		x
	*/
	pgn::Square sq7(sqRelative.col() - 2, sqRelative.row() - 1);


	/*
		x
		x x O
	*/
	pgn::Square sq8(sqRelative.col() - 2, sqRelative.row() + 1);

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




