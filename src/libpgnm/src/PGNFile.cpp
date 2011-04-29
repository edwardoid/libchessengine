#include "PGNFile.h"
#include "PGNException.h"
#include <fstream>
#include <iostream>
#include <errno.h>
#include <string.h>

pgn::File::File()
{
}

pgn::File::File(const File& other)
{
	hdata= other.gamesC();
}

pgn::File::File(const std::string fileName)
{
	loadFile(fileName);
}

pgn::File::File(const char* fileName)
{
	loadFile(fileName);
}

pgn::File::File(const GameCollection& gameCollection)
{
	hdata = GameCollection(gameCollection);
}

void pgn::File::loadFile(std::string fileName)
{
	if(fileName.size() > 0)
		loadFile(fileName.c_str());
}

void pgn::File::loadFile(const char* fileName)
{
	try
	{
		std::ifstream inp;
		inp.open(fileName, std::fstream::in);
		inp >> hdata;
	}
	catch ( std::fstream::failure e )
	{
		std::string errText = fileName;
		errText.append(" : ");
		errText.append( strerror( errno ) );
		throw pgn::bad_pgn_file( errText );
	}
}

pgn::GameCollection& pgn::File::games()
{
	return hdata;
}


pgn::GameCollection pgn::File::gamesC() const
{
	return hdata;
}

pgn::File::~File()
{
}
