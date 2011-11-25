#include "CEPawnMove.h"
#include "CETable.h"
#include <PGNPly.h>

ChEngn::PawnMove::PawnMove(const pgn::Ply* ply)
{
	m_ply = new pgn::Ply(*ply);
}

ChEngn::PawnMove::~PawnMove()
{
}

bool ChEngn::PawnMove::make( const ChEngn::Table* table) const
{
	return true;
}
