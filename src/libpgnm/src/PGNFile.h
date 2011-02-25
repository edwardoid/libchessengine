#ifndef PGNFile_h
#define PGNFile_h

#include <string>
#include <PGNGameCollection.h>

namespace pgn
{
	class File
	{
		public:
			File();
			File(const File& other);
			File(const std::string fileName);
			File(const char* fileName);
			File(const pgn::GameCollection& otherGameCollection);
			virtual ~File();
			void loadFile(std::string fileName);
			void loadFile(const char* fileName);
			GameCollection* games();
			GameCollection games() const;
		private:
			GameCollection hdata;
	};
};

#endif
