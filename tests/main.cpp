#include <iostream>
#include <CEPiece.h>
#include <CETable.h>
#include <CEEngine.h>
#include <PGNFile.h>

bool test_making_moves( pgn::Game gm );


int main()
{
	pgn::File file;
	file.loadFile("tests/1966.pgn");
	pgn::GameCollection *cG = file.games();

	bool res = true;
	if( cG != 0 )
	{
		for( int i = 0; i < cG->size(); i++ )
			test_making_moves( (*cG)[i] );

		std::cout<<" Making moves engine test: ";
		if( res )
			std::cout<< " PASSED " << std::endl;
		else
			std::cout<< " PASSED " << std::endl;
	}
	else
		std::cout << "File can't be opened or there are no games in the file" <<std::endl;
	return 0;
}

bool test_making_moves( pgn::Game gm )
{
	ChEngn::Engine en( gm );
	int movesDone = 0;
	int movesCount = en.moves()->size();
	for( int i = 0; i < movesCount; i++ )
		if( en.makeNextMove() )
			movesDone++;
		else
			std::cerr << "Can't make move " << i+1 << std::endl;

	std::cout<< " Moves done: "<< movesDone <<"/"<< movesCount << std::endl;
	if ( movesDone == movesCount )
		return true;
	return false;
}
