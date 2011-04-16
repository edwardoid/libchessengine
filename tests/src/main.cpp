#include <iostream>
#include "ut_piece.h"

int main()
{
	bool res = false;
	std::cout << "Testing ChEngn::Piece class... " << std::endl;
	res = unit_test_piece();

	std::cout << "ChEngn::Piece tests : " << ( res ? "PASSED" : "FAILED"  ) << std::endl;

	return 0;
}
