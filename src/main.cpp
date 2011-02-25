#include <iostream>
#include <CEPiece.h>
#include <CETable.h>

int main()
{
	ChEngn::Table tbl;

	ChEngn::Table other(tbl);
	std::cout<<tbl<<std::endl;
	std::cout<<other<<std::endl;
	return 0;
}
