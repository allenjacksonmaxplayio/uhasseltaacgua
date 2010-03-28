#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>
#include "inifile.h"

namespace HovUni {

	/**
	*	This class wraps the INI functionality to read/write key-value pairs to file.
	*	@author Dirk Delahaye, 26/03/2010
	*/
	class Config {
	private:
		/**
		*	The singleton Config object.
		*/
		static Config* mConfig;

		/**
		*	The INI File object.
		*/
		CIniFile mReader;

		/**
		*	The default filename to save to
		*/
		std::string mFilename;

		
	public:

		/**
		*	Constructor. Use Config::getSingletonPtr().
		*/
		Config();

		/**
		*	Destructor.
		*/
		~Config();

		/**
		*	Returns a pointer to the singleton Config object.
		*	@return	The Config object (singleton).
		*/
		static Config* getSingletonPtr();

		/**
		*	Loads an INI File. 
		*	NOTE: The contents will be merged into this object.
		*			If you do not wish to do this, create a new Config object instead.
		*	@param	filename
		*	@throws ConfigException
		*/
		void loadFile(std::string filename);

		/**
		*	Saves the internal representation to a file.
		*	@param	filename	The config filename.
		*	@throws ConfigException
		*/
		void saveFile(std::string filename);

		/**
		*	Saves the internal representation to the same file it's been loaded from.
		*	@throws ConfigException
		*/
		void saveFile();

		/**
		*	Returns the value for the given (section, field, value) tuple.
		*	@param	section	The section name
		*	@param	field	The key, or field name.
		*	@return	The value, as a string. NOTE! This string is whitespace-trimmed.
		*/
		std::string getValue(std::string section, std::string field);

		/**
		*	Put the value in the config as a (section, field, value) tuple.
		*	@param	section	The section name
		*	@param	field	The key, or field name.
		*	@param	value	The value, as a string. NOTE! This string will bewhitespace-trimmed.
		*/
		void putValue(std::string section, std::string field, std::string value);
	};

}

#endif //CONFIG_H_