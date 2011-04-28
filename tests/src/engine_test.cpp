#include "engine_test.h"
#include <CEException.h>
#include <PGNException.h>
#include <PGNFile.h>
#include <iostream>

void TestEngine::test()
{
	pgn::File file("tests/good_pawn.pgn");
	
	if( file.games()->size() > 0 )
	{
		ChEngn::Engine engn( (*file.games())[0] );
		int i = 1;
		try{
		
			while( engn.makeNextMove() )
			{
				std::cout << * engn.nextMove() << std::endl;
				++i;
			}
		}
		catch( ChEngn::BadMove e )
		{
			std::cerr << e.what() << "Comment: " << e.comment() << std::endl;
		}
		std::cout << "From " << engn.moves()->size() << "moves " << i << "moves done!" << std::endl;
		std::cout << engn << std::endl;
	}
	else
	{
		std::cerr << "tests/good_pawn.pgn can't found!" << std::endl;
	}
}

void TestEngine::brute_test()
{
/*
	try
	{
		pgn::File file("1963.pgn");
		pgn::GameCollection *cG = file.games();
    
		CPPUNIT_ASSERT( 0 != cG );
		for( int i = 0; i < cG->size(); i++ )
			{
				std::cout << "Making game: " << i + 1 << std::endl;
				ChEngn::Engine en( (*cG)[i] );
				int movesDone = 0;
				int movesCount = en.moves()->size();
				for( int i = 0; i < movesCount; i++ )
					if( en.makeNextHalfMove() )
						movesDone++;
					else
					{
						std::cerr << "Can't make move " << i+1 << std::endl;
						std::cerr << "Current table status: \n";
						std::cerr << "Move: " << (*(en.nextMove()) ) << std::endl;
						std::cerr << en.getVirtualTable() << std::endl; 
						break;
					}
            
				std::cout<< " Moves done: "<< movesDone <<"/"<< movesCount << std::endl
						 << "Last state: \n" << en << std::endl;
			}
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
*/
}
