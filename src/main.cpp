#include <iostream>
#include <CEPiece.h>


int main()
{
	ChEngn::Piece pc;
	pc.setType(ChEngn::knight);
	pc.setMoved();
	std::cout<<pc<<std::endl;
	return 0;
}
