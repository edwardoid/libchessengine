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

#ifndef PGNGameCollection_h
#define PGNGameCollection_h

#include <fstream>
#include <vector>
#include "PGNGame.h"
#include "PGNMGlobals.h"

/**
 * @brief global namespace for libpgnm
 * @namespace pgn
 */
namespace pgn
{
	/**
	 * @class PGNM_EXPORT GameCollection
	 * @brief Stores a collection of pgn::Game.
	 */
	class PGNM_EXPORT GameCollection 
	{
		public:
	
			/**
			 * @brief Simple iterator.
			 * See more pgn::GameCollection::iterator.
			 */
			class PGNM_EXPORT iterator;

			/**
			 * @brief Simple iterator.
			 * See more pgn::GameCollection::iterator.
			 */

			friend class PGNM_EXPORT iterator;

			/**
			 * @brief Costructs empty collection.
			 */
			GameCollection();


			/**
			 * @brief Constructs copy of given collection.
			 * @param src Source collection
			 */
			GameCollection(const GameCollection& src);

			/**
			 * @brief Clears collection
			 */
			virtual ~GameCollection();

			/**
			 * @brief Copies to given collection to current collection. Works
			 * like copy constructor.
			 */
			GameCollection& operator = (const GameCollection& src);

			/**
			 * @brief Compares 2 collections.
			 * Collections are equal if each game from source at position
			 * <i>i</i> is equal to currect golelctions game at same position.
			 * @param src Collection with which must be compaired current
			 * collection.
			 * @see pgn::Game::operator==( const Game& ).
			 * @return true if collections are equal, false — otherway.
			 */
			bool operator == (const GameCollection& src) const;

			/**
			 * @brief Negative variant of pgn::GameCollection::operator==
			 * @param src Collection with which must be compaired current
			 * collection.
			 * @return (! operator==( const GameCollection &src ) );
			 */
			bool operator != (const GameCollection& src) const;

			/**
			 * @brief Returns game at given position.
			 * @param inx Position of game.
			 * @return Game at potion <i>inx</i>.
			 */
			virtual Game operator [] (const int idx) const;

			void insert(const Tag& src); // deprecated
			void erase(const Tag& src); // deprecated
			void sort(const Tag &key); // deprecated
			
			/**
			 * @brief Inserts game to collection.
			 * @param src Game for insertion.
			 */
			void insert(const Game& src);

			/**
			 * @brief Removes all games from list which are equal with given
			 * @param src Remove game.
			 */
			void erase(const Game& src);

			/**
			 * @brief Get list's size.
			 */
			int size() const;

			/**
			 * @brief removes all games from list.
			 */
			void clear();

			/**
			 * @brief Get iterator to first game in list.
			 */
			iterator begin();

			/**
			 * @brief Get iterator positioned <b>after<b> last game in list.
			 */
			iterator end();
				
			/**
			 * @brief Prints all games from list to given stream. @see
			 * pgn::Game::operator<<( std::ostream, const Game ).
			 * @param os Stream-printer.
			 * @param src Games list to print.
			 */
			friend std::ostream& operator << ( std::ostream& os, const GameCollection& src);

			/**
			 * @brief Read text from given stream and tryes to parse and extract
			 * game from it.
			 * @param is Input stream.
			 * @param src Games Container.
			 */
			friend std::istream& operator >> ( std::istream& is, GameCollection& src);

		private:
	
			struct GameCollectionData *hdata;
	};

	/**
	 * @class PGNM_EXPORT GameCollection::iterator
	 * @brief Instrument for safe iteration in pgn::GameCollection
	 */
	class PGNM_EXPORT GameCollection::iterator
	{
		public:
			/**
			 * @brief Default constructor.
			 */
			iterator();

			/**
			 * @brief Constructs iterator pointing to first game in given list.
			 * @param ml Collection to iteration.
			 */
			iterator(const GameCollection &ml);

			/**
			 * @brief Costructs iterator poinitng to game at idx. If at index
			 * idx is no game ml::end() will be returned.
			 * @param ml Collection to iteration.
			 * @param idx Iterator position.
			 */
			iterator(const GameCollection &ml, int idx);

			/**
			 * @brief Copy constructor.
			 */
			iterator(const iterator&);

			/**
			 * @brief Destructor
			 */
			~iterator();

			/**
			 * @brief Sets current iterator pointing as given.
			 * @param src Source iterator.
			 */
			iterator& operator = (const iterator& src);

			/**
			 * @brief Sets iterator point to next game.
			 */
			iterator& operator ++ ();

			/**
			 * @brief Moves iterator to <i> positions forward.
			 * @param i Positions count to be forwarded.
			 */
			iterator& operator ++ (int i);

			/**
			 * @brief Get game iterator is pointing to.
			 * @return Game iterator is pointing to.
			 */
			Game* operator -> () const;

			/**
			 * @brief Get game iterator is pointing to.
			 * @return Game iterator is pointing to.
			 */
			const Game& operator * () const;

			/**
			 * @brief Checks are two iterator pointing to same game.
			 * @return true if iterators are equal.
			 */
			bool operator == (const iterator&) const;

			/**
			 * @brief Negative variant of operator==
			 */
			bool operator != (const iterator&) const;

		private:
		
			struct iteratorData *hdata;
	};
};

#endif 

