#include "Application.h"
#include "Server.h"
#include "Havok.h"
#include "EntityManager.h"
#include "Console.h"
#include <windows.h>
#include <OgreString.h>

void process_zoidcom_log(const char *_log) {
	Ogre::LogManager::getSingleton().getDefaultLog()->stream() << _log;
}

/**
 * Hovercraft Universe Application entry point.
 *
 * @author Kristof Overdulve & Olivier Berghmans & Pieter-Jan Pintens
 */
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT) {
	// Create ZoidCom
	ZoidCom *zcom = new ZoidCom(process_zoidcom_log);
	if (!zcom || !zcom->Init()) {
		return 1;
	}

	bool console = false;
	bool server = false;
	unsigned int port = 3040;
	Ogre::String host = "localhost";
	//parse all commandline parameters (seperated by spaces)
	Ogre::String commandline (strCmdLine);
	Ogre::vector<Ogre::String>::type result = Ogre::StringUtil::split(commandline, " ");
	for ( Ogre::vector<Ogre::String>::type::iterator i = result.begin(); i != result.end(); i++ ){
		if ( (*i) == "--server" ){
			server = true;
		}
		else if ( Ogre::StringUtil::startsWith(*i,"--host=") ) {
			//string of the form host:port
			Ogre::String connectionstring = (*i).substr(7);
			size_t pos = connectionstring.find(":");
			if ( pos == Ogre::String::npos ){
				host = connectionstring;
			} else {
				host = connectionstring.substr(0,pos);
				port = Ogre::StringConverter::parseInt(connectionstring.substr(pos+1));
			}
		}
		else if ( (*i) == "--console") {
			console = true;
		}
	}

	if ( server ) {

		HovUni::Console::createConsole("SERVER");

		new Ogre::Root();
		Ogre::LogManager::getSingleton().createLog("Server.log", true);

		HovUni::Server* server = new HovUni::Server();
		server->start();
		server->join();
		delete server;

		server = 0;
		HovUni::Console::destroyConsole();

	} else {
		if ( console )
			HovUni::Console::createConsole("CLIENT");

		HovUni::Application app;
		
		try {
			app.go(host,port);
		} catch (Ogre::Exception & e) {
			MessageBox(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
		}

		if ( console )
			HovUni::Console::destroyConsole();
	}

	delete zcom;
	return 0;
}