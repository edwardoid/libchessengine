#ifndef TEST_CE_PIECE
#define TEST_CE_PIECE
#include <CEPiece.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>

class TestPiece: public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE( TestPiece );
	CPPUNIT_TEST( default_constructor );
	CPPUNIT_TEST( default_values );
	CPPUNIT_TEST( globals );
	CPPUNIT_TEST( set_get_functions );
	CPPUNIT_TEST( operators );
	CPPUNIT_TEST_SUITE_END();
	public:
		TestPiece();
		static std::string name(){ return "Testing ChEngn::Piece class"; }
		void default_constructor();
		void default_values();
		void set_get_functions();
		void globals();
		void set_type( ChEngn::piece_type type );
		void operators();
	private:
		ChEngn::Piece *m_a;
		ChEngn::Piece *m_b;
};

#endif // TEST_CE_PIECE
