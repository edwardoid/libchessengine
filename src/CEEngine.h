#ifndef CHESS_ENGINE_ENGINE
#define CHESS_ENGINE_ENGINE

#include <CETable.h>
#include <PGNGame.h>
#include <PGNMoveList.h>
#include <iostream>

/**
 * @file Provides access to current game. Can make moves, get table state ( Virtual
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
	 **/

	 /**
	  * Every library user will use "Virtual tables". E.g. you get current table
	  * state, and then you can make changes, but all your changes will not
	  * change real table.
	  */
	typedef ChEngn::Table VirtualTable;

	class Engine
	{
		public:
			/**
			 * @brief Default constructor
			 */
			Engine();

			/**
			 * @brief Copy constructor
			 * @param other source
			 */
			Engine(const Engine &other);

			/**
			 * Creates Engine from pgn::Game
			 * @brief Constructor.
			 * @param gm Game from an opened *.pgn file
			 */
			Engine(const pgn::Game &gm);

			/**
			 * @brief Destructor
			 */
			virtual ~Engine();

			/**
			 * @brief Get an <b>copy</b> of current game table
			 * @return Current table copy
			 */
			VirtualTable getVirtualTable() const;

			/**
			 * @brief return loaded moves
			 */
			pgn::MoveList* moves();

			/**
			 * Gets pgn::MoveList::iterator to current move. If there are no
			 * aviable moves return vaule will be equal to @code moves()->end()
			 * @endcode, also if
			 * there are no maked moves the return value will be equal to
			 * @code moves()->begin(); @endcode
			 * @brief Iterarator to next move
			 * @return Iterator to next move
			 * @warning Before using iterator chech is return value different
			 * from @code move()->end(); @endcode
			 * @warning You should use the return vallue very careful. Everytime
			 * check is iterator valid.
			 */
			pgn::MoveList::iterator nextMove();
			

			/**
			 * @brief "Print" current table
			 */
			friend std::ostream& operator << (std::ostream &out, const Engine& engn );
		private: // functions

		private: // variables
			VirtualTable m_table;
			pgn::MoveList m_moves;
			pgn::MoveList::iterator m_currentMoveIt;
	};
};

#endif
