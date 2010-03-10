#include "Application.h"
#include "ServerCore.h"
#include "Havok.h"
#include "EntityManager.h"
#include "Console.h"
#include <windows.h>


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

	if (!strcmp(strCmdLine, "--server")) {

		HovUni::Console::createConsole("SERVER");

		new Ogre::Root();
		Ogre::LogManager::getSingleton().createLog("Server.log", true);
		HovUni::ServerCore* server = new HovUni::ServerCore();

		while (true) {
			// let the server do processing
			//Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "Server start input output process\n";
			server->process();
			HovUni::EntityManager::getServerSingletonPtr()->updateEntities(0.05f);
			//Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "Server ends input output process\n";
			// let the program sleep for 0 msecs
			zcom->Sleep(1);
		}

		delete server;

		HovUni::Console::destroyConsole();

	} else {
		HovUni::Application app;
	
		try {
			app.go();
		} catch (Ogre::Exception & e) {
			MessageBox(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
		}
	}

	delete zcom;
	return 0;
}