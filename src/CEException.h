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

#ifndef CHESS_ENGINE_EXCEPTION
#define CHESS_ENGINE_EXCEPTION

#include <string>
#include <exception>
#include <PGNPly.h>
/**
 * @file CEException.h
 * @brief Here are defined ChEngn::Exception class.
 */


/// @namespace ChEngn Contains all typedefs, constants, classes defined in
//libchessengine
namespace ChEngn
{

	/// Represents unknown exception's additional information
	static const char* UNKNOWN_ERROR = "Unknown error";

	/**
	 * Represents exception's additional information if ChEngn::Engine tryes to
	 * get access square which isn't exist
	 */
	static const char* DEST_OUT_OF_RANGE = "Destination square is out of range";

	/**
	 * Represents exception's additional information if Ply's piece
	 * tryes to capture piece whith same color
	 */
	static const char* SAME_COLOR = "Ply's and destination square's piece are same color";

	/**
	 * Represents exception text, when no suitable piece can make given move;
	 */
	static const char* NO_SUITABLE_PIECE = "No suitable piece for move.";

	/**
	 */
	static const char* UNKNOWN_CAPTURE = "Cat't capture \"unknown\" piece";


	/**
	 * @brief Implements all exception which will be generated ty ChEngn::Engine
	 * while trying to make move which i sincorrect.
	 */
	class BadMove: std::exception
	{
		public:
			
			/**
			 * @brief constructor
			 * @param p pgn::Ply which can be done a.t.m.
			 * @param comm Addiotional comment
			 * @param moveNum Move number which can't be completly done
			 */
			BadMove( pgn::Ply p, std::string comm,  int moveNum = 0 ) throw():m_ply( p ),
																			  m_comm( comm ),
																		  m_num( moveNum ) {} ;
			/**
			 * @brief Destructor
			 */
			~BadMove()throw(){};

			/**
			 * @brief Bind addiotional information to exception;
			 * @param comm Additional comment
			 */
			void bindComment( std::string comm )throw() { m_comm = comm; };

			void bindNumber( int num ) throw() { m_num = num; };

			/**
			 * @brief Get binded information
			 */
			std::string comment() throw() { return m_comm; };

			/**
			 * @brief Basic information about given exception
			 */
			virtual const char* what() throw();
		private:
			pgn::Ply m_ply;
			int m_num;
			std::string m_comm;
			
	};
};


#endif // CHESS_ENGINE_EXCEPTION
