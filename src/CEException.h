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
/**
 * @file CEException.h
 * @brief Here are defined ChEngn::Exception class.
 */


/// @namespace ChEngn Contains all typedefs, constants, classes defined in
//libchessengine
namespace ChEngn
{
	/// @namespace ErrorCodes contains definition of all error codes
	namespace ErrorCodes
	{
		/// Useless code, used as deafult value, for example in copy-constructor
		const int OK = 0;

		/**
		 * Used when ChEngn::Engine tryes to make ply, but can't find piece
		 * which has been moved
		 */
		const int CAN_T_FIND_SOURCE_PIECE = -1;

		/**
		 * Used when ChEngn::Engine tryes to make ply, but can't find
		 * destination piece
		 */
		const int CAN_T_FIND_DESTINATION_PIECE = -2;

		/**
		 * Used when castling can't be do. Chech chess rules for cases
		 * when this exception can be used
		 */
		const int CAN_T_MAKE_CASTLING = -3;

		/**
		 * Used when ply pointer given to
		 * ChEngn::Engine::make<PieceType>Ply is equal to 0
		 */
		const int PLY_S_POINTER_IS_NULL = -4;

		/** 
		 * Used when uses tryes to get access to whong piece from
		 * ChEngn::Table
		 */
		const int OUT_OF_RANGE= -5;

		/// @typedef ERROR_CODE Empty typedef for nice code :)
		typedef int ERROR_CODE;
	};


	/**
	 * @namespace ErrorMessages contains all standart error's messages
	 */
	namespace ErrorMessages
	{

		/// Useles message
		const std::string OK = "Everything is ok";

		const std::string CAN_T_FIND_SOURCE_PIECE = "Can't find source piece";
		const std::string CAN_T_FIND_DESTINATION_PIECE = "Can't find  destination piece";
		const std::string PLY_S_POINTER_IS_NULL = "Given Ply's pointer is == 0"; 
		const std::string OUT_OF_RANGE= "Trying to acces bad position in table"; 

		/// @typedef ERROR_MSG Empty typedef for nice code :)
		typedef std::string ERROR_MSG;
	};


	class Exception
	{
		public:
			/**
			 * Default constructor: Creates Exception whith given error code and
			 * error message.
			 * @param errCode Exception's error code. Default value: ChEngn::ErrorCodes::OK
			 * @param errMsg Exception's error message. Default value:
			 * ChEngn::ErrorMessages::OK
			 */
			Exception( const ErrorCodes::ERROR_CODE errCode = ErrorCodes::OK,
					   const ErrorMessages::ERROR_MSG errMsg = ErrorMessages::OK);

			/// @brief Copy-constructor
			Exception( const Exception& other );

			/// Destructor
			~Exception() {};

			/**
			 * @brief Get error code
			 * @return Current error code
			 */
			int code() const { return m_code; };

			/**
			 * @brief Get exception message
			 * @return Current error text
			 */ 
			std::string what() const{ return m_msg; };

			/**
			 * @brief Sets error code
			 * @param code Error code
			 */
			void setCode( const int code ) { m_code = code; };

			/**
			 * @brief Sets error message
			 * @param mess Error message
			 */
			void setMessage( std::string mess ) { m_msg = mess; };
		private:
			int m_code;
			std::string m_msg;
	};
};


#endif // CHESS_ENGINE_EXCEPTION
