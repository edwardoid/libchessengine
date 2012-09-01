//
// Copyright (C) 2011 Edward Sarkisyan <edward.sarkisyan@gmail.com>
//
//     This file is part of libchessengine.
//
//     libchessengine is free software; you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation; either version 2 of the License, or
//     (at your option) any later version.     
// 
//     libchessengine is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
// 
//     See the GNU General Public License for more details. 
// 
//     You should have received a copy of the GNU General Public License
//     along with pgnlib; if not, write to the Free Software Foundation, 
//     Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

#ifndef CHESS_ENGINE_ENGINE
#define CHESS_ENGINE_ENGINE

#include "CEGlobal.h"
#include "CETable.h"
#include <PGNGame.h>
#include <PGNMoveList.h>
#include <PGNPly.h>
#include <iostream>

/**
 * @file CEEngine.h  Provides access to current game. Can make moves, get table state ( Virtual
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
	  * Every library user will use "Virtual tables". E.g. you get current table
	  * state, and then you can make changes, but all your changes will not
	  * change real table.
	  */
	typedef ChEngn::Table VirtualTable;


	/**
	 * Provides access to current game. Can make moves, get table current state
	 * (Virtual Table).
	 * @class ChEngn::Engine
	 * @brief Make moves.
	 * @note This class <b>does not</b> manipulate pgn files.
	 **/
	class CE_EXPORT Engine
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
			~Engine();

			/**
			 * @brief Get an <b>copy</b> of current game table
			 * @return Current table copy
			 */
			VirtualTable getVirtualTable() const;

			/**
			 * @brief Get loaded moves
			 * @return moves in loaded game, if there are no loaded game will be
			 * returned empty pgn::MoveList
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
			 * @warning Before using iterator, check is return value different
			 * from @code move()->end(); @endcode
			 * @warning You should use the return value very careful. Everytime
			 * check is iterator valid.
			 */
			pgn::MoveList::iterator nextMove();
			
			/**
			 * Try to make next move.
			 * @brief make next move.
			 * @return true if move can was successefully did. Else -  fale will
			 * be returned. False will be returned if no moves is aviable.
			 */
			bool makeNextMove();

			/**
			 * Try to make next half-move.
			 * @brief make next half-move.
			 * @return true if move can was successefully did. Else -  fale will
			 * be returned. False will be returned if no moves is aviable.
			 */
			bool makeNextHalfMove();
			
			/** Tryes to make move.
			 * OK if white player's move did successefully AND black player's
			 * move did successefully.
			 * @brief Make move
			 * @param move - Move which must to do
			 * @return true if move has been succesefully done. else - otherway
			 */
			bool makeMove(pgn::Move& move);

			/**
			 * Make simple ply move
			 * @brief Make ply's move
			 * @param pl - Ply to do
			 * @param isWhite - true if pl is white player's ply
			 * @return true if successefully, false - otherway.
			 */
			bool makePly(const pgn::Ply* pl, bool isWhite);

			/**
			 * @brief "Print" current table
			 */
			friend std::ostream& operator << (std::ostream &out, const Engine& engn );

		private: // variables
			bool m_halfMove;
			Table m_table;
    		pgn::MoveList::iterator m_currentMoveIt;
			pgn::MoveList m_moves;
	};
};

#endif
