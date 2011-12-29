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

#ifndef CHESS_ENGINE_DEBUG_UTILS_H
#define CHESS_ENGINE_DEBUG_UTILS_H

// Useful macroses

// Swaps 2 variables. Requeres operator==() for both variables
#define SWAP(T, F, S) { T CE__TMP_VARIABLE = F; F = S; S = CE__TMP_VARIABLE; }

// Checks pointer. Throws exception if pointer is == 0 and prints error message with line and file name.
#define CHECK_PTR(P) { if(0 == P)\
		       {\
	       			printf("\e[1;31mBad pointer \"%s\" on line %d in file %s\e[0m\n",\
							QUOTATE(P) ,\
							__LINE__,\
							__FILE__);\
				throw "Bad pointer";\
		       } }

// Add quotation symbols for given expression
#define QUOTATE(STR) #STR

// Prints error message in red color
#define ERROR(MSG){   printf("\n\e[1;31mError: %s      \n\e[0m", MSG); }

// Prints warning message in blue color
#define WARNING(MSG){ printf("\n\e[1;34mWarning: %s    \n\e[0m", MSG); }

// Prints information message in green color;
#define INFO(MSG){    printf("\n\e[1;32mInformation: %s\n\e[0m", MSG); }

#endif // CHESS_ENGINE_DEBUG_UTILS_H

