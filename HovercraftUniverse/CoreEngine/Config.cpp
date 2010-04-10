#include "Config.h"

#include "Exception.h"
#include <boost/algorithm/string/trim.hpp>
#include <sstream>

#include <OgreLogManager.h>

namespace HovUni {

	Config::Config() {

	}

	Config::~Config() {
		//...
	}

	void Config::loadFile(std::string filename) {
		bool success = mReader.Load(filename, true);
		std::cout << "Config Loading file " << filename <<"."<< std::endl;
		if (!success) {
			throw new ConfigException("Could not read file " + filename + ": INI library returned false.");
		}
		mFilename = filename;
		std::cout << "Config new Filename " << mFilename << std::endl;
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

	int Config::getIntValue(std::string section, std::string field) {
		std::string stringValue = getValue(section, field);
		std::istringstream buffer(stringValue);
		int result;
		buffer >> result;
		return result;
	}

	float Config::getFloatValue(std::string section, std::string field) {
		std::string stringValue = getValue(section, field);
		std::istringstream buffer(stringValue);
		float result;
		buffer >> result;
		return result;
	}

	double Config::getDoubleValue(std::string section, std::string field) {
		std::string stringValue = getValue(section, field);
		std::istringstream buffer(stringValue);
		double result;
		buffer >> result;
		return result;
	}

	void Config::putValue(std::string section, std::string field, std::string value) {
		mReader.SetKeyValue(section,field,value);
	}

}