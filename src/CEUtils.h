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

#ifndef CHESS_ENGINE_UTILS
#define CHESS_ENGINE_UTILS

#include <string>

/**
 * @file CEUtils.h
 * @brief Here are defined ChEngn::Exception class.
 */


/// @namespace ChEngn Contains all typedefs, constants, classes defined in
//libchessengine
namespace CE
{
	/**
	 * @brief Converts given number to std::string
	 * @param num Number to convert
	 */
	std::string itostr( int num );

	/**
	 * @brief Converts given number to std::string
	 * @param num Number to convert
	 */
	const char* itoa( int num );
};


#endif // CHESS_ENGINE_UTILS
