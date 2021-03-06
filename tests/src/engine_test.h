#ifndef TEST_CE_ENGINE
#define TEST_CE_ENGINE
#include <CEEngine.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>

class TestEngine: public CppUnit::TestCase
{
	CPPUNIT_TEST_SUITE( TestEngine );
	CPPUNIT_TEST( test_copy_constructor );
	CPPUNIT_TEST( brute_test );
	CPPUNIT_TEST_SUITE_END();
	public:
		TestEngine(){};
		void test_copy_constructor();
		void brute_test();
		static std::string name(){ return "Testing ChEngn::Engine class"; }
	private:
};

#endif // TEST_CE_ENGINE
