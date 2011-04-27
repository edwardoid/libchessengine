#include "table_test.h"

void TestTable::test()
{
	ChEngn::Table a;
	ChEngn::Table b(a);
	for( int i =0; i < ChEngn::default_table_height; i++)
		for( int j = 0; j < ChEngn::default_table_width; j++ )
		{
			CPPUNIT_ASSERT( a.pieceAt( i, j ) == b.pieceAt( i, j ) );
		}
	
	for( int i = 'a'; i <= 'h'; i++)
		for( int j = '1'; j < '9'; j++ )
		{
			CPPUNIT_ASSERT( a.pieceAtC( i, j ) == b.pieceAtC( i, j ) );
		}
	CPPUNIT_ASSERT( 0 != a.	table() );
	CPPUNIT_ASSERT( 0 != a.	table() );
	CPPUNIT_ASSERT( 0 != a.	table() );
	CPPUNIT_ASSERT( 0 != a.	table() );
}
