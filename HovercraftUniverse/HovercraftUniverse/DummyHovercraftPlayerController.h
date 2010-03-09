#ifndef DUMMYHOVERCRAFTPLAYERCONTROLLER_H_
#define DUMMYHOVERCRAFTPLAYERCONTROLLER_H_

#include "DummyHovercraftController.h"
#include <OgreVector3.h>
#include "InputManager.h"

namespace HovUni {

/**
 * Dummy hovercraft player controller that listens to controls and feeds it to the dummy hovercraft.
 *
 * @author Kristof Overdulve, edited by Tobias Van Bladel
 */
class DummyHovercraftPlayerController : public DummyHovercraftController, public OIS::KeyListener {
protected:
	
	/** The input manager */
	InputManager * mInputManager;

	/** The different states the hovercraft can be in */
	bool mMovingLeft;
	bool mMovingForward;
	bool mMovingRight;
	bool mMovingBackward;


public:
	/**
	 * Constructr.
	 */
	DummyHovercraftPlayerController(void);

	/**
	 * Destructor.
	 */
	virtual ~DummyHovercraftPlayerController(void);

	/**
	 * @see DummyHovercraftController::moveForward()
	 */
	bool moveForward();

	/**
	 * @see DummyHovercraftController::moveBackward()
	 */
	bool moveBackward();

	/**
	 * @see DummyHovercraftController::turnLeft()
	 */
	bool turnLeft();

	/**
	 * @see DummyHovercraftController::turnRight()
	 */
	bool turnRight();

	/**
	 * @see KeyListener::keyPressed().
	 */
	bool keyPressed(const OIS::KeyEvent & e);

	/**
	 * @see KeyListener::keyReleased().
	 */
	bool keyReleased(const OIS::KeyEvent & e);
};

}

#endif

