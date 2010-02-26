#ifndef BASICENTITYEVENT_H_
#define BASICENTITYEVENT_H_

#include "ControllerEvent.h"
#include <OgreVector3.h>

namespace HovUni {

/**
 * This is a basic entity event which involves changing position
 * and orientation.
 *
 * @author Olivier Berghmans
 */
class BasicEntityEvent: public ControllerEvent
{
private:
	/** The direction */
	Ogre::Vector3 mDirection;

	/** The orientation change */
	Ogre::Vector3 mOrientation;

	/** The time since last frame */
	Ogre::Real mTime;

public:
	/**
	 * Constructor
	 *
	 * @param direction the direction in which the entity is to move
	 * @param orientationchange the orientation change of the entity
	 */
	BasicEntityEvent(Ogre::Vector3 direction, Ogre::Vector3 orientationchange);

	/**
	 * Destructor
	 */
	~BasicEntityEvent();

	/**
	 * Get the direction in which the entity is to move
	 *
	 * @return the direction
	 */
	Ogre::Vector3 getDirection() const;

	/**
	 * Get the orientation change of the entity
	 *
	 * @return the orientation change
	 */
	Ogre::Vector3 getOrientationChange() const;

	/**
	 * @see ControllerEvent::write(ZCom_BitStream* stream)
	 */
	virtual void write(ZCom_BitStream* stream) const;

	/**
	 * @see ControllerEvent::read(ZCom_BitStream* stream)
	 */
	virtual void read(ZCom_BitStream* stream);

	/**
	 * Parse the stream to create this event
	 *
	 * @param stream the bitstream containing the event
	 * @return the event
	 */
	static BasicEntityEvent* parse(ZCom_BitStream* stream);

};

}

#endif
