#include "Application.h"
#include <windows.h>

/**
 * Hovercraft Universe Application entry point.
 *
 * @author Kristof Overdulve
 */
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT) {
	HovUni::Application app;

	try {
		app.go();
	} catch (Ogre::Exception & e) {
		MessageBox(NULL, e.getFullDescription().c_str(), "An exception has occurred!", 
			MB_OK | MB_ICONERROR | MB_TASKMODAL);
	}

	return 0;
}