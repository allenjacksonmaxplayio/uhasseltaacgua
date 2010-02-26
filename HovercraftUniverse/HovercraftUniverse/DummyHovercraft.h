#ifndef DUMMYHOVERCRAFT_H_
#define DUMMYHOVERCRAFT_H_

#include "Entity.h"

namespace HovUni {

/**
 * Dummy hovercraft for iterative development only.
 *
 * @author Kristof Overdulve
 */
class DummyHovercraft : public Entity
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
};

}

#endif