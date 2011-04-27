#ifndef TEST_CE_PIECE
#define TEST_CE_PIECE
#include <CEEngine.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>

class TestEngine: public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE( TestEngine );
	CPPUNIT_TEST( test );
	CPPUNIT_TEST_SUITE_END();
	public:
		TestEngine(){};
		void test();
		static std::string name(){ return "Testing ChEngn::Engine class"; }
	private:
};

#endif // TEST_CE_PIECE
