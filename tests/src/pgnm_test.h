#ifndef TEST_LIB_PGNM
#define TEST_LIB_PGNM
#include <cppunit/extensions/HelperMacros.h>

class TestPGNM: public CppUnit::TestCase
{
	CPPUNIT_TEST_SUITE( TestPGNM );
	CPPUNIT_TEST( test_ply_parser );
	CPPUNIT_TEST_SUITE_END();
	public:
		TestPGNM(){};
		void test_ply_parser();
		static std::string name(){ return "Testing libgnm"; }
	private:
};

#endif // TEST_LIB_PGNM
