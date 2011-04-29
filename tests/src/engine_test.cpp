#include "engine_test.h"
#include <CEException.h>
#include <PGNException.h>
#include <PGNFile.h>
#include <iostream>

void TestEngine::test()
{
	pgn::File file("tests/good_pawn.pgn");
	
	if( file.gamesC().size() > 0 )
	{
		ChEngn::Engine engn( file.gamesC()[6] );
		int i = 1;
		try{
		
			while( engn.makeNextMove() )
			{
				//std::cout << *engn.nextMove() << std::endl;
				++i;
			}
		}
		catch( ChEngn::BadMove e )
		{
			std::cerr << e.what() << "Comment: " << e.comment() << std::endl;
		}
		//std::cout << "From " << engn.moves()->size() << "moves " << i << "moves done!" << std::endl;
		std::cout << engn << std::endl;
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
						std::cout << * en.nextMove() << std::endl;
						movesDone++;
					}

					std::cout << en << std::endl;
				}
				catch ( ChEngn::BadMove e )
				{
					std::cerr << e.what() << " " << e.comment() << " Game #" << i << std::endl;
				}
				
				if ( movesCount > movesDone )
				{
					std::cerr << "Can't make move " << i+1 << std::endl;
					std::cerr << "Current table status: \n";
					std::cerr << "Move: " << (*(en.nextMove()) ) << std::endl;
					std::cerr << en.getVirtualTable() << std::endl; 
					break;
				}
            
				std::cout<< " Moves done: "<< movesDone <<"/"<< movesCount << std::endl
						;// << "Last state: \n" << en << std::endl;
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

}
