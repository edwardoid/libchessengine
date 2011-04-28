#include "pgnm_test.h"
#include <string>
#include <PGNPly.h>
#include <iostream>

void TestPGNM::test_ply_parser()
{
	std::string bad_case = "dxe8=Q+";
	pgn::Ply ply( bad_case );
	
	CPPUNIT_ASSERT( !ply.isLongCastle() );
	CPPUNIT_ASSERT( !ply.isShortCastle() );
	CPPUNIT_ASSERT( ply.isCheck() );
	CPPUNIT_ASSERT( !ply.isCheckMate() );

	CPPUNIT_ASSERT( ( pgn::Piece::Pawn() == ply.piece() ) );

	CPPUNIT_ASSERT( pgn::Piece::Queen() == *ply.promoted() );
}
