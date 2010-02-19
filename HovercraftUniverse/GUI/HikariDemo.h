#ifndef HIKARIDEMO_H
#define HIKARIDEMO_H

#include "Ogre.h"
#include "Hikari.h"
#include "InputManager.h"
#include "BasicOverlay.h"

class HikariDemo : public Ogre::WindowEventListener
{
	Ogre::Root* root;
	Ogre::RenderWindow* renderWin;
	Ogre::SceneManager* sceneMgr;
	Ogre::Viewport* viewport;
	InputManager* inputMgr;

	unsigned long lastTime;
	Ogre::Timer timer;
	void parseResources();
	void loadInputSystem();
	void updateStats();

	HovUni::BasicOverlay* webcam;

public:
	bool shouldQuit;
	HikariDemo();
	~HikariDemo();

	void createScene();
	void setupHikari();

	void update();

	void windowMoved(Ogre::RenderWindow* rw);
	void windowResized(Ogre::RenderWindow* rw);
	void windowClosed(Ogre::RenderWindow* rw);
	void windowFocusChange(Ogre::RenderWindow* rw);
};

#endif //HIKARIDEMO_H