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
#include "PGNPiece.h" 
#include <PGNSquare.h> 
#include <PGNCommentText.h>

namespace pgn
{
	class Ply 
	{
		public:

			Ply(const Ply& src);
			Ply(const std::string &ply_text);

			virtual ~Ply();

			Ply& operator = (const Ply& src);
			bool operator == (const Ply& src) const;
			bool operator != (const Ply& src) const;

			bool isLongCastle() const;
			bool isShortCastle() const;
			bool isCapture() const;
			bool isCheck() const;
			bool isCheckMate() const;
			void bindComment(const CommentText &comment);
			void unbindComment();

			char fromSquare() const;
			Square toSquare() const;
			Piece piece() const;
			Piece* promoted() const;

			std::string toStdString() const;
			friend std::ostream& operator << ( std::ostream& os, const pgn::Ply& src);

		private:

			struct PlyData *hdata;
	};
};

#endif 

