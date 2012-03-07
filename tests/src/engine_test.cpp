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
