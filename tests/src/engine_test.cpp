#include "engine_test.h"
#include <PGNFile.h>
#include <iostream>

void TestEngine::test()
{
	pgn::File file("tests/good_pawn.pgn");
	
	std::cout << "Hmmmmm.....";
	std::cerr << "Hmmmmm.....";
	if( file.games()->size() > 0 )
	{
		ChEngn::Engine engn( (*file.games())[0] );
		while( engn.makeNextMove() );
		
		std::cout << engn << std::endl;
	}
	else
	{
		std::cerr << "tests/good_pawn.pgn can't found!" << std::endl;
	}
}
