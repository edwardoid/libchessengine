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

#ifndef PGNCommentText_h
#define PGNCommentText_h

#include "PGNMGlobals.h"
#include <fstream>
#include <string>

/// @file PGNCommentText.h

/**
 * @brief global namespace for libpgnm
 * @namespace pgn
 */
namespace pgn
{
	/**
	 * @class PGNM_EXPORT CommentText
	 * @brief Provides comment to move.
	 */
	class PGNM_EXPORT CommentText 
	{
		public:
		
			/**
			 * @brief Default constructor.
			 */
			CommentText();

			/**
			 * @brief Constructs comment by given text.
			 * @param s Comment text.
			 */
			CommentText(const std::string &s);

			/**
			 * @brief Creates object as copy of given one.
			 * @param src Object which copy will be constructed.
			 */
			CommentText(const CommentText& src);

			virtual ~CommentText();

			/**
			 * @param src Copies given comment to current object.
			 * @param src Source object.
			 */
			CommentText& operator = (const CommentText& src);

			/**
			 * @brief Checks are comments equal.
			 * @param src Comment with which will be compaired.
			 * @return true if comments are equal, false in onther case
			 */
			bool operator == (const CommentText& src) const;

			/**
			 * @brief Negative variant of pgn::CommentText::operator=(const
			 * CommentText).
			 */
			bool operator != (const CommentText& src) const;
		
			/**
			 * @brief Represents comment as std::string.
			 */
			std::string toStdString();

			/**
			 * @brief Prints comment to stream.
			 * @param os Stream to print.
			 * @param src Comment which must be printed.
			 */
			friend std::ostream& operator << ( std::ostream& os, const CommentText& src);

		private:

			struct CommentTextData *hdata;

	};
};

#endif 

