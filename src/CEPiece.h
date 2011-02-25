#ifndef CHESS_ENGINE_PIECE
#define CHESS_ENGINE_PIECE

#include <iostream>
/**
 * @file CEPiece.h
 * @brief Here are defined ChEngn::Piece class. Most of constants and structs:
 * ChEngn::piece_movement_flag, ChEngn::piece_color, ChEngn::piece_type, 
 */


/// @namespace ChEngn Contains all typedefs, constants, classes defined in
//linchessengine
namespace ChEngn
{

	/// Piece type is just a unsigned char
	typedef const unsigned char piece_type;

	/// Piece color is just a unsigned char
	typedef const unsigned char piece_color;

	/// Piece movement flag is just a bit in unsigned char
	typedef const unsigned char piece_movement_flag;
	
	/// Uses to present unknown type piece 63 = [00011111]
	piece_type unknown = 63;

	/// Uses to present pawns
	piece_type pawn   = 1 << 0;

	/// Uses to present knights
	piece_type knight = 1 << 1;

	/// Uses to present bishops
	piece_type bishop = 1 << 2;

	/// Uses to present rooks
	piece_type rook   = 1 << 3;

	/// Uses to present queens
	piece_type queen  = 1 << 4;

	/// Uses to present kings
	piece_type king   = 1 << 5;

	/// Uses to set flag if piece is white ( else flag is not set)
	piece_color  white  = 1 << 6;

	/// Uses to unset flag if piece is black
	piece_color  black  = 0 << 6;

	/// Uses to set flag is piece has been moved
	piece_movement_flag moved  = 1 << 7;

	/**
	 * Provides basic interface for init some chess piece, eg "knight"
	 * @class ChEngn::Piece
	 * @brief Chess piece
	 */
	class Piece
	{
		public:
			/**
			 * After this piece is:
			 *  1. White piece
			 *  2. Of unknown type
			 *  3. Not moved yet
			 * @brief Default constructor.
			 */
			Piece(piece_type tpe = unknown, piece_color col = white);

			/**
			 * @brief Copy constructor.
			 * @param other - source
			 */
			Piece(const Piece &other);

			/**
			 * @brief Destructor.	
			 */
			~Piece();

			/**
			 * @brief Get the piece's type
			 * @return Type
			 */
			piece_type type() const;

			/**
			 * @brief Get the piece's color ( white | black )
			 * @return Color
			 */
			piece_color color() const;

			/**
			 * @brief Check piece's color state
			 * @return true if piece is white
			 * @note Same as
			 * @code
			 * if ( piece.color() == ChEngn::white )
			 * {
			 *  	// routine
			 * }
			 * @endcode
			 */
			bool isWhite() const;

			/**
			 * @brief Check piece's color state
			 * @return true if piece is black
			 * @note Same as
			 * @code
			 * if ( piece.color() == ChEngn::black )
			 * {
			 * 		// routine
			 * }
			 * @endcode
			 */
			bool isBlack() const;

			/**
			 * @brief Check piece's type
			 * @return true if piece type is unknown
			 * @note Same as:
			 * @code
			 * if ( piece.type() == ChEngn::unknown )
			 * {
			 * 		// routine
			 * }
			 * @endcode
			 * @note Piece initialized by ChEngn::Piece::Piece() will be unknown
			 * type
			 */
			bool isUnknown() const;
			
			/** @brief Get piece movement flag
			 *  @return flag's value
			 */
			piece_movement_flag moveFlag() const;

			/**
			 * @brief Set Piece's type
			 * @param tpe - New piece's type
			 */
			void setType(piece_type);
			
			/**
			 * @brief Changes piece's color to white
			 */
			
			void setWhite();

			/**
			 * @brief Changes piece's colot to black
			 */
			void setBlack();
	
			/**
			 * @brief Sets Piece as moved
			 * @note It's not requered to always set this flag. For example this
			 * flag doesn't make sense if piece's type is ChEngn::bishop
			 * @warning You can only <b>set</b> this flag. You can't change this
			 * flag later
			 */
			void setMoved();

			/**
			 * Overloaded operation =. Will be copied type, color, moving flag
			 * @brief Overloaded operator =
			 * @param other - Source
			 */
			void operator = (const Piece& other);

			/**
			 * Compare two pieces. Pieces are equal if their types, color,
			 * moving flag are same.
			 * @brief Compare pieces
			 * @param other - Source
			 */
			bool operator == (const Piece& other) const;

			/**
			 * "Prints" piece in std::ostream
			 * @brief Overloaded operator << ()
			 * @param out - Stream for printing
			 * @param pce - Piece to print
			 */
			friend std::ostream& operator << (std::ostream &out, const Piece& pce);
		private:
			unsigned char m_piece;
	};
};


#endif
