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

#ifndef PGNMoveList_h
#define PGNMoveList_h

#include <fstream>
#include <vector>
#include <set>
#include <string>
#include <PGNMove.h>
#include <PGNGameResult.h>

namespace pgn
{
	class MoveList 
	{
		public:

			class iterator;
			friend class iterator;
		
			MoveList();
			MoveList(const MoveList& src);

			virtual ~MoveList();

			MoveList& operator = (const MoveList& src);
			bool operator == (const MoveList& src) const;
			bool operator != (const MoveList& src) const;
			Move operator [] (int idx);

			void insert(const Move& src);
			bool find(const Move& src) const;
			int size() const;
			iterator begin() const;
			iterator end() const;

			std::string toStdString();
			friend std::ostream& operator << ( std::ostream& os, const MoveList& src);

		private:

			struct MoveListData *hdata;
		
	};


	class MoveList::iterator
	{
		public:

			iterator();
			iterator(const MoveList &ml);
			iterator(const MoveList &ml, int);
			iterator(const iterator&);
			~iterator();
			iterator& operator = (const iterator&);
			iterator& operator ++ ();
			iterator& operator ++ (int);
			Move* operator -> () const;
			const Move& operator * () const;
			bool operator == (const iterator&) const;
			bool operator != (const iterator&) const;

		private:
		
			struct iteratorData *hdata;
	};

};

#endif 

