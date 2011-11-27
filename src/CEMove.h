#ifndef CHESS_ENGINE_MOVE
#define CHESS_ENGINE_MOVE

#include "CEPiece.h"

namespace pgn
{
	class Ply;
};

namespace ChEngn
{
	class Table;

	class Move
	{
	public:
		Move(const pgn::Ply*, const bool);
		virtual ~Move() {};
		virtual bool make(const Table* table) const = 0;
		static piece_type guessTypeByChar( const char character );
		friend class PawnMove;
	protected:
		bool m_isWhite;
	};
}

#endif // CHESS_ENGINE_MOVE 
