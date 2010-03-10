#include "Application.h"
#include "Server.h"
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
		HovUni::Console::createConsole("Hovercraft Universe Server");
		new Ogre::Root();
		Ogre::LogManager::getSingleton().createLog("Server.log", true);
		HovUni::Server* server = new HovUni::Server();
		server->start();
		server->join();
		delete server;
		server = 0;
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