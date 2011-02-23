#ifndef CHESS_ENGINE_PIECE
#define CHESS_ENGINE_PIECE

/**
 * @author Ed Sarkisyan
 * @version 0.0.1a
 */


/// @namespace ChEngn
namespace ChEngn
{
	/**
	 * @class ChEngn::Piece
	 * Provides basic interface for init some chess piece, eg "knight"
	 */
	class Piece
	{
		public:
			/**
			 * @brief Default constructor.
			 */
			Piece();

			/**
			 * @brief Copy constructor.
			 * @param other - source
			 */
			Piece(const Piece &other);

			/**
			 * @brief Destructor.	
			 */
			~Piece();
		private:
	};
};


#endif
