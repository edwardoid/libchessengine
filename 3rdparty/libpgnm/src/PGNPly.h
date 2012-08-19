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

#ifndef PGNPly_h
#define PGNPly_h

#include <fstream>
#include <string>
#include <vector>
#include "PGNM.h"
#include "PGNPiece.h" 
#include "PGNSquare.h" 
#include "PGNCommentText.h"

/**
 * @brief global namespace for libpgnm
 * @namespace pgn
 */
namespace pgn
{
	/**
	 * @class PGNM_EXPORT Ply
	 * @brief Represents simple half-move.
	 */
	class PGNM_EXPORT Ply 
	{
		public:
			
			/**
			 * @brif Copy-constructor.
			 * @param src Source ply.
			 */
			Ply(const Ply& src);

			/**
			 * @brief Constructs ply by extracting information from given
			 * string.
			 * @param ply_text Text to parse.
			 */
			Ply(const std::string &ply_text);

			/**
			 * @brief Destructor.
			 */
			virtual ~Ply();
			
			/**
			 * @brief Copies given ply to current.
			 * @param Source ply.
			 * @return Reference to current ply.
			 */
			Ply& operator = (const Ply& src);

			/**
			 * @brief Check is given ply and current ply equal.
			 * @param src Source ply.
			 * @return true if plyes are equal.
			 */
			bool operator == (const Ply& src) const;
			
		 	/**
			 * @brief Negative veriosn of Ply::operator==().
			 * @param src Source ply.
			 * @return true if plyes are not equal.
			 */	
			bool operator != (const Ply& src) const;
		
			/**
			 * @brief Checks is ply long castle( e.g. does ply contain O-O-O
			 * character ).
			 * @return true is ply is long castle.
			 */
			bool isLongCastle() const;
			
			/**
			 * @brief Checks is ply short castle( e.g. does ply contain O-O
			 * character ).
			 * @return true is ply is short castle.
			 */
			bool isShortCastle() const;
			
			/**
			 * @brief Checks is ply capture( e.g. does ply contain x
			 * character ).
			 * @return true is ply is capture.
			 */
			bool isCapture() const;
			
			/**
			 * @brief Checks is ply check( e.g. does ply contain +
			 * character ).
			 * @return true is ply is check.
			 */
			bool isCheck() const;
			
			/**
			 * @brief Checks is ply checkmate( e.g. does ply contain #
			 * character ).
			 * @return true is ply is checkmate.
			 */
			bool isCheckMate() const;

			/**
			 * @brief Bind comment to the ply.
			 * @param comment Comment to bind.
			 */
			void bindComment(const CommentText &comment);
			
			/**
			 * @brief Remove bound comment.
			 */
			void unbindComment();
			
			/**
			 * @brief Get information about square from where ply has been done.
			 * @return Row or square from where move has been done. If there is
			 * nno square provided with ply '-' will be returned.
			 * @see http://http://en.wikipedia.org/wiki/Portable_Game_Notation for
			 * more information about PGN notation.
			 * @note Situation when row and column is provided with ply is
			 * ignored because it's happend very rarely.
			 */
			char fromSquare() const;

			/**
			 * @brief Get information about destination square.
			 * @return Destination square.
			 */
			Square toSquare() const;

			/**
			 * @brief Get information about piece which makes ply.
			 * @return Piece which makes ply.
			 */
			Piece piece() const;

			/**
			 * @Gets information about promoted to ply piece.
			 * @return Provided piece. If there is no provided piece 0 will be
			 * returned.
			 */
			Piece* promoted() const;
			
			/**
			 * @brief Converts ply to string.
			 * @return Converted verision.
			 */
			std::string toStdString() const;

			/**
			 * @brief Prints ply to given stream.
			 * @param os Stream to print.
			 * @param src Printing ply.
			 */
			friend std::ostream& operator << ( std::ostream& os, const pgn::Ply& src);

		private:

			struct PlyData *hdata;
	};
};

#endif 

