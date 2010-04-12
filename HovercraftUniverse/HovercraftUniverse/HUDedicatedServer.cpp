#include "HUServer.h"
#include "HUDedicatedServer.h"
#include <OgreRoot.h>
#include <OgreConfigFile.h>
#include <OgreMaterialManager.h>
#include <windows.h>
#include <math.h>


namespace HovUni {
	HUDedicatedServer::HUDedicatedServer(const std::string& configINI) : 
		DedicatedServer(configINI) {
	}

	void HUDedicatedServer::run() {
		//TODO Dirk retrieve these values from server ini
		Ogre::Root ogreRoot(getConfig()->getValue("Ogre", "Plugins", "plugins.cfg"), getConfig()->getValue("Ogre", "ConfigFile", "ogre.cfg"), getConfig()->getValue("Ogre", "LogFile", "Server.log"));
		//Ogre::LogManager::getSingleton().createLog(getConfig()->getValue("Server", "LogFile", "Server.log"), true);

// HACK IN OGRE FILE THINGY

		Ogre::ConfigFile cf;
		cf.load(mConfig->getValue("Ogre", "Resources", "resources.cfg").c_str());
		// Iterate over config
		Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
		while (seci.hasMoreElements()) {
			// Read property
			Ogre::String secName = seci.peekNextKey();
			Ogre::ConfigFile::SettingsMultiMap * settings = seci.getNext();
			
			// For all settings of that property, add them
			for (Ogre::ConfigFile::SettingsMultiMap::iterator it = settings->begin(); it != settings->end(); it++) {
				Ogre::String typeName = it->first;
				Ogre::String archName = it->second;
				Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
			}
		}

		//make sure it doesn't parse materials
		Ogre::ResourceGroupManager::getSingleton()._unregisterScriptLoader(Ogre::MaterialManager::getSingletonPtr());

// HACK IN OGRE FILE THINGY

		HovUni::HUServer server;
		server.start();
		server.join();
//		delete server;
//		server = 0;
//		delete ogreRoot;
//		ogreRoot = 0;
	}

	void HUDedicatedServer::init() {
		DedicatedServer::init();
	}
}