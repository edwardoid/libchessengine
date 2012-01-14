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
#include <stdexcept>
#include <PGNMove.h>
#include <stdlib.h>

namespace pgn
{
	struct MoveData 
	{
		bool complete;
		int number;
		pgn::Ply *white;
		pgn::Ply *black;
	};
};

pgn::Move::Move(const pgn::Move& src) 
{
	hdata = new pgn::MoveData;

	hdata->complete = src.hdata->complete;
	hdata->number = src.hdata->number;
	if (src.hdata->white)
		hdata->white = new pgn::Ply(*(src.hdata->white));
	else
		hdata->white = 0;
	if (src.hdata->black)
		hdata->black = new pgn::Ply(*(src.hdata->black));
	else
		hdata->black = 0;
//	std::cout << "new MoveData " << sizeof(*hdata) << std::endl; 
}

pgn::Move& pgn::Move::operator = (const pgn::Move& src) 
{
	std::cout << "entro dentro qiu" << std::endl;
	if (&src == this)
		return(*this);

	hdata->complete = src.hdata->complete;
	hdata->number = src.hdata->number;
	if (src.hdata->white)
	{
		delete hdata->white;
		hdata->white = new pgn::Ply(*(src.hdata->white));
	}
	else
		hdata->white = 0;
	if (src.hdata->black)
	{
		delete hdata->black;
		hdata->black = new pgn::Ply(*(src.hdata->black));
	}
	else
		hdata->black = 0;

	return *this;
}

pgn::Move::Move(const pgn::Ply *white, const pgn::Ply *black, int number)
{
	hdata = new pgn::MoveData;

	hdata->number = number;
	if (white)
		hdata->white = new Ply(*white);
	else
		hdata->white = 0;
	if (black)
		hdata->black = new Ply(*black);
	else
		hdata->black = 0;

	hdata->complete = (hdata->white && hdata->black);
//	std::cout << "new MoveData " << sizeof(*hdata) << std::endl; 
}

pgn::Move::~Move() 
{
//	std::cout << "deleting MoveData " << sizeof(*hdata) << std::endl; 
	
	if( 0 != hdata->white )
		delete hdata->white;
	if( 0 != hdata->black )
		delete hdata->black;
	
	delete hdata;
}

bool pgn::Move::operator == (const pgn::Move& src) const
{
	if (hdata->complete != src.hdata->complete)
		return false;
	if (hdata->number != src.hdata->number)
		return false;
	if ((hdata->white == 0) && (src.hdata->white != 0))
		return false;
	else if ((hdata->white != 0) && (src.hdata->white == 0))
		return false;
	else if ((hdata->white != 0) && (src.hdata->white != 0) &&
			*(hdata->white) != *(hdata->white))
		return false;
	if ((hdata->black == 0) && (src.hdata->black != 0))
		return false;
	else if ((hdata->black != 0) && (src.hdata->black == 0))
		return false;
	else if ((hdata->black != 0) && (src.hdata->black != 0) &&
			*(hdata->black) != *(hdata->black))
		return false;

	return true;
}

std::string pgn::Move::toStdString()
{
	std::string res = "";
	if (hdata->white && hdata->black)
	{
		
		res = itoa(hdata->number);
		res += ". ";
		res += hdata->white->toStdString();
		res += " ";
		res += hdata->black->toStdString();
	}
	else if (hdata->white)
	{
		res = itoa(hdata->number);
		res += ". ";
		res += hdata->white->toStdString();
	}
	else if (hdata->black)
	{
		res = itoa(hdata->number);
		res += "... ";
		res += hdata->black->toStdString();
	}
	return res;
}

std::ostream& pgn::operator << ( std::ostream& os, const pgn::Move& src ) 
{
	if (src.hdata->white && src.hdata->black)
		os << src.hdata->number << ". " << *(src.hdata->white) << " " << *(src.hdata->black);
	else if (src.hdata->white)
		os << src.hdata->number << ". " << *(src.hdata->white);
	else if (src.hdata->black)
		os << src.hdata->number << "... " << *(src.hdata->black);
	return os;
}

bool pgn::Move::isCheckMate() const
{
	return (hdata->white && hdata->white->isCheckMate() || hdata->black && hdata->black->isCheckMate());
}

bool pgn::Move::operator != (const pgn::Move& src) const 
{ 
	return !(*this == src); 
}

pgn::Ply* pgn::Move::white() const 
{ 
	return hdata->white; 
} 

pgn::Ply* pgn::Move::black() const 
{ 
	return hdata->black; 
}


std::string pgn::Move::itoa(int n)
{
        char * s = new char[17];
        std::string u;
        if (n < 0)
	{ //turns n positive
                n = (-1 * n);
                u = "-"; //adds '-' on result string
        }

        int i=0; //s counter
        do
	{
                s[i++]= n%10 + '0'; //conversion of each digit of n to char
                n -= n%10; //update n value
        }

        while ((n /= 10) > 0);

        for (int j = i-1; j >= 0; j--)
	{
                u += s[j]; //building our string number
        }
        delete[] s; //free-up the memory!
        return u;
}

