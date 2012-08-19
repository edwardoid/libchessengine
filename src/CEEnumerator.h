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

#ifndef CHESS_ENGINE_ENUMERATOR
#define CHESS_ENGINE_ENUMERATOR

#include <iostream>
#include "CETable.h"
#include "CEPiece.h"


/**
 * @file CEEnumerator.h
 * @brief Here defined ChEngn::Enumetaror class.
 */


/// @namespace ChEngn Contains all typedefs, constants, classes defined in
//linchessengine
namespace ChEngn
{

	/**
	 * Defines Enumeration "side", e.g. is Enumeration for white player,
	 * or not
	 */
	enum EnumerationSide
	{

		/// Default value
		UndefinedSide = 0,

		/// White player's side
		WhiteSide,

		/// Black player's side
		BlackSide 
	};


	/**
	 * Enumerate possible moves in given deep 
	 * @class ChEngn::Enumerator
	 * @brief Enumerate possibile moves
	 */

	class Enumerator
	{
		public:

			/**
			 * Default constructor creates ChEngn::Enumerator whithout ChEngn::Table
			 * @code
			 * 		ChEngn::Enumerator tmpEnumerator;
			 * 		if ( tmpEnumerator.table() == 0 ) // <- will return true
			 * 		...
			 * @endcode
			 * 
			 * And enumeration deep will be set 0
			 * And side will be
			 *
			 * @warning:
			 * 		Enumeration process is hard process, if it's possible use
			 * 		small values for deep
			 * @brief Constructor
			 */
			Enumerator();

			/**
			 * Created ChEngn::Enumerator whis given table, side, deepness
			 * @param table Start position for enumeration
			 * @param enumSide Enumeration side, default value ChEngn::UndefinedSide
			 * @param deep Enumeration deep
			 * @warning:
			 * 		Enumeration process is hard process, if it's possible use
			 * 		small values for deep
			 *
			 * @brief Custom constructor
			 */
			Enumerator( const Table& table, EnumerationSide enumSide =  UndefinedSide , unsigned short deep = 2);


			/** Set enumeration deepness
			 * @brief Sets enumeration deepness
			 * @param deep Enumeration depness
			 */
			void setDeep(unsigned short deep);

			/** Set give table as start position
			 * @brief Initialize start position
			 * @param table Start position
			 */
			void setTable( const Table& table);

			/** Sets enumeration side
			 * @brief Sets enumeration side
			 * @param enumSide Enumeration side
			 */
			void setSide( EnumerationSide enumSide );
	
			/**
			 * Return Enumeration deepness
			 * @return Enumeration depness
			 */
			unsigned short deepness() const;

			/** Get start position table
			 * @return Start position
			 */
			Table* startPosition() const;
			
			/** Get Enumeration side
			 * @return Enumeration side
			 */
			EnumerationSide side() const;
		private:
			EnumerationSide m_side;
			unsigned short m_deep;
			Table* m_table;
	};
};


#endif
