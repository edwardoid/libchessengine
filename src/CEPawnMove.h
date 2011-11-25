#ifndef CHESS_ENGINE_PAWN_MOVE
#define CHESS_ENGINE_PAWN_MOVE

#include "CEMove.h"

namespace pgn
{
	class Ply;
};

namespace ChEngn
{
	class Table;

	class PawnMove: public Move
	{
	public:
		PawnMove( const pgn::Ply* ply);
		~PawnMove();
		virtual bool make( const Table* table) const;
	private:
		pgn::Ply* m_ply;	
	};
};

#endif // CHESS_ENGINE_PAWN_MOVE
