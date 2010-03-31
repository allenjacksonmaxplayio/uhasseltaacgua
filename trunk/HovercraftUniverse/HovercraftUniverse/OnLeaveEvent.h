#ifndef ONLEAVEEVENT_H
#define ONLEAVEEVENT_H

#include "GameEvent.h"

namespace HovUni {

class OnLeaveEvent : public GameEvent
{
private:
	
	ZCom_ConnID mConnectionId;

public:

	/**
	 * Constructor
	 * @param connection id, the id of the new player
	 */
	OnLeaveEvent( ZCom_ConnID connectionid );

	/**
	 * Default constructor for event construction
	 */
	OnLeaveEvent(void);

	virtual ~OnLeaveEvent(void);

	/**
	 * Get the connection id from the player that left
	 * @return the connection id from the player that left
	 */
	ZCom_ConnID getConnectionId() const {
		return mConnectionId;
	}


	void write(ZCom_BitStream* stream) const;

	void read(ZCom_BitStream* stream);

	static OnLeaveEvent * parse(ZCom_BitStream* stream);
};

}

#endif