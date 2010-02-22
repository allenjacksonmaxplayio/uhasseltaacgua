#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <OgreRoot.h>
#include "ApplicationFrameListener.h"
#include "EntityManager.h"
#include "InputManager.h"
#include "RepresentationManager.h"
#include <GUIManager.h>

namespace HovUni {

/**
 * Main application for the Hovercraft Universe game.
 *
 * @author Kristof Overdulve
 */
class Application {
private:

	/** The root Ogre object */
	Ogre::Root * mOgreRoot;

	/** The application frame listener */
	ApplicationFrameListener * mFrameListener;

	/** The entity manager */
	EntityManager * mEntityManager;

	/** The input manager */
	InputManager * mInputManager;

	/** The representation manager */
	RepresentationManager * mRepresentationManager;

	/** The GUI Manager */
	GUIManager * mGUIManager;

public:

	/**
	 * Constructor.
	 *
	 */
	Application(void);

	/**
	 * Destructor.
	 */
	virtual ~Application(void);

	/**
	 * The main method that triggers the application to run.
	 */
	void go();

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

#endif

}