#ifndef CHESS_ENGINE_TABLE
#define CHESS_ENGINE_TABLE
#include "CEPiece.h"
#include <iostream>

/**
 * @namespace ChEngn
 */
namespace ChEngn
{

	/**
	 * @struct table_size
	 * Provides information about table size
	 */
	struct table_size
	{
		unsigned int height;
		unsigned int width;
	};


	/// Standart table height
	const unsigned int default_table_height = 8;

	/// Standart table width
	const unsigned int default_table_width = 8;

	/**
	 * @class ChEngn::Table
	 *
	 * Provides basic manipulations whis chess table (no matter "virtual" ot
	 * "real". Find ChEngn::Piece, move them.
	 */
	class Table
	{
		public:
		
			/**
			 * @brief Default constructor.
			 */
			Table();

			/**
			 * @brief Copy constructor.
			 * @param other - Source.
			 */
			Table(const Table& other);

			/**
			 * @brief Destructor.
			 */
			virtual ~Table();

			/**
			 * @brief Get table's size
			 */
			const table_size size() const;

			/**
			 * @brief Get table's height
			 * @return height
			 */
			const unsigned int height() const;

			/**
			 * @brief Get table's width
			 * @return width
			 */
			const unsigned int width() const;
			
			/**
			 * @brief Get current table state
			 * @return Current table state
			 * @warning If you don't gonna change the table use const-version
			 */
			Piece** table();

			
			/**
			 * 	Get piece from table.
			 * 	@brief Return piece at given position.
			 * 	@param row - Piece's position row.
			 * 	@param column  - Piece's position column.
			 * 	@return - Referentce to piece, if row and/or column are invalid
			 * 	Piece() will be returned.
			 */
			Piece pieceAt(unsigned int row, unsigned int column) const;
			/**
			 * @brief Set table for beginig gaming
			 * @warning Function will do changes if table size is 8x8. In
			 * another case nothing will be done
			 */
			void resetComplect();

			/**
			 * "Prints" table into std::ostream
			 * @brief Overloaded operator << ()
			 * @param out - Stream for printing
			 * @param tbl - table to print
			 */
			friend std::ostream& operator << (std::ostream &out, const Table& tbl);
		private: //methods

			void setComplectNull();
			void setDefaultComplect();
		private: // variables

			table_size m_size;
			Piece **m_table;
	};
};

#endif
