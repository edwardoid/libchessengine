//
// Copyright (C) 2002 Andrea Vinzoni <vinzo@planet.it>
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

#ifndef PGNException_h
#define PGNException_h

#include <exception>
#include <string>

/**
 * @brief global namespace for libpgnm
 * @namespace pgn
 */
namespace pgn
{
	/**
	 * @brief Represents exceptions which must be throwed on parsing
	 */
	class parse_exception : public std::exception 
	{
		public:
   			
   			/**
   			 * @brief Represents parse exception with given message.
   			 * @param message Text message, description of error.
   			 */
			parse_exception(const std::string &message) throw():message_(message) {}
			~parse_exception() throw() {}

			/**
			 * @brief Sets text which is wrong.
			 * @param parsingtext Wrong text from PGN file.
			 */
			void bindParsingText(const std::string &parsingtext) throw() { parsing_text_ = parsingtext; }

			/**
			 * @brief Gets text which is wrong.
			 * @return Wrong text fomr PGN file.
			 */
			const char *parsing_text() const throw() { return parsing_text_.c_str(); }

			/**
			 * @brief Gets additional information about exception.
			 * @return Additional information.
			 */
    		virtual const char *what() const throw() { return message_.c_str(); }

		private:

			std::string message_;
			std::string parsing_text_;
	};

	/**
	 * @brief Throws when castle in pgnfile is incorrect format.
	 */
	class invalid_castle_string : public parse_exception
	{
		public:
    
			invalid_castle_string() throw();
			~invalid_castle_string() throw() {};
	};

	/**
	 * @brief Throws when ply is in incorrect format.
	 */
	class invalid_ply_text : public parse_exception
	{
		public:
    
			~invalid_ply_text() throw() {};
			invalid_ply_text(const std::string &ply) throw();
	};

	/**
	 * @brief Throws when file contains tag with wrong format.
	 */
	class invalid_tag : public parse_exception
	{
		public:
    
			~invalid_tag() throw() {};
			invalid_tag() throw();
	};

	/**
	 * @brief Throws when file contains result string in incorrect format.
	 */
	class invalid_result : public parse_exception
	{
		public:
    
			~invalid_result() throw() {};
			invalid_result() throw();
	};

	/**
	 * @brief Throws when game/file does not contain information about game
	 * result
	 */
	class missing_result : public parse_exception
	{
		public:
    
			~missing_result() throw() {};
			missing_result() throw();
	};

	// TODO: da eliminare quando il parsing delle varianti sara` sviluppato
	class unsupported_variations : public parse_exception
	{
		public:
    
			~unsupported_variations() throw() {};
			unsupported_variations() throw();
	};

	// TODO: da eliminare quando il supporto ai glyphs sara` sviluppato
	class unsupported_glyphs : public parse_exception
	{
		public:
    
			~unsupported_glyphs() throw() {};
			unsupported_glyphs() throw();
	};
	
	/**
	 * @brief Throws when file in incorrect/invalid
	 */
	class bad_pgn_file: public std::exception
	{
		public:
			~bad_pgn_file() throw(){};
			bad_pgn_file( const std::string message ) throw():message_( message ) {}
   		 	virtual const char *what() const throw() { return message_.c_str(); }
   		private:
   			std::string message_;
	};
}


#endif 
