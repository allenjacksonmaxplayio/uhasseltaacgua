#ifndef DUMMYHOVERCRAFT_H_
#define DUMMYHOVERCRAFT_H_

#include "Entity.h"
#include "BasicEntityEvent.h"

namespace HovUni {

/**
 * Dummy hovercraft for iterative development only.
 *
 * @author Kristof Overdulve & Olivier Berghmans
 */
class DummyHovercraft : public Entity {
private:
	/** The moving status */
	BasicEntityEvent* mMovingStatus;

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
	 * @see Entity::process(float timeSince).
	 */
	virtual void process(float timeSince);

	/**
	 * @see Entity::processEventsServer(ControllerEvent* event).
	 */
	virtual void processEventsServer(ControllerEvent* event);

	/**
	 * @see Entity::processEventsOwner(ControllerEvent* event).
	 */
	virtual void processEventsOwner(ControllerEvent* event);

	/**
	 * @see Entity::processEventsOther(ControllerEvent* event).
	 */
	virtual void processEventsOther(ControllerEvent* event);

};

}

#endif