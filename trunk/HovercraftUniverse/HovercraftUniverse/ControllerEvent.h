#ifndef CONTROLLEREVENT_H_
#define CONTROLLEREVENT_H_

#include "NetworkEvent.h"
#include "ControllerEventType.h"
#include <OgrePrerequisites.h>

namespace HovUni {

/**
 * This is an event created by the controller. It is serializable so that
 * it can be sent to the other clients (through the server).
 *
 * @author Olivier Berghmans
 */
class ControllerEvent: public NetworkEvent<ControllerEventType>
{
private:
	/** The time since last frame */
	Ogre::Real mTime;

public:
	/**
	 * Constructor
	 *
	 * @param type the type of the entity (used for serialization)
	 */
	ControllerEvent(ControllerEventType type);

	/**
	 * Destructor
	 */
	~ControllerEvent();

	/**
	 * Set the time that elapsed since the last frame
	 *
	 * @param time the time that elapsed since the last frame
	 */
	void setTimeSinceLastFrame(Ogre::Real time);

	/**
	 * Get the time that elapsed since the last frame
	 *
	 * @return the time since last frame
	 */
	Ogre::Real getTimeSinceLastFrame() const;

	/**
	 * Write the event
	 *
	 * @param stream the bitstream to append the event
	 */
	virtual void write(ZCom_BitStream* stream) const;

	/**
	 * Read the event
	 *
	 * @param stream the bitstream containing the event
	 */
	virtual void read(ZCom_BitStream* stream);

};

}

#endif
