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

#ifndef PGNTagList_h
#define PGNTagList_h

#include <fstream>
#include <vector>
#include "PGNTag.h"
#include "PGNMGlobals.h"

namespace pgn
{
	class PGNM_EXPORT TagList 
	{
		public:
		
			class PGNM_EXPORT iterator;
			friend class PGNM_EXPORT iterator;

			TagList();
			TagList(const TagList& src);

			virtual ~TagList();

			TagList& operator = (const TagList& src);
			bool operator == (const TagList& src) const;
			bool operator != (const TagList& src) const;
			Tag operator [] (const std::string& tagName) const;

			bool find(std::string tagName) const;
			void insert(const Tag& src);
			void erase(const Tag& src);
			int size() const;
		
			friend std::ostream& operator << ( std::ostream& os, const TagList& src);
			friend std::istream& operator >> ( std::istream& is, TagList& target);

		private:

			struct TagListData *hdata;
	};

	class PGNM_EXPORT TagList::iterator
	{
		public:

			iterator();
			iterator(const TagList &tl);
			iterator(const TagList &tl, int);
			iterator(const iterator&);
			~iterator();
			iterator& operator = (const iterator&);
			iterator& operator ++ ();
			iterator& operator ++ (int);
			Tag* operator -> () const;
			const Tag& operator * () const;
			bool operator == (const iterator&) const;
			bool operator != (const iterator&) const;

		private:
		
			struct iteratorData *hdata;
	};
};

#endif 

