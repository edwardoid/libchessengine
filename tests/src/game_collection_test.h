#ifndef TEST_PGN_GAME_COLLECTION
#define TEST_PGN_GAME_COLLECTION
#include <PGNGameCollection.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>

class TestGameCollection: public CppUnit::TestCase
{
	CPPUNIT_TEST_SUITE( TestGameCollection );
	CPPUNIT_TEST( test );
//	CPPUNIT_TEST( brute_test );
	CPPUNIT_TEST_SUITE_END();
	public:
		TestGameCollection(){};
		void test();
		static std::string name(){ return "Testing ChEngn::GameCollection class"; }
	private:
};

#endif // TEST_PGN_GAME_COLLECTION
