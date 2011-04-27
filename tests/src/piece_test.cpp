#include "piece_test.h"

TestPiece::TestPiece()
{
	m_a = 0;
	m_b = 0;
}

void TestPiece::default_constructor()
{
	m_a = new ChEngn::Piece();
	CPPUNIT_ASSERT( m_a != 0 );

	m_b =  new ChEngn::Piece();
	CPPUNIT_ASSERT( m_b!= 0 );
}

void TestPiece::default_values()
{
	if( m_a == 0 )
		m_a = new ChEngn::Piece();
	CPPUNIT_ASSERT( m_a != 0 );
	CPPUNIT_ASSERT( m_a->isWhite() );
	CPPUNIT_ASSERT( !m_a->isBlack() );
	CPPUNIT_ASSERT_EQUAL( m_a->type(), ChEngn::unknown );

}

void TestPiece::set_get_functions()
{
	if( m_a == 0 )
		m_a = new ChEngn::Piece();
	CPPUNIT_ASSERT( m_a != 0 );
	
	CPPUNIT_ASSERT( ChEngn::white != ChEngn::black );

	m_a->setWhite();
	CPPUNIT_ASSERT( m_a->isWhite() );
	CPPUNIT_ASSERT( m_a->color() == ChEngn::white );
	
	m_a->setBlack();
	CPPUNIT_ASSERT( !m_a->isWhite() );
	CPPUNIT_ASSERT( m_a->color() == ChEngn::black );

	CPPUNIT_ASSERT( m_a->moveFlag() != ChEngn::moved );
	m_a->setMoved();
	CPPUNIT_ASSERT( m_a->moveFlag() == ChEngn::moved );

	CPPUNIT_ASSERT( m_a->type() == ChEngn::unknown );
	set_type( m_a->type() );

	set_type( ChEngn::pawn );
	set_type( ChEngn::knight );
	set_type( ChEngn::bishop );
	set_type( ChEngn::rook );
	set_type( ChEngn::queen );
}

void TestPiece::globals()
{
	CPPUNIT_ASSERT( ChEngn::pawn == 1 );
	CPPUNIT_ASSERT( ChEngn::knight > ChEngn::pawn );
	CPPUNIT_ASSERT( ChEngn::bishop > ChEngn::knight );
	CPPUNIT_ASSERT( ChEngn::rook > ChEngn::bishop );
	CPPUNIT_ASSERT( ChEngn::queen > ChEngn::rook );
	CPPUNIT_ASSERT( ChEngn::king > ChEngn::queen );
	CPPUNIT_ASSERT( ChEngn::white != ChEngn::black );
	CPPUNIT_ASSERT( ChEngn::unknown == 63 );
}

void TestPiece::set_type( ChEngn::piece_type tpe )
{
	if( m_a == 0 )
		m_a = new ChEngn::Piece();
	m_a->setType( tpe );
	m_a->setWhite();
	CPPUNIT_ASSERT( tpe == m_a->type() );
	m_a->setBlack();
	CPPUNIT_ASSERT( tpe == m_a->type() );
}

void TestPiece::operators()
{
	ChEngn::Piece first;
	ChEngn::Piece second( first );
	CPPUNIT_ASSERT( first == second );
	CPPUNIT_ASSERT( !( first != second ) );
	first.setBlack();
	second.setWhite();
	CPPUNIT_ASSERT( first != second );
	CPPUNIT_ASSERT( !(first == second ) );

	first = second;
	CPPUNIT_ASSERT( first == second );
}
