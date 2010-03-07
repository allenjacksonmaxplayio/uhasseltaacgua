#ifndef DUMMYHOVERCRAFTCONTROLLER_H_
#define DUMMYHOVERCRAFTCONTROLLER_H_

#include "Controller.h"
#include <OgreVector3.h>
#include "BasicEntityEvent.h"

namespace HovUni {

/**
 * Dummy hovercraft controller interface that specifies which actions must be under control.
 *
 * @author Kristof Overdulve, Olivier Berghmans, Dirk Delahaye
 */
class DummyHovercraftController : public Controller {
protected:
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
	virtual bool moveForward() = 0;

	/**
	 * Check whether the entity should move backward
	 *
	 * @return true if the entity should move backward
	 */
	virtual bool moveBackward() = 0;

	/**
	 * Check whether the entity should turn left
	 *
	 * @return true if the entity should turn left
	 */
	virtual bool turnLeft() = 0;

	/**
	 * Check whether the entity should turn right
	 *
	 * @return true if the entity should turn right
	 */
	virtual bool turnRight() = 0;

};

}

#endif
