#include "ut_piece.h"
#include <iostream>


bool unit_test_piece()
{
	bool test_result = true;
	std::cout << "ChEngn::Piece::Piece() : ";
	try
	{
		ChEngn::Piece p;
		std::cout << "PASSED" << std::endl;
	}
	catch(...)
	{
		std::cout << "FAILED" << std::endl;
	}

	std::cout << "ChEngn::Piece::Piece( const ChEngn::Piece& )  : ";
	try
	{
		ChEngn::Piece q( ChEngn::Piece() );
		std::cout << "PASSED" << std::endl;
	}
	catch(...)
	{
		std::cout << "FAILED" << std::endl;
	}

	std::cout << "ChEngn::Piece::type() : ";
	try
	{
		ChEngn::Piece p;
		if( p.type() == ChEngn::unknown )
			std::cout << "PASSED" << std::endl;
		else
			throw 0;
	}
	catch(...)
	{
		std::cout << "FAILED" << std::endl;
	}

	std::cout << "ChEngn::Piece::color() : ";
	try
	{
		ChEngn::Piece p;
		if( p.color() == ChEngn::white )
			std::cout << "PASSED" << std::endl;
		else
			throw 0;
	}
	catch(...)
	{
		std::cout << "FAILED" << std::endl;
	}

	std::cout << "ChEngn::Piece::isWhite(): SAME AS BELOW " << std::endl
			  << "ChEngn::Piece::isBlack(): SAME AS BELOW " << std::endl
			  << "ChEngn::Piece::isUnknown() : ";
	try
	{
		ChEngn::Piece p;
		if( ( p.color() == ChEngn::white ) && p.isWhite()
			&& (!p.isBlack() ) && p.isUnknown() )
			std::cout << "PASSED" << std::endl;
		else
			throw 0;
	}
	catch(...)
	{
		std::cout << "FAILED" << std::endl;
	}
	
	std::cout << "ChEngn::Piece::setMoved() : SAME AS BELOW " << std::endl
			  << "ChEngn::Piece::moveFlag() : ";
	try
	{
		ChEngn::Piece p;
		p.setMoved();
		if( p.moveFlag() == ChEngn::moved )
			std::cout << "PASSED" << std::endl;
		else
			throw 0;
	}
	catch(...)
	{
		std::cout << "FAILED" << std::endl;
	}	
	
	std::cout << "ChEngn::Piece::setType( ChEngn::piece_type ) : ";
	try
	{
		ChEngn::Piece p;
		bool tmpR = true;
		p.setType( ChEngn::unknown );
		if( p.type() == ChEngn::unknown )
		{
			p.setType( ChEngn::pawn );
			if ( p.type() == ChEngn::pawn )
			{
				p.setType( ChEngn::knight );
				if ( p.type() == ChEngn::knight )
				{
					p.setType( ChEngn::bishop );
					if ( p.type() == ChEngn::bishop )
					{
						p.setType( ChEngn::rook );
						if ( p.type() == ChEngn::rook )
						{
							p.setType( ChEngn::queen );
							if ( p.type() == ChEngn::queen )
							{
								p.setType( ChEngn::king );
								if ( p.type() == ChEngn::king )
									std::cout << "PASSED" << std::endl;
							}
						}
					}
				}
			}
		}

	}
	catch(...)
	{
		std::cout << "FAILED" << std::endl;
	}	

	std::cout << "ChEngn::Piece::operator = ( const ChEngn::Piece& ): ";
	try
	{
		ChEngn::Piece p;
		ChEngn::Piece q;
		p = q;
		std::cout << "PASSED" << std::endl;
	}
	catch( ... )
	{
		std::cout << "FAILED" << std::endl;
	}
	
	std::cout << "ChEngn::Piece::operator == ( const ChEngn::Piece& ): SAME AS BELOW "
			  << "ChEngn::Piece::operator != ( const ChEngn::Piece& ): ";
	try
	{
		ChEngn::Piece p;
		p.setType( ChEngn::pawn );
		ChEngn::Piece q;
		q.setType( ChEngn::pawn );
		
		if( p == q )
		{
			p.setType( ChEngn::knight );
			if ( p != q )
			{
				q.setType( ChEngn::knight );
				if ( p == q )
				{
					p.setMoved();
					if( p != q )
						std::cout << "PASSED" << std::endl;
				}
			}
		}

	}
	catch( ... )
	{
		std::cout << "FAILED" << std::endl;
	}

	std::cout << "operator << ( std::ostream&, const ChEngn::Piece& ): " << std::endl;
	try
	{
		ChEngn::Piece p;
		p.setWhite();
		std::cout << "White pieces: ";
		p.setType( ChEngn::unknown );
		std::cout << "*  unknown: " << p << std::endl;
		
		p.setType( ChEngn::pawn );
		std::cout << "*  pawn: " << p << std::endl;

		p.setType( ChEngn::knight );
		std::cout << "*  knight: " << p << std::endl;

		p.setType( ChEngn::bishop );
		std::cout << "*  bishop: " << p << std::endl;

		p.setType( ChEngn::rook );
		std::cout << "*  rook: " << p << std::endl;

		p.setType( ChEngn::queen );
		std::cout << "*  queen: " << p << std::endl;

		p.setType( ChEngn::king );
		std::cout << "*  king: " << p << std::endl;

		p.setBlack();
		std::cout << "Black pieces: ";
		p.setType( ChEngn::unknown );
		std::cout << "unknown: " << p << std::endl;
		
		p.setType( ChEngn::pawn );
		std::cout << "*  pawn: " << p << std::endl;

		p.setType( ChEngn::knight );
		std::cout << "*  knight: " << p << std::endl;

		p.setType( ChEngn::bishop );
		std::cout << "*  bishop: " << p << std::endl;

		p.setType( ChEngn::rook );
		std::cout << "*  rook: " << p << std::endl;

		p.setType( ChEngn::queen );
		std::cout << "*  queen: " << p << std::endl;

		p.setType( ChEngn::king );
		std::cout << "*  king: " << p << std::endl;


	}
	catch( ... )
	{
		std::cout << "operator << ( std::ostream&, const ChEngn::Piece& ): FAILED  " << std::endl;
	}

	return test_result;
}

