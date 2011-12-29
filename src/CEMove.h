#ifndef CHESS_ENGINE_MOVE
#define CHESS_ENGINE_MOVE

#include "CEPiece.h"
#include <PGNSquare.h>

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
		
		/**
		 * @brief Moves piece for current table, and check for check.
		 * Tyres to move piece form current table, is piece on given
		 * square is no ChEngn::king and checks is new position check
		 * position for given player
		 * @param oldPos - Position from piece will be moved
		 * @param newPos - Position where piece will be moved
		 * @param isWhite - Player color. True if player's color is white,
		 * false in other case.
		 * @return true if new check found
		 * @warning only ChEngn::queen, ChEngn::rook and ChEngn::bishop will
		 * be checked!
		 */
		bool moveAndCheckForCheck( const Table* table,
					   const pgn::Square oldPos,
					   const pgn::Square newPos,
					   const bool isWhite ) const;
		/** Tryes to found check in given table for given color's player.
		 * @brief Checks for check on table.
		 * @param tbl - Source table
		 * @param isWhite - Player color. True if player's colro white,
		 * false in other case.
		 * @return true if check position found.
		 */
		static bool isCheck( const Table& tbl, bool isWhite );

		friend class PawnMove;
	protected:
		bool m_isWhite;
	};
}

#endif // CHESS_ENGINE_MOVE 
