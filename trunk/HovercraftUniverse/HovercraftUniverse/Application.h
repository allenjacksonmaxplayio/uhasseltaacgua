#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <OgreRoot.h>
#include "ApplicationFrameListener.h"
#include "ClientCore.h"
#include "ClientPreparationLoader.h"
#include "EntityManager.h"
#include "InputManager.h"
#include "RepresentationManager.h"
#include <GUIManager.h>
#include <SoundManager.h>
#include <string>

#include "GameStateManager.h"

namespace HovUni {

/**
 * Main application for the Hovercraft Universe game.
 *
 * @author Kristof Overdulve, Dirk Delahaye
 */
class Application {
private:

	/** The root Ogre object */
	Ogre::Root * mOgreRoot;

	/** The application frame listener */
	ApplicationFrameListener * mFrameListener;
	GameStateManager* mGameStateMgr;

	/** The entity manager */
	EntityManager * mEntityManager;

	/** The input manager */
	InputManager * mInputManager;

	/** The representation manager */
	RepresentationManager * mRepresentationManager;

	/** The GUI Manager */
	GUIManager * mGUIManager;

	/** The sound manager */
	SoundManager * mSoundManager;

	/** The client */
	ClientCore* mClient;

	//INI file values
	std::string mDataPath;
	std::string mLogPath;
	std::string mOgreConfig;
	std::string mOgrePlugins;
	
public:

	/** The scene manager */
	static Ogre::SceneManager * msSceneMgr;

	/** The client preparation loader that can be used to read and reread scenes to render */
	static ClientPreparationLoader * msPreparationLoader;

	/**
	 * Constructor.
	 */
	Application();

	/**
	 * Destructor.
	 */
	virtual ~Application(void);

	/**
	 * The main method that triggers the application to run.
	 */
	void go(const Ogre::String& host, unsigned int port);

	void createClient(const Ogre::String& host, unsigned int port);

	void parseIni();
	void createRoot();
	void defineResources();
	void setupRenderSystem();
	void createRenderWindow();
	void initializeResourceGroups();
	void setupScene();
	void setupInputSystem();
	void createFrameListener();
	void startRenderLoop();

};

}

#endif
