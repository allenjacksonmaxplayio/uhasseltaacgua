#include "HavocWorldUpdater.h"

#include <OgreRoot.h>
#include "../HovercraftUniverse/InputManager.h"
using HovUni::InputManager;

int main( int argc, char * argv [] )
{
		//we need ogre for IO
		Ogre::Root * mOgreRoot = new Ogre::Root();
		mOgreRoot->restoreConfig();
		Ogre::RenderWindow * window = mOgreRoot->initialise(true, "Hovercraft Universe");
		InputManager::getSingletonPtr()->initialise(window);

		//do havoc sim in background
		HavocWorldUpdater mHavoc (".\\..\\..\\..\\art\\models\\planetgravity_L4101.hkx");

		// A stopwatch for waiting until the real time has passed
		hkStopwatch stopWatch;
		stopWatch.start();
		hkReal lastTime = stopWatch.getElapsedSeconds();

		//run physics at 60FPS
		hkReal timestep = 1.f / 60.f;

		while ( true )
		{
			mHavoc.update(timestep);

			// Pause until the actual time has passed
			while (stopWatch.getElapsedSeconds() < lastTime + timestep);
			lastTime += timestep;
		}

    return 0;
}