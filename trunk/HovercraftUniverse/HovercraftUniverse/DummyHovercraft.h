#ifndef DUMMYHOVERCRAFT_H_
#define DUMMYHOVERCRAFT_H_

#include "Entity.h"
#include <Moveable3DEmitter.h>

namespace HovUni {

/**
 * Dummy hovercraft for iterative development only.
 *
 * @author Kristof Overdulve
 */
class DummyHovercraft : public Entity, public Moveable3DEmitter
{
public:

	/**
	 * Constructor.
	 */
	DummyHovercraft(void);

	/**
	 * Destructor.
	 */
	virtual ~DummyHovercraft(void);

	/**
	 * @see Entity::processControllerEventsInServer(ControllerEvent* event).
	 */
	virtual void processControllerEventsInServer(ControllerEvent* event);

	/**
	 * @see Entity::processControllerEventsInOwner(ControllerEvent* event).
	 */
	virtual void processControllerEventsInOwner(ControllerEvent* event);

	/**
	 * @see Entity::processControllerEventsInOther(ControllerEvent* event).
	 */
	virtual void processControllerEventsInOther(ControllerEvent* event);

	/**
	 * Task for processing at owner and other
	 *
	 * @param event the event
	 */
	void processEventsOwnerAndOther(ControllerEvent* event);

	/**
	 * See Moveable3DEmitter for details
	 */
	void getUpdates(Ogre::Vector3 ** position, Ogre::Vector3 ** velocity, Ogre::Vector3 ** orientation);
};

}

#endif