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
		std::cout<<"Loaded: "<<cG->size()<<" games"<<std::endl;
		ChEngn::Engine en( (*cG)[0] );
		std::cout<< en.moves()->size() << " moves in loaded game"<<std::endl;
		std::cout<<en<<std::endl;

		int i=0;
		while(en.makeNextHalfMove())
			std::cout<< ++i <<" "<<en.getVirtualTable()<<std::endl;
	}
	else
	{
		std::cout<<"File can't be opened or there are no games in the file"<<std::endl;
	}
	return 0;
}
