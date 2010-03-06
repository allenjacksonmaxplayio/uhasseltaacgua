#ifndef DUMMYHOVERCRAFTCONTROLLER_H_
#define DUMMYHOVERCRAFTCONTROLLER_H_

#include "Controller.h"
#include <OgreVector3.h>
#include "BasicEntityEvent.h"

namespace HovUni {

/**
 * Dummy hovercraft controller interface that specifies which actions must be under control.
 *
 * @author Kristof Overdulve
 */
class DummyHovercraftController : public Controller {
private:
	/** The last sent moving state */
	BasicEntityEvent mLast;

public:
	/**
	 * Default constructor
	 */
	DummyHovercraftController();

	/**
	 * Destructor
	 */
	virtual ~DummyHovercraftController();

	/**
	 * @see Controller::getEvents()
	 */
	virtual std::vector<ControllerEvent*> getEvents();

	/**
	 * Check whether the entity should move forward
	 *
	 * @return true if the entity should move forward
	 */
	virtual bool moveForward() const = 0;

	/**
	 * Check whether the entity should move backward
	 *
	 * @return true if the entity should move backward
	 */
	virtual bool moveBackward() const = 0;

	/**
	 * Check whether the entity should move left
	 *
	 * @return true if the entity should move left
	 */
	virtual bool moveLeft() const = 0;

	/**
	 * Check whether the entity should move right
	 *
	 * @return true if the entity should move right
	 */
	virtual bool moveRight() const = 0;

};

}

#endif
