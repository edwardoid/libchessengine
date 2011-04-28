#include <iostream>
#include <cppunit/ui/text/TextTestRunner.h>
#include "piece_test.h"
#include "table_test.h"
#include "engine_test.h"
#include "pgnm_test.h"

CPPUNIT_TEST_SUITE_REGISTRATION( TestPiece );
CPPUNIT_TEST_SUITE_REGISTRATION( TestTable );
CPPUNIT_TEST_SUITE_REGISTRATION( TestEngine );
CPPUNIT_TEST_SUITE_REGISTRATION( TestPGNM );

int main()
{
	CppUnit::TextTestRunner runner;

	runner.addTest( TestPiece::suite() );
	runner.addTest( TestTable::suite() );
	runner.addTest( TestEngine::suite() );
	runner.addTest( TestPGNM::suite() );
	runner.run();
	return 0;
}
