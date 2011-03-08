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

#ifndef CHESS_ENGINE_TABLE
#define CHESS_ENGINE_TABLE
#include "CEPiece.h"
#include <iostream>
/**
 * @file CETable.h Here defined ChEngn::Table, ChEngn::table_size,
 * @brief ChEngn::default_table_height, ChEngn::default_table_width
 */


/**
 * @namespace ChEngn Contains all typedefs, constans, classes defined in
 * libchessengine
 */
namespace ChEngn
{

	/**
	 * @struct table_size
	 * Provides information about table size
	 * @brief Table dimensions
	 */
	struct table_size
	{
		unsigned int height;
		unsigned int width;
	};


	/// Standart table height
	const unsigned int default_table_height = 8;

	/// Standart table width
	const unsigned int default_table_width = 8;

	/**
	 * Provides basic manipulations whis chess table (no matter "virtual" ot
	 * "real". Find ChEngn::Piece, move them.
	 * @class ChEngn::Table
	 * @brief Chess board
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

			/**
			 * @brief Get table's size
			 */
			const table_size size() const;

			/**
			 * @brief Get table's height
			 * @return height
			 */
			const unsigned int height() const;

			/**
			 * @brief Get table's width
			 * @return width
			 */
			const unsigned int width() const;
			
			/**
			 * @brief Get current table state
			 * @return Current table state
			 * @warning If you don't gonna change the table use const-version
			 */
			Piece** table();

			
			/**
			 * 	Get piece from table.
			 * 	@brief Return piece at given numeric position.
			 * 	@param row - Piece's position numeric row.
			 * 	@param column  - Piece's position numeric column.
			 * 	@return - Pointer to piece, if row and/or column are invalid
			 * 	0 will be returned.
			 */
			Piece* pieceAt(unsigned int column, unsigned int row) const;

			/**
			 * 	Get piece from table.
			 * 	@brief Return piece at given numeric position.
			 * 	@param column - Piece's position column as character, like 'd'
			 * 	@param row - Piece's position row as character, like '3'.
			 * 	@return - Pointer to piece, if row and/or column are invalid
			 * 	0 will be returned.
			 */
			Piece* pieceAtC(char column, char row) const;

			/**
			 * @brief Set table for beginig gaming
			 * @warning Function will do changes if table size is 8x8. In
			 * another case nothing will be done
			 */
			void resetComplect();
			
			/**
			 * Copies given table to current.
			 * @brief Overloaded operation =
			 * @param other - Source
			 */
			void operator = (const Table& other);

			/**
			 * "Prints" table into std::ostream
			 * @brief Overloaded operator << ()
			 * @param out - Stream for printing
			 * @param tbl - table to print
			 */
			friend std::ostream& operator << (std::ostream &out, const Table& tbl);
		private: //methods

			void getMemoryForTable();
			void fillDefault();
			void cleanMemory();
			void setDefaultComplect();
		private: // variables

			table_size m_size;
			Piece **m_table;
	};
};

#endif
