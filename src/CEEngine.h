#ifndef CHESS_ENGINE_ENGINE
#define CHESS_ENGINE_ENGINE

/**
 * @author Edward Sarkisyan
 * @version 0.0.1a
 * @license GPL
 *
 * Provides access to current game. Can make moves, get table state ( Virtual
 * Table)
 * 
 * @note This class <b>does not</b> manipulate pgn files.
 */


/** @namespace ChEngn contains all classes, structs, constants to work whis
 * library.
 */
namespace ChEngn
{
	/**
	 * @class ChEngn::Engine provides most functionality
	 * Provides access to current game. Can make moves, get table current state
	 * (Virtual Table)
	 * @note This class <b>does not</b> manipulate pgn files.
	 * */
	class Engine
	{
		public:
			/**
			 * @brief default constructor
			 */
			Engine();

			/**
			 * @brief copy constructor
			 * @param other source
			 */
			Engine(const Engine &other);

			/**
			 * @brief destructor
			 */
			virtual ~Engine();
		private:

			/// @TODO all work :)
	};
};

#endif
