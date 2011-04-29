#include "game_collection_test.h"
#include <PGNFile.h>
#include <PGNGame.h>
#include <PGNMoveList.h>
#include <PGNMove.h>

void TestGameCollection::test()
{
	pgn::File file("tests/collection.pgn");
	for( int i =0; i< file.gamesC().size(); i++ )
	{
		pgn::Game gm = file.gamesC()[i];
		pgn::MoveList ml = gm.moves();
		int j = 0;
		for( pgn::MoveList::iterator it = ml.begin(); it != ml.end(); it++)
			j++;
		std::cout << "For game #" << i <<" from " << ml.size() << " " << j << " moves are iterated " << std::endl;
	}
}
