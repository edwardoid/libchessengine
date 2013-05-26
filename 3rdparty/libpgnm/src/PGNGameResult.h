//
// Copyright (C) 2002 Andrea Vinzoni <vinzoni@users.sourceforge.net>
//
//     This file is part of pgnlib.
//
//     pgnlib is free software; you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation; either version 2 of the License, or
//     (at your option) any later version.     
// 
//     pgnlib is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
// 
//     See the GNU General Public License for more details. 
// 
//     You should have received a copy of the GNU General Public License
//     along with pgnlib; if not, write to the Free Software Foundation, 
//     Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
// 

#ifndef PGNGameResult_h
#define PGNGameResult_h

#include "PGNMGlobals.h"
#include <fstream>
#include <string>

/**
 * @brief global namespace for libpgnm
 * @namespace pgn
 */
namespace pgn
{
	/**
	 * @class PGNM_EXPORT GameResult
	 * @brief Stores information about game result.
	 */
	class PGNM_EXPORT GameResult 
	{
		public:
	
			/**
			 * @brief Default constructor
			 */
			GameResult();

			/**
			 * @brief Extracts result information from given string, and
			 * constructs object by extracted information.
			 * @param s Source string.
			 */
			GameResult(std::string s);

			/**
			 * @brief Copy-constructor.
			 */
			GameResult(const GameResult& src);

			/**
			 * @brief Copies information from other object.
			 * @param src Source result.
			 */
			GameResult& operator = (const GameResult& src);

			/**
			 * @brief Compares 2 game results.
			 * @param src Source result.
			 * @return true if results are equal(same).
			 */
			bool operator == (const GameResult& src) const;

			/**
			 * @brief Negative verion of GameResult::operator==().
			 */
			bool operator != (const GameResult& src) const;

			/**
			 * @brief Checks is result "1-0".
			 * @return true if white player wins.
			 */
			bool isWhiteWin() const;

			/**
			 * @brief Checks is result "0-1".
			 * @return true if black player wins.
			 */
			bool isBlackWin() const;

			/**
			 * @brief Checks is result "1/2-1/2"
			 * @return true if game finished as draw.
			 */
			bool isDrawn() const;

			/**
			 * @brief Checks is game's result not "1-0", "0-1" or "1/2-1/2".
			 * @return true If there is no result specified in game, or result
			 * is "*".
			 */
			bool isUnknown() const;

			/**
			 * @brief Prints result to given stream.
			 * @param os Strem to print.
			 * @param src Result to print.
			 * 
			 * Result will be printed as "1-0" or "0-1" or "1/2-1/2".
			 */
			friend std::ostream& operator << ( std::ostream& os, const GameResult& src);

		private:

			char result_;
	};
};

#endif 

