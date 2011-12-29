#include <iostream>
#include <PGNFile.h>
#include <CEEngine.h>
#include <CEException.h>

int main()
{
	pgn::File file( "myfile.pgn" );
	
	for ( int i = 0; i < file.games().size(); i ++ )
	{
		ChEngn::Engine engine( file.games()[ i ] );
		try {
			while( engine.makeNextHalfMove() )
			{
				;
			}
		}
		catch ( ChEngn::BadMove e )
		{
			std::cerr << e.what() << std::endl;
		}
		catch( ... )
		{
			std::cerr << "Unknown error..." << std::endl;
		}
	}

	return 0;
}
