#ifndef CHESS_ENGINE_PAWN_MOVE
#define CHESS_ENGINE_PAWN_MOVE

#include "CEMove.h"
#include <PGNSquare.h>

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
		PawnMove( const pgn::Ply* ply, const bool isWhite);
		~PawnMove();
		virtual bool make( const Table* table) const;
	private:
		bool makeCaptureMove(const Table* table) const;
		bool makeSimpleMove(const Table* table) const;
	private:
		pgn::Ply* m_ply;
		pgn::Square m_newPos;
	};
};

#endif // CHESS_ENGINE_PAWN_MOVE
