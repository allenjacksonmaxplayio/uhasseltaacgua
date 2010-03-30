#include "Config.h"

#include "Exception.h"
#include <boost/algorithm/string/trim.hpp>

namespace HovUni {

	Config::Config() {

	}

	Config::~Config() {
		//...
	}

	void Config::loadFile(std::string filename) {
		bool success = mReader.Load(filename, true);
		if (!success) {
			throw new ConfigException("Could not read file " + filename + ": INI library returned false.");
		}
		mFilename = filename;
	}

	void Config::saveFile(std::string filename) {
		bool success = mReader.Save(filename);
		if (!success) {
			throw new ConfigException("Could not save to config file " + filename + ".");
		}
	}

	void Config::saveFile() {
		bool success = mReader.Save(mFilename);
		if (!success) {
			throw new ConfigException("Could not save to default config file " + mFilename + ".");
		}
	}

	std::string Config::getValue(std::string section, std::string field) {
		std::string value = mReader.GetKeyValue(section, field);
		boost::algorithm::trim(value);
		return value;
	}

	void Config::putValue(std::string section, std::string field, std::string value) {
		mReader.SetKeyValue(section,field,value);
	}

}