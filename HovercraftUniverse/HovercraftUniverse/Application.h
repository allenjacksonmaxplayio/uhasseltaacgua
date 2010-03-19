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
 * Main application for a game using the core engine.
 *
 * @author Kristof Overdulve, Dirk Delahaye
 */
class Application {
private:

	/** The name of the application */
	Ogre::String mAppName;

	/** The config INI file */
	Ogre::String mConfigINI;

	/** The root Ogre object */
	Ogre::Root * mOgreRoot;

	/** The application frame listener */
	ApplicationFrameListener * mFrameListener;

	/** The game state manager */
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

	/** INI file values */
	std::string mDataPath;
	std::string mLogPath;
	std::string mOgreConfig;
	std::string mOgrePlugins;
	std::string mSoundPath;
	std::string mSoundFile;
	
public:

	/** The scene manager */
	static Ogre::SceneManager * msSceneMgr;

	/** The client preparation loader that can be used to read and reread scenes to render */
	static ClientPreparationLoader * msPreparationLoader;

	/**
	 * Constructor.
	 *
	 * @param appName the name of the application/game
	 * @param configINI the INI file that contains all initialization and configuration properties in order to run the application properly
	 */
	Application(Ogre::String appName, Ogre::String configINI);

	/**
	 * Destructor.
	 */
	virtual ~Application();

	/**
	 * The main method that triggers the application to run.
	 *
	 * @param host the hostname to connect to
	 * @param port the port to connect on
	 */
	void go(const Ogre::String& host, unsigned int port);

	/**
	 * Creates the client.
	 * 
	 * @param host the hostname to connect to
	 * @param port the port to connect on
	 */
	void createClient(const Ogre::String& host, unsigned int port);

	/**
	 * Parse the INI file.
	 */
	void parseIni();

	/**
	 * Creates the root object.
	 */
	void createRoot();

	/**
	 * Defines the used resources.
	 */
	void defineResources();

	/**
	 * Sets up the render system.
	 */
	void setupRenderSystem();

	/**
	 * Creates the window that is rendered.
	 */
	void createRenderWindow();

	/**
	 * Initializes the resource groups.
	 */
	void initializeResourceGroups();

	/**
	 * Sets up the scene that should be displayed.
	 */
	void setupScene();

	/**
	 * Implement this method in order to play music. Leave empty if no music must be played.
	 *
	 * @param soundMgr the sound manager to use to play the music
	 */
	virtual void playMusic(SoundManager * soundMgr) = 0;

	/**
	 * Implement this method in order to perform custom scene operations.
	 */
	virtual void customSceneSetup() = 0;

	/**
	 * Creates input managers in order to be able to process input later.
	 */
	void setupInputSystem();

	/**
	 * Creates the frame listener.
	 */
	void createFrameListener();

	/**
	 * Starts rendering.
	 */
	void startRenderLoop();

};

}

#endif
