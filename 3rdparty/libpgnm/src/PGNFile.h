#ifndef PGNFile_h
#define PGNFile_h

#include <string>
#include "PGNGameCollection.h"
#include "PGNM.h"

/**
 * @brief global namespace for libpgnm
 * @namespace pgn
 */
namespace pgn
{
	/**
	 * @class PGNM_EXPORT File
	 * @brief Opens and extract games from PGN file and/or compile
	 * pgn::GameCollection fo file.
	 */
	class PGNM_EXPORT File
	{
		public:
			/**
			 * @brief Default constructor.
			 */
			File();

			/**
			 * @brief Copy constructor.
			 */
			File(const File& other);

			/**
			 * @brief tryes to open given file and extract games from it.
			 * @param fileName Path to opening file.
			 */
			File(const std::string fileName);

			/**
			 * @brief tryes to open given file and extract games from it.
			 * @param fileName Path to opening file.
			 */	
			File(const char* fileName);

			/**
			 * @brief Constructs object to compile givens games to file.
			 */
			File(const pgn::GameCollection& otherGameCollection);
			virtual ~File();

			/**
			 * @brief Tryes to load given file, and extract games from it.
			 * @param fileName Path to opening file.
			 */
			void loadFile(std::string fileName);
			
			/**
			 * @brief Tryes to load given file, and extract games from it.
			 * @param fileName Path to opening file.
			 */
			void loadFile(const char* fileName);

			/**
			 * @brief Get extracted games.
			 * @return Extracted games.
			 */
			GameCollection& games();

			/**
			 * Same as pgn::File::games()
			 * @brief Get extracted games.
			 * @return Extracted games.
			 */

			GameCollection gamesC() const;
		private:
			GameCollection hdata;
	};
};

#endif
