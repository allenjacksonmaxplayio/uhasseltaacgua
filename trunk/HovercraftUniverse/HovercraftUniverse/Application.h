#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "ExampleApplication.h"
#include "EntityManager.h"
#include "InputManager.h"
#include "RepresentationManager.h"

namespace HovUni {

/**
 * Main application for the Hovercraft Universe game.
 *
 * @author Kristof Overdulve
 */
class Application : public ExampleApplication {
private:

	/** The entity manager */
	EntityManager * mEntityManager;

	/** The input manager */
	InputManager * mInputManager;

	/** The representation manager */
	RepresentationManager * mRepresentationManager;

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
	 * @see ExampleApplication::createCamera().
	 */
	void createCamera();

	/**
	 * @see ExampleApplication::createScene().
	 */
	void createScene();

	/**
	 * @see ExampleApplication::createFrameListener().
	 */
	void createFrameListener();
};

#endif

}