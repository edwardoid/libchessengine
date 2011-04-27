#include <iostream>
#include <cppunit/ui/text/TextTestRunner.h>
#include "piece_test.h"

CPPUNIT_TEST_SUITE_REGISTRATION( TestPiece );

int main()
{
	CppUnit::TextTestRunner runner;
	CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();

	runner.addTest( registry.makeTest() );
	runner.run();
	return 0;
}
