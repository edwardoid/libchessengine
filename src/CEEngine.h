//
// Copyright (C) 2002 Edward Sarkisyan <edward.sarkisyan@gmail.com>
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

#include <CETable.h>
#include <PGNGame.h>
#include <PGNMoveList.h>
#include <PGNPly.h>
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
			 * @warning Before using iterator chech is return value different
			 * from @code move()->end(); @endcode
			 * @warning You should use the return vallue very careful. Everytime
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
			 * @make ply's move
			 * @param pl - Ply to do
			 * @param isWhite - true if pl is white player's ply
			 * @return true if successefully, false - otherway.
			 */
			bool makePly(const pgn::Ply* pl, bool isWhite);

			/**
			 * @brief "Print" current table
			 */
			friend std::ostream& operator << (std::ostream &out, const Engine& engn );

			/**
			 * Checks for emptyness given horisontal. (from .... to)
			 * @brief Check horisontal for emptyness
			 * @param from - source column
			 * @param to - destination column
			 * @param row - checking row
			 * @param table - table to searching
			 * @return true if line is empty, false if there're some figure or
			 * table is invalid
			 */
			static bool checkForEmptynessH(char from, char to, char row, VirtualTable* table);

			/**
			 * Checks for emptyness given vertical. (from .... to)
			 * @brief Check horisontal for emptyness
			 * @param from - source row
			 * @param to - destination row
			 * @param row - checking column
			 * @param table - table to searching
			 * @return true if vertical is empty, false if there're some figure or
			 * table is invalid
			 */
			static bool checkForEmptynessV(char from, char to, char column, VirtualTable* table);

			/**
			 * Checks for emptyness given diagonal. (from .... to)
			 * @brief Check horisontal for emptyness
			 * @param fromC - source column
			 * @param fromR - source row
			 * @param toC - destination column
			 * @param roR - destination row
			 * @param table - table to searching
			 * @return true if diagonal is empty, false if there're some figure or
			 * table is invalid
			 */
			static bool checkForEmptynessDiagonal(char fromC, char fromR, char toC, char toR, VirtualTable* table);


		protected: //protected functions

			/** Tryes to make pawn's move)
			 * @brief Makes pawn's move
			 * @return true if ply has been done successefully
			 * @param ply - Ply to do
			 * @param is isWhite - True if ply's owner is white player.
			 */
			bool makePawnPly( const pgn::Ply* ply, bool isWhite);
	
			/** Tryes to make knight's move)
			 * @brief Makes knight's move
			 * @return true if ply has been done successefully
			 * @param ply - Ply to do
			 * @param is isWhite - True if ply's owner is white player.
			 */	
			bool makeKnightPly( const pgn::Ply* ply, bool isWhite);

			/** Tryes to make bishop's move)
			 * @brief Makes bishop's move
			 * @return true if ply has been done successefully
			 * @param ply - Ply to do
			 * @param is isWhite - True if ply's owner is white player.
			 */	
			bool makeBishopPly( const pgn::Ply* ply, bool isWhite);

			/** Tryes to make bishop's move)
			 * @brief Makes bishop's move
			 * @return true if ply has been done successefully
			 * @param ply - Ply to do
			 * @param is isWhite - True if ply's owner is white player.
			 */	
			bool makeRookPly( const pgn::Ply* ply, bool isWhite);

			/** Tryes to make queen's move)
			 * @brief Makes queen's move
			 * @return true if ply has been done successefully
			 * @param ply - Ply to do
			 * @param is isWhite - True if ply's owner is white player.
			 */	
			bool makeQueenPly( const pgn::Ply* ply, bool isWhite);
		
			/** Tryes to make king's move)
			 * @brief Makes kings's move
			 * @return true if ply has been done successefully
			 * @param ply - Ply to do
			 * @param is isWhite - True if ply's owner is white player.
			 */	
			bool makeKingPly( const pgn::Ply* ply, bool isWhite);

			/** Tryes to make short castling
			 * @brief Makes short castling move
			 * @return true if castling has been done successefully
			 * @param is isWhite - True if castling  owner is white player.
			 */	
			bool makeShortCastling( bool isWhite);


			/** Tryes to make long castling
			 * @brief Makes long castling move
			 * @return true if castling has been done successefully
			 * @param is isWhite - True if castling  owner is white player.
			 */	
			bool makeLongCastling( bool isWhite);

		private: // functions
		private: // variables
			bool m_halfMove;
			VirtualTable m_table;
			pgn::MoveList m_moves;
			pgn::MoveList::iterator m_currentMoveIt;
	};
};

#endif
