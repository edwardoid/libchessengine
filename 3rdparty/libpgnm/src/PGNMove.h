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

#ifndef PGNMove_h
#define PGNMove_h

#include <fstream>
#include "PGNPly.h"
#include "PGNMGlobals.h"

/**
 * @file PGNMove.h Contains information about storing simple move extracted from
 * PGN file.
 */


/**
 * @brief global namespace for libpgnm
 * @namespace pgn
 */
namespace pgn 
{
	/**
	 * @brief Represents simple move.
	 * @class PGNM_EXPORT Move
	 */
	class PGNM_EXPORT Move 
	{
		public:
	
			/**
			 * @brief Copy-constructor
			 * @param src Source move.
			 */
			Move(const Move& src);

			/**
			 * @brief constructs move by given white and black players plyes.
			 * @param white White players ply.
			 * @param black Black players ply.
			 * @param int Move number.
			 */
			Move(const Ply *white, const Ply *black, int number = 1 ) ;
			
			/**
			 * @brief Destructor.
			 */
			virtual ~Move();

			/**
			 * @brief Copies given move to current.
			 * @param Source move.
			 * @return Reference to current move.
			 */
			Move& operator = (const Move& src);

			/**
			 * @brief Check is given move and current move equal.
			 * @param src Source move.
			 * @return true if moves are equal.
			 */
			bool operator == (const Move& src) const;

			/**
			 * @brief Negative veriosn of Move::operator==().
			 * @param src Source move.
			 * @return true if moves are not equal.
			 */
			bool operator != (const Move& src) const;

			/**
			 * @brief Checks is move checkmate( e.g. does move contain #
			 * character ).
			 * @return true is move is checkmate.
			 */
			bool isCheckMate() const;

			/**
			 * @brief Get white player's ply.
			 * @return Pointer to ply, or if there is no ply, returns 0.
			 */
			Ply* white() const;
		
			/**
			 * @brief Get black player's ply.
			 * @return Pointer to ply, or if there is no ply, returns 0.
			 */
			Ply* black() const;


			/**
			 * @brief Convert move to string using <b>short</b> PGN notation.
			 * @return Converted move.
			 */
			std::string toStdString();
		
			/**
			 * @brief Prints move to given stream.
			 * @param os Stream to print.
			 * @param src Move to print.
			 */
			PGNM_EXPORT friend std::ostream& operator << ( std::ostream& os, const Move& src);
			
			/**
			 * @brief Converts given number to string.
			 * @note Function use converts from/to decimal number.
			 * @return converted result.
			 */
			static std::string itoa(int n);
		private:
	
			struct MoveData *hdata;
	};
};

#endif 

