#include "DedicatedServer.h"
#include "Exception.h"
#include <windows.h>
#include "Config.h"

namespace HovUni {
	DedicatedServer::DedicatedServer() {

	}

	DedicatedServer::~DedicatedServer() {
		delete mConfig;
		mConfig = 0;
	}

	Config* DedicatedServer::mEngineSettings = 0;

	Config* DedicatedServer::getEngineSettings() {
		if (!mEngineSettings) {
			mEngineSettings = new Config();
		}
		return mEngineSettings;
	}

	void DedicatedServer::init() {
		parseIni();
	}

	void DedicatedServer::parseIni() {
		mConfig = new Config();
		mConfig->loadFile("HovercraftUniverse.ini");
		//Get(section, name, defaultValue)
		std::string mDataPath = mConfig->getValue("Paths", "DataPath", "data");
		DWORD  retval=0;
		TCHAR  buffer[MAX_PATH]=TEXT(""); 
		TCHAR** lppPart={NULL};
		GetFullPathName(mDataPath.c_str(),MAX_PATH,buffer,lppPart);
		std::cout << "Changing Working Dir to " << buffer << std::endl;
		BOOL success = SetCurrentDirectory(buffer);
		if (!success) {
			std::string error = "Could not set working dir (check config file DataPath var)!";
			std::cerr << error << std::endl;
			//TODO Throw Exception
		}
		//Parse Engine settings
		mEngineSettings = getEngineSettings();
		mEngineSettings->loadFile("engine_settings.cfg");
	}
}