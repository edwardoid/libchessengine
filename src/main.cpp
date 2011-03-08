#include <iostream>
#include <CEPiece.h>
#include <CETable.h>
#include <CEEngine.h>
#include <PGNFile.h>

int main()
{
	pgn::File file;
	file.loadFile("tests/1963.pgn");
	pgn::GameCollection *cG = file.games();
	if( cG != 0 )
	{
		ChEngn::Engine en( (*cG)[1] );

		int i=0;
		while(en.makeNextMove())
			++i;

		std::cout<<"Game: "<<4 << " from: "<<cG->size()<< " Moves done: "<<i<<"/"<<en.moves()->size()<<std::endl;
	}
	else
	{
		std::cout<<"File can't be opened or there are no games in the file"<<std::endl;
	}
	return 0;
}
