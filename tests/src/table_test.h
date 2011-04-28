#ifndef TEST_CE_TABLE
#define TEST_CE_TABLE
#include <CETable.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>

class TestTable: public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE( TestTable );
	CPPUNIT_TEST( test );
	CPPUNIT_TEST_SUITE_END();
	public:
		TestTable(){};
		void test();
		static std::string name(){ return "Testing ChEngn::Table class"; }
	private:
};

#endif // TEST_CE_TABLE
