#include "engine_test.h"
#include <CEException.h>
#include <PGNException.h>
#include <PGNFile.h>
#include <iostream>
double CALC_IN_PERCENTAGE ( double val, double max ) {
	return ( double )( ( ( val ) * 100 ) / ( max ) );
};

void TestEngine::test_copy_constructor()
{
	pgn::File file("tests/collection.pgn");
	
	if( file.gamesC().size() > 0 )
	{
		ChEngn::Engine engn( file.gamesC()[27] );
		std::cout << engn.moves()->size() << std::endl;
		
		for( int i = 0; i < 100; i++ )
		{
			ChEngn::Engine copy_engine( engn );
			std::cout << copy_engine.moves()->size() << std::endl;
		}
	}
	else
	{
		std::cerr << "tests/good_pawn.pgn can't found!" << std::endl;
	}
}


void TestEngine::test_check_finding()
{
	return;
	ChEngn::VirtualTable tbl;
	tbl.cleanTable();

	CPPUNIT_ASSERT( 0 != tbl.pieceAtC( 'd', '3' ) );
	tbl.pieceAtC( 'd', '3' )->setType( ChEngn::king );
	tbl.pieceAtC( 'd', '3' )->setWhite();

    CPPUNIT_ASSERT( 0 != tbl.pieceAtC( 'd', '7' ) );
	tbl.pieceAtC( 'd', '7' )->setType( ChEngn::knight );
	tbl.pieceAtC( 'd', '7' )->setBlack();
	
	//std::cout << "Checking for check on: " << tbl << std::endl;
	CPPUNIT_ASSERT( !ChEngn::Engine::isCheck( tbl, true ) );

	CPPUNIT_ASSERT( 0 != tbl.pieceAtC( 'd', '5' ) );
	tbl.pieceAtC( 'd', '5' )->setType( ChEngn::rook );
	tbl.pieceAtC( 'd', '5' )->setWhite();
	
	//std::cout << "Checking for check on: " << tbl << std::endl;
	CPPUNIT_ASSERT( !ChEngn::Engine::isCheck( tbl, true ) );
	
	CPPUNIT_ASSERT( 0 != tbl.pieceAtC( 'd', '4' ) );
	tbl.pieceAtC( 'd', '4' )->setType( ChEngn::queen );
	tbl.pieceAtC( 'd', '4' )->setBlack();
	
	//std::cout << "Checking for check on: " << tbl << std::endl;
	CPPUNIT_ASSERT( ChEngn::Engine::isCheck( tbl, true ) );

	CPPUNIT_ASSERT( 0 != tbl.pieceAtC( 'd', '4' ) );
	tbl.pieceAtC( 'd', '4' )->setType( ChEngn::unknown );
	tbl.pieceAtC( 'd', '4' )->setBlack();
	

	CPPUNIT_ASSERT( 0 != tbl.pieceAtC( 'd', '4' ) );
	tbl.pieceAtC( 'd', '1' )->setType( ChEngn::rook );
	tbl.pieceAtC( 'd', '1' )->setBlack();
	
	//std::cout << "Checking for check on: " << tbl << std::endl;
	CPPUNIT_ASSERT( ChEngn::Engine::isCheck( tbl, true ) );

	CPPUNIT_ASSERT( 0 != tbl.pieceAtC( 'd', '2' ) );
	tbl.pieceAtC( 'd', '2' )->setType( ChEngn::queen );
	tbl.pieceAtC( 'd', '2' )->setWhite();
	
	//std::cout << "Checking for check on: " << tbl << std::endl;
	CPPUNIT_ASSERT( !ChEngn::Engine::isCheck( tbl, true ) );

	tbl.cleanTable();

	CPPUNIT_ASSERT( 0 != tbl.pieceAtC( 'e', '3' ) );
	tbl.pieceAtC( 'e', '3' )->setType( ChEngn::king );
	tbl.pieceAtC( 'e', '3' )->setWhite();

	CPPUNIT_ASSERT( 0 != tbl.pieceAtC( 'd', '4' ) );
	tbl.pieceAtC( 'h', '3' )->setType( ChEngn::queen );
	tbl.pieceAtC( 'h', '3' )->setBlack();
	
	//std::cout << "Checking for check on: " << tbl << std::endl;
	CPPUNIT_ASSERT( ChEngn::Engine::isCheck( tbl, true ) );

	CPPUNIT_ASSERT( 0 != tbl.pieceAtC( 'g', '3' ) );
	tbl.pieceAtC( 'g', '3' )->setType( ChEngn::queen );
	tbl.pieceAtC( 'g', '3' )->setWhite();
	
	//std::cout << "Checking for check on: " << tbl << std::endl;
	CPPUNIT_ASSERT( !ChEngn::Engine::isCheck( tbl, true ) );

	CPPUNIT_ASSERT( 0 != tbl.pieceAtC( 'b', '3' ) );
	tbl.pieceAtC( 'b', '3' )->setType( ChEngn::queen );
	tbl.pieceAtC( 'b', '3' )->setBlack();
	
	//std::cout << "Checking for check on: " << tbl << std::endl;
	CPPUNIT_ASSERT( ChEngn::Engine::isCheck( tbl, true ) );

	CPPUNIT_ASSERT( 0 != tbl.pieceAtC( 'd', '3' ) );
	tbl.pieceAtC( 'd', '3' )->setType( ChEngn::pawn );
	tbl.pieceAtC( 'd', '3' )->setWhite();
	
	//std::cout << "Checking for check on: " << tbl << std::endl;
	CPPUNIT_ASSERT( !ChEngn::Engine::isCheck( tbl, true ) );

	tbl.cleanTable();

	CPPUNIT_ASSERT( 0 != tbl.pieceAtC( 'f', '6' ) );
	tbl.pieceAtC( 'f', '6' )->setType( ChEngn::king );
	tbl.pieceAtC( 'f', '6' )->setBlack();

	CPPUNIT_ASSERT( 0 != tbl.pieceAtC( 'a', '2' ) );
	tbl.pieceAtC( 'a', '2' )->setType( ChEngn::pawn );
	tbl.pieceAtC( 'a', '2' )->setWhite();
	
	//std::cout << "Checking for check on: " << tbl << std::endl;
	CPPUNIT_ASSERT( !ChEngn::Engine::isCheck( tbl, false ) );

	CPPUNIT_ASSERT( 0 != tbl.pieceAtC( 'b', '2' ) );
	tbl.pieceAtC( 'b', '2' )->setType( ChEngn::queen );
	tbl.pieceAtC( 'b', '2' )->setWhite();
	
	//std::cout << "Checking for check on: " << tbl << std::endl;
	CPPUNIT_ASSERT( ChEngn::Engine::isCheck( tbl, false ) );

	CPPUNIT_ASSERT( 0 != tbl.pieceAtC( 'c', '3' ) );
	tbl.pieceAtC( 'c', '3' )->setType( ChEngn::bishop );
	tbl.pieceAtC( 'c', '3' )->setBlack();
	
	//std::cout << "Checking for check on: " << tbl << std::endl;
	CPPUNIT_ASSERT( !ChEngn::Engine::isCheck( tbl, false ) );

	CPPUNIT_ASSERT( 0 != tbl.pieceAtC( 'd', '4' ) );
	tbl.pieceAtC( 'd', '4' )->setType( ChEngn::bishop );
	tbl.pieceAtC( 'd', '4' )->setWhite();
	
	//std::cout << "Checking for check on: " << tbl << std::endl;
	CPPUNIT_ASSERT( ChEngn::Engine::isCheck( tbl, false ) );

	CPPUNIT_ASSERT( 0 != tbl.pieceAtC( 'e', '5' ) );
	tbl.pieceAtC( 'e', '5' )->setType( ChEngn::rook );
	tbl.pieceAtC( 'e', '5' )->setBlack();
	
	//std::cout << "Checking for check on: " << tbl << std::endl;
	CPPUNIT_ASSERT( !ChEngn::Engine::isCheck( tbl, false ) );

	CPPUNIT_ASSERT( 0 != tbl.pieceAtC( 'h', '8' ) );
	tbl.pieceAtC( 'h', '8' )->setType( ChEngn::bishop );
	tbl.pieceAtC( 'h', '8' )->setWhite();
	
	//std::cout << "Checking for check on: " << tbl << std::endl;
	CPPUNIT_ASSERT( ChEngn::Engine::isCheck( tbl, false ) );

	CPPUNIT_ASSERT( 0 != tbl.pieceAtC( 'g', '7' ) );
	tbl.pieceAtC( 'g', '7' )->setType( ChEngn::bishop );
	tbl.pieceAtC( 'g', '7' )->setBlack();
	
	//std::cout << "Checking for check on: " << tbl << std::endl;
	CPPUNIT_ASSERT( !ChEngn::Engine::isCheck( tbl, false ) );

	CPPUNIT_ASSERT( 0 != tbl.pieceAtC( 'b', '8' ) );
	tbl.pieceAtC( 'b', '8' )->setType( ChEngn::bishop );
	tbl.pieceAtC( 'b', '8' )->setWhite();
	
	//std::cout << "Checking for check on: " << tbl << std::endl;
	CPPUNIT_ASSERT( !ChEngn::Engine::isCheck( tbl, false ) );

	CPPUNIT_ASSERT( 0 != tbl.pieceAtC( 'c', '7' ) );
	tbl.pieceAtC( 'c', '7' )->setType( ChEngn::queen );
	tbl.pieceAtC( 'c', '7' )->setBlack();
	
	//std::cout << "Checking for check on: " << tbl << std::endl;
	CPPUNIT_ASSERT( !ChEngn::Engine::isCheck( tbl, false ) );

	CPPUNIT_ASSERT( 0 != tbl.pieceAtC( 'h', '2' ) );
	tbl.pieceAtC( 'h', '2' )->setType( ChEngn::bishop );
	tbl.pieceAtC( 'h', '2' )->setWhite();
	
	//std::cout << "Checking for check on: " << tbl << std::endl;
	CPPUNIT_ASSERT( !ChEngn::Engine::isCheck( tbl, false ) );

	CPPUNIT_ASSERT( 0 != tbl.pieceAtC( 'd', '6' ) );
	tbl.pieceAtC( 'd', '6' )->setType( ChEngn::king );
	tbl.pieceAtC( 'd', '6' )->setWhite();
	
	//std::cout << "Checking for check on: " << tbl << std::endl;
	CPPUNIT_ASSERT( ChEngn::Engine::isCheck( tbl, true ) );


	tbl.cleanTable();
	tbl.pieceAtC('e', '8')->setType( ChEngn::king );
	tbl.pieceAtC('e', '8')->setBlack();
	tbl.pieceAtC('g', '6')->setType( ChEngn::knight);
	tbl.pieceAtC('g', '6')->setBlack();
	tbl.pieceAtC('h', '5')->setType( ChEngn::queen );
	tbl.pieceAtC('h', '5')->setWhite();

	std::cout << "Checking for check on: " << tbl << std::endl;
	CPPUNIT_ASSERT( !ChEngn::Engine::isCheck( tbl, false ) );

}

void TestEngine::test_remove_and_found_check()
{
	
	pgn::File file("tests/opening_check.pgn");
	ChEngn::Engine en( file.gamesC()[0] );
	try
	{
		while( en.makeNextMove() );
	
		std::cout << "Removing piece on d7, and trying to foun chec\n" << en << std::endl;
		CPPUNIT_ASSERT( en.moveAndCheckForCheck( pgn::Square( 'd', '7' ), pgn::Square( 'd', '6' ), false ) );
		CPPUNIT_ASSERT( !en.moveAndCheckForCheck( pgn::Square( 'd', '7' ), pgn::Square( 'd', '6' ), true ) ); 

	}
	catch( ChEngn::BadMove e )
	{
		std::cerr << e.what() << " " << e.comment() << std::endl;
	}
}


void TestEngine::brute_test()
{
	try
	{
		pgn::File file("tests/collection.pgn");
		pgn::GameCollection cG = file.gamesC();
		int doneGames = 0;
		for( int i = 0; i < cG.size(); i++ )
			{
				std::cout << "Making game: " << i << std::endl;
				ChEngn::Engine  en( cG[i] );
				int movesDone = 1;
				const int movesCount = en.moves()->size();

				try
				{
					while( en.makeNextMove() )
					{
						//std::cout << * en.nextMove() << std::endl;
						movesDone++;
					}

				}
				catch ( ChEngn::BadMove e )
				{
					std::cerr << e.what() << " " << e.comment() << " Game #" << i << std::endl;
				}
				
				std::cout<< " Moves done: "<< movesDone <<"/"<< movesCount  << " ("
						<< CALC_IN_PERCENTAGE( movesDone, movesCount ) << "%)" << std::endl
						 << "Last state: \n" << en << std::endl;
				if ( movesDone == movesCount )
					doneGames++;
			}
			std::cout << "From " << cG.size() << " games " << doneGames << " games evaluated ( "
					  << ( double ) ( ( doneGames * 100 )/ cG.size() )  << "% )." << std::endl;
	}
	catch( pgn::bad_pgn_file e )
	{
		std::cerr << e.what() << ":(" << std::endl;
	}
	catch( pgn::invalid_result e )
	{
		std::cerr << e.what() << std::endl;
	}
	catch( ... )
	{
		std::cerr << "Unknown exception!" << std::endl;
	}

}
