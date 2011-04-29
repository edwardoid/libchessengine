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

#include <iostream>
#include <sstream>
#include <algorithm>
#include <PGNGameCollection.h>
#include <PGNTagList.h>
#include <PGNTag.h>
#include <PGNParser.h>

namespace pgn
{
	struct GameCollectionData 
	{
		std::vector<pgn::Game> games;
	};
};

pgn::GameCollection::GameCollection(): hdata( 0 ) 
{
	hdata = new pgn::GameCollectionData;
//	std::cout << "new GameCollectionData " << sizeof(*hdata) << std::endl; 
}

pgn::GameCollection::GameCollection(const pgn::GameCollection& src): hdata( 0 )
{
	hdata = new pgn::GameCollectionData;
	hdata->games = src.hdata->games;
//	std::cout << "new GameCollectionData " << sizeof(*hdata) << std::endl; 
}

pgn::GameCollection::~GameCollection() 
{
//	std::cout << "delete GameCollectionData " << sizeof(*hdata) << std::endl; 
	if ( 0 != hdata )
		delete hdata;
}

// TODO: ottimizzare algoritmo di sort
void pgn::GameCollection::sort(const pgn::Tag &key)
{
	for (int i=0; i<(int)hdata->games.size()-1; i++)
		for (int j=i+1; j<(int)hdata->games.size(); j++)
		{
			Tag tj = hdata->games[j].tags()[key.name()];
			Tag ti = hdata->games[i].tags()[key.name()];

			if (tj.value() < ti.value())
			{
				pgn::Game g = hdata->games[i];
				hdata->games[i] = hdata->games[j];
				hdata->games[j] = g;			

			}
		}
}

pgn::GameCollection& pgn::GameCollection::operator = (const pgn::GameCollection& src) 
{
	if (&src == this)
		return(*this);

	hdata->games = src.hdata->games;

	return *this;
}

void pgn::GameCollection::insert(const pgn::Tag& src)
{
	for (int i=0; i<(int)hdata->games.size(); i++)
	{
		hdata->games[i].tags().insert(src);
	}
}

void pgn::GameCollection::erase(const pgn::Tag& src)
{
	for (int i=0; i<(int)hdata->games.size(); i++)
	{
		hdata->games[i].tags().erase(src);
	}
}

void pgn::GameCollection::insert(const pgn::Game& game)
{
	hdata->games.push_back(game);
}

void pgn::GameCollection::erase(const pgn::Game& game)
{
	std::vector<pgn::Game>::iterator itr;
	itr = std::find(hdata->games.begin(), hdata->games.end(), game);	
	if (itr != hdata->games.end())
		hdata->games.erase(itr);
}

bool pgn::GameCollection::operator == (const pgn::GameCollection& src) const
{
	if (hdata->games.size() != src.hdata->games.size())
		return false;

	for (int i=0; i<(int)src.hdata->games.size(); i++)
	{
		if (hdata->games[i] != src.hdata->games[i])
			return false;
	}

	return true;
}

bool pgn::GameCollection::operator != (const pgn::GameCollection& src) const 
{ 
	return !(*this == src); 
}

std::ostream& pgn::operator << ( std::ostream& os, const pgn::GameCollection& src ) 
{
	for (int i=0; i<(int)src.hdata->games.size(); i++)
	{
		os << src.hdata->games[i] << std::endl;
	}

	return os;
}

std::istream& pgn::operator >> ( std::istream& is, pgn::GameCollection& src ) 
{
	std::string pgndata;
	std::string line;

	// TODO: si puo` fare meglio la copia in una stringa del contenuto
	// del file
	while (getline(is, line))
	{
		pgndata += line;
		pgndata += "\n";
	}
		
	std::string::const_iterator itr1 = pgndata.begin();
	std::string::const_iterator itr2 = pgndata.end();
	
	pgn::Parser parser;
	parser.getGameCollection(itr1, itr2, src);
}

int pgn::GameCollection::size() const
{ 
	return hdata->games.size(); 
}

void pgn::GameCollection::clear() 
{ 
	hdata->games.clear(); 
}

pgn::GameCollection::iterator pgn::GameCollection::begin() 
{ 
	pgn::GameCollection::iterator itr(*this);
	return itr;
}

pgn::GameCollection::iterator pgn::GameCollection::end() 
{ 
	pgn::GameCollection::iterator itr(*this, 0);
	return itr;
}

pgn::Game pgn::GameCollection::operator [] (const int idx) const 
{ 
	return hdata->games[idx]; 
}

//
// iterator
//

namespace pgn
{
	struct iteratorData 
	{
		std::vector<pgn::Game>::iterator it;
	};
};


pgn::GameCollection::iterator::iterator()
{
	hdata = new iteratorData;
}

pgn::GameCollection::iterator::iterator(const pgn::GameCollection &ml)
{
	hdata = new iteratorData;
	hdata->it = ml.hdata->games.begin();
}

pgn::GameCollection::iterator::iterator(const pgn::GameCollection &ml, int)
{
	hdata = new iteratorData;
	hdata->it = ml.hdata->games.end();
}

pgn::GameCollection::iterator::iterator(const pgn::GameCollection::iterator &other)
{
	hdata = new iteratorData;
	hdata->it = other.hdata->it;	
}

pgn::GameCollection::iterator::~iterator()
{
	delete hdata;
}

pgn::GameCollection::iterator& 
	pgn::GameCollection::iterator::operator = (const pgn::GameCollection::iterator& other) 
{
	if (&other == this)
		return *this;

	hdata->it = other.hdata->it;	

	return *this;
}

pgn::GameCollection::iterator& pgn::GameCollection::iterator::operator ++ ()
{
	hdata->it++;
	return (*this);
}

pgn::GameCollection::iterator& pgn::GameCollection::iterator::operator ++ (int)
{
	return (operator ++ ());
}

pgn::Game* pgn::GameCollection::iterator::operator -> () const
{
	return &(*hdata->it);
}

const pgn::Game& pgn::GameCollection::iterator::operator * () const
{
	return *(hdata->it);
}

bool pgn::GameCollection::iterator::operator == (const pgn::GameCollection::iterator& other) const
{
	if (hdata->it == other.hdata->it)
		return true;
	else
		return false;
}

bool pgn::GameCollection::iterator::operator != (const pgn::GameCollection::iterator& other) const
{
	return (!((*this) == other));
}

