#ifndef CHESS_ENGINE_TABLE
#define CHESS_ENGINE_TABLE
/**
 * @author Ed Sarkisyan
 * @version 0.0.1
 */


/**
 * @namespace ChEngn
 */
namespace ChEngn
{

	/**
	 * @class ChEngn::Table
	 *
	 * Provides basic manipulations whis chess table (no matter "virtual" ot
	 * "real". Find ChEngn::Piece, move them.
	 */
	class Table
	{
		public:
			/**
			 * @brief Default constructor.
			 */
			Table();

			/**
			 * @brief Copy constructor.
			 * @param other - Source.
			 */
			Table(const Table& other);

			/**
			 * @brief Destructor.
			 */
			virtual ~Table();
		private:
	};
};

#endif
