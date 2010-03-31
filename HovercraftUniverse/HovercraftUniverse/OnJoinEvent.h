#ifndef ONJOINEVENT_H
#define ONJOINEVENT_H

#include "GameEvent.h"

namespace HovUni {

class OnJoinEvent : public GameEvent
{
private:
	
	ZCom_ConnID mConnectionId;

public:

	/**
	 * Constructor
	 * @param connection id, the id of the new player
	 */
	OnJoinEvent( ZCom_ConnID connectionid );

	/**
	 * Default constructor for event construction
	 */
	OnJoinEvent(void);

	virtual ~OnJoinEvent(void);

	/**
	 * Get the connection id from the new player
	 * @return the connection id from the new player
	 */
	ZCom_ConnID getConnectionId() const {
		return mConnectionId;
	}

	//Network functionality

	void write(ZCom_BitStream* stream) const;

	void read(ZCom_BitStream* stream);

	static OnJoinEvent * parse(ZCom_BitStream* stream);
};

}

#endif