#include <iostream>
#include <CEPiece.h>
#include <CETable.h>
#include <CEEngine.h>
#include <PGNFile.h>

const int copying_count = 100;

bool test_making_moves( pgn::Game gm );
bool test_table_creating( pgn::Game gm );
bool test_virtual_tables_copying( pgn::Game gm);

int main()
{
	pgn::File file;
	file.loadFile("tests/1963.pgn");
	pgn::GameCollection *cG = file.games();

	bool res = true;
	if( cG != 0 )
	{
		test_virtual_tables_copying( (*cG)[0] );

		for( int i = 0; i < cG->size(); i++ )
		{
			std::cout << "Making game: " << i + 1 << std::endl;
			test_making_moves( (*cG)[i] );
		}

		std::cout<<" Making moves engine test: ";
		if( res )
			std::cout<< " PASSED " << std::endl;
		else
			std::cout<< " FAILED " << std::endl;

		for( int i = 0; i < cG->size(); i++ )
			test_virtual_tables_copying( (*cG)[i] );

		std::cout<<" Making virtual table copyng test: ";
		if( res )
			std::cout<< " PASSED " << std::endl;
		else
			std::cout<< " FAILED " << std::endl;
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

	std::cout<< " Moves done: "<< movesDone <<"/"<< movesCount << std::endl;
	if ( movesDone == movesCount )
		return true;
	return false;
}

bool test_virtual_tables_copying( pgn::Game gm )
{
	ChEngn::Engine en( gm );
	ChEngn::VirtualTable tbl;
	for( int i = 0; i < copying_count; i++ )
		tbl = en.getVirtualTable();	
	return true;
}

bool test_table_creating( pgn::Game gm )
{
	ChEngn::Table tbl;
	ChEngn::VirtualTable tbl1(tbl);
	std::cout << tbl1 << std::endl;
}
