#include "CEMove.h"
#include "CETable.h"
#include <assert.h>

CE::Move::Move(const pgn::Ply* ply, const bool isWhite)
	: m_isWhite(isWhite)
    , m_ply(ply)
{
}

CE::piece_type CE::Move::guessTypeByChar( const char character )
{
	if( ( character == 'P') || ( character == '-') || ( character == 'p' ) )
		return pawn;

	if ( ( character == 'N' ) || ( character == 'n' ) )
		 return knight;

	if ( ( character == 'B' ) || ( character == 'b' ) )
		 return bishop;

	if ( ( character == 'R' ) || ( character == 'r' ) )
		 return rook;

	if ( ( character == 'Q' ) || ( character == 'q' ) )
		 return queen;

	if ( ( character == 'k' ) || ( character == 'K' ) )
		 return king;
	
	return unknown;
}

bool CE::Move::moveAndCheckForCheck(const CE::Table* table,
					const pgn::Square oldPos,
					const pgn::Square newPos,
					const bool isWhite ) const
{
	VirtualTable tmp = *table;
	assert ( 0 != tmp.pieceAt( oldPos.colIndex(), oldPos.rowIndex() ) );
	assert ( 0 != tmp.pieceAt( newPos.colIndex(), newPos.rowIndex() ) );
	tmp.pieceAtC( newPos.col(), newPos.row() )->setType( tmp.pieceAtC( oldPos.col(), oldPos.row() )->type() );
	if ( tmp.pieceAtC( oldPos.col(), oldPos.row() )->isWhite() ) 
		tmp.pieceAtC( newPos.col(), newPos.row() )->setType(unknown);
	else
		tmp.pieceAtC( newPos.col(), newPos.row() )->setBlack();
	tmp.pieceAtC( oldPos.col(), oldPos.row() )->setType( unknown );
	return isCheck( tmp , isWhite);
}

bool CE::Move::isCheck( const CE::Table& tbl, bool isWhite )
{
	char kingsColumn = 0;
	char kingsRow = 0;
	for( char c = 'a'; c <= 'h'; c++ )
		for( char r = '1'; r <= '8'; r++ )
		{
			Piece* tmp =  tbl.pieceAtC( c, r );
			if( ( 0 != tmp ) &&
				( tmp->isWhite() == isWhite ) &&
				( tmp->type() == king ) )
				{
					kingsColumn = c;
					kingsRow = r;
					break;
				}
		}

	if ( ( 0 != kingsColumn ) && ( 0 != kingsRow ) )
	{
		for ( char c = kingsColumn+1; c <= 'h'; c++ )
		{
			Piece* tmp = tbl.pieceAtC( c, kingsRow );
			if( ( 0 != tmp ) &&
				( tmp->isWhite() != isWhite ) &&
				( ( queen == tmp->type() ) || ( rook == tmp->type() ) ) )
				{
					std::cout << "HORISONTAL+: On " << c << kingsRow << " " << *tmp << std::endl;
				}
			else if ( ( 0 != tmp ) && ( unknown != tmp->type() ) )
				break;
		}
			
		for ( char c = kingsColumn - 1 ; c >= 'a'; c-- )
		{
			Piece* tmp = tbl.pieceAtC( c, kingsRow );
			if( ( 0 != tmp ) &&
				( tmp->isWhite() != isWhite ) &&
				( ( queen == tmp->type() ) || ( rook == tmp->type() ) ) )
				{
					std::cout << "HORISONTAL-: On " << c  << kingsRow << " " << *tmp << std::endl;
					return true;
				}
			else if ( ( 0 != tmp ) && ( unknown != tmp->type() ) )
				break;
		}
		for ( char r = kingsRow -1 ; r >= '1'; r-- )
		{
			Piece* tmp = tbl.pieceAtC( kingsColumn , r );
			if( ( 0 != tmp ) &&
				( tmp->isWhite() != isWhite ) &&
				( ( queen == tmp->type() ) || ( rook == tmp->type() ) ) )
				{
					std::cout << "VERTICAL1: On " << kingsColumn << r<< " " << *tmp << std::endl;
					return true;
				}
			else if ( ( 0 != tmp ) && ( unknown != tmp->type() ) )
				break;
		}
		
		for ( char r = kingsRow + 1; r <= '8'; r++ )
		{
			Piece* tmp = tbl.pieceAtC( kingsColumn , r );
			if( ( 0 != tmp ) &&
				( tmp->isWhite() != isWhite ) &&
				( ( queen == tmp->type() ) || ( rook == tmp->type() ) ) )
				{
					std::cout << "VERTICAL2: On " << kingsColumn << " " << r << *tmp << std::endl;
					return true;
				}
			else if ( ( 0 != tmp ) && ( unknown != tmp->type() ) )
				break;
		}

		for( char c = kingsColumn + 1, r = kingsRow + 1;
			( ( c <= 'h' ) && ( r <= '8' ) ); c++, r++ )
			{
				Piece* tmp = tbl.pieceAtC( c , r );
				if( ( 0 != tmp ) &&
					( tmp->isWhite() != isWhite ) &&
					( ( queen == tmp->type() ) || ( bishop == tmp->type() ) ) )
					{
						std::cout << "DIAGONAL /: On " << c << r << " " << *tmp << std::endl;
						return true;
					}
				else if ( ( 0 != tmp ) && ( unknown != tmp->type() ) )
					break;
			}
		
		for( char c = kingsColumn + 1, r = kingsRow - 1;
				( ( c <= 'h' ) && ( r >= '1' ) ); c++, r--)
				{
					Piece* tmp = tbl.pieceAtC( c , r );
					if( ( 0 != tmp ) &&
						( tmp->isWhite() != isWhite ) &&
						( ( queen == tmp->type() ) || ( bishop == tmp->type() ) ) )
						{
							std::cout << "DIAGONAL \\: On " << c << r << " " << *tmp << std::endl;
							return true;
						}
					else if ( ( 0 != tmp ) && ( unknown != tmp->type() ) )
						break;
				}
    
		for( char c = kingsColumn - 1, r = kingsRow - 1;
			( ( c >= 'a' ) && ( r >= '1' ) ); c--, r--)
			{
				Piece* tmp = tbl.pieceAtC( c , r );
				if( ( 0 != tmp ) &&
					( tmp->isWhite() != isWhite ) &&
					( ( queen == tmp->type() ) || ( bishop == tmp->type() ) ) )
					{
						std::cout << "VERTICAL: On " << c << r << " " << *tmp << std::endl;
						return true;
					}
//				else if ( ( 0 != tmp ) && ( unknown != tmp->type() ) )
					break;
			}
    
		for( char c = kingsColumn - 1, r = kingsRow - 1;
			( ( c >= 'a' ) && ( r >= '1' ) ); c--, r--)
			{
				Piece* tmp = tbl.pieceAtC( c , r );
				if( ( 0 != tmp ) &&
					( tmp->isWhite() != isWhite ) &&
					( ( queen == tmp->type() ) || ( bishop == tmp->type() ) ) )
					{
						std::cout << "VERTICAL: On " << c << r << " " << *tmp << std::endl;
						return true;
					}
				else if ( ( 0 != tmp ) && ( unknown != tmp->type() ) )
					break;
			}
    
    
		for( char c = kingsColumn - 1, r = kingsRow + 1;
			( ( c >= 'a' ) && ( r <= '8' ) ); c--, r++)
			{
				Piece* tmp = tbl.pieceAtC( c , r );
				if( ( 0 != tmp ) &&
					( tmp->isWhite() != isWhite ) &&
					( ( queen == tmp->type() ) || ( bishop == tmp->type() ) ) )
					{
						std::cout << "VERTICAL: On " << c << r << " " << *tmp << std::endl;
						return true;
					}
				else if ( ( 0 != tmp ) && ( unknown != tmp->type() ) )
					break;
			}
	}
	return false;
}
