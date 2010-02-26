#ifndef DUMMYHOVERCRAFTCONTROLLER_H_
#define DUMMYHOVERCRAFTCONTROLLER_H_

#include "Controller.h"
#include <OgreVector3.h>

namespace HovUni {

/**
 * Dummy hovercraft controller interface that specifies which actions must be under control.
 *
 * @author Kristof Overdulve
 */
class DummyHovercraftController : public Controller {
public:

	/**
	 * Destructor
	 */
	virtual ~DummyHovercraftController();

	/**
	 * @see Controller::getEvents()
	 */
	virtual std::vector<ControllerEvent*> getEvents();

	/**
	 * Tells in which direction the hovercraft is to move.
	 *
	 * @return the direction
	 */
	virtual Ogre::Vector3 getDirection() = 0;

	/**
	 * Tells the orientation change of the hovercraft.
	 *
	 * @return the orientation change
	 */
	virtual Ogre::Vector3 getOrientationChange() = 0;
};

}

#endif
