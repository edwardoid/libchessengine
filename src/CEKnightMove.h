#ifndef CHESS_ENGINE_KNIGHT_MOVE
#define CHESS_ENGINE_KNIGHT_MOVE

#include "CEMove.h"
#include <PGNSquare.h>

namespace pgn
{
	class Ply;
};

namespace ChEngn
{
	class KnightMove: Move
	{
	public:

		KnightMove( const pgn::Ply* ply, const bool isWhite );
		~KnightMove();
		bool  make( const Table* table ) const;
	private:
		pgn::Square try2Top1Right( const Table* table, const pgn::Square& newPos ) const;
		pgn::Square try2Right1Top( const Table* table, const pgn::Square& newPos ) const;	
		pgn::Square try2Right1Bottom( const Table* table, const pgn::Square& newPos ) const;
		pgn::Square try2Bottom1Right( const Table* table, const pgn::Square& newPos ) const;
		pgn::Square try2Bottom1Left( const Table* table, const pgn::Square& newPos ) const;
		pgn::Square try2Left1Bottom( const Table* table, const pgn::Square& newPos ) const;
		pgn::Square try2Left1Top( const Table* table, const pgn::Square& newPos ) const;
		pgn::Square try2Top1Left( const Table* table, const pgn::Square& newPos ) const;
		bool tryToFindKnight(  const Table* table,
				       const pgn::Square& oldPos,
				       const pgn::Square& newPos ) const;
	private:
		mutable Piece *m_movedPiece;
		mutable char m_row;
		mutable char m_column;
		pgn::Ply *m_ply;
	};
}

#endif // CHESS_ENGINE_KNIGHT_MOVE
