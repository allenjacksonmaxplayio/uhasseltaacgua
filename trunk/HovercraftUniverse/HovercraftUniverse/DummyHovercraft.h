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
	 * @see Entity::processController().
	 */
	void processController(Ogre::Real timeSinceLastFrame);
};

}

#endif