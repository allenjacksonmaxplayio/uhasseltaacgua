#ifndef NETWORKENTITY_H_
#define NETWORKENTITY_H_

#define ZCOM_REPFLAG_SETUPAUTODELETE   (1L << 6)

#include "NetworkEvent.h"
#include <zoidcom/zoidcom_node.h>

namespace HovUni {

/**
 * This class represents an entity.
 *
 * @author Olivier Berghmans
 */
class NetworkEntity
{
protected:
	/** The network node */
	ZCom_Node* mNode;

	/** Whether the entity is registered to the network */
	bool mRegistered;

public:
	/**
	 * Constructor
	 */
	NetworkEntity();

	/**
	 * Destructor
	 */
	virtual ~NetworkEntity();

	/**
	 * Register the node for the network
	 *
	 * @param id the zoidcom class ID
	 * @param control the zoidcom control
	 */
	void networkRegister(ZCom_ClassID id, ZCom_Control* control);

	/**
	 * Check whether the entity is registered for the network
	 *
	 * @return true if the entity is registered
	 */
	bool isRegistered() const;

	/**
	 * Process the events waiting for this entity. This method
	 * should be called regularly because otherwise events for
	 * this entity will stay in the queue.
	 *
	 * @param timeSince the time since the last process of the events
	 */
	void processEvents(float timeSince);

	/**
	 * A callback that should be implemented so that events for
	 * this entity are handled in a good way. Normally this method
	 * would first parse the stream to an event and then process
	 * the event.
	 *
	 * @param stream the bitstream containing the event
	 * @param timeSince the time since the last processing of the events
	 */
	virtual void parseEvents(ZCom_BitStream* stream, float timeSince) = 0;

	/**
	 * Send an event for this entity
	 *
	 * @param event the network event
	 * @param secret false if the data may be send to all proxies
	 * @return result of the send operation
	 */
	template <typename EventType>
	bool sendEvent(const NetworkEvent<EventType>& event, bool secret = false) const;

	/**
	 * Get the network node. You should probably not be calling this.
	 *
	 * @return the network node
	 */
	ZCom_Node* getNetworkNode();

private:
	/**
	 * Hide the copy constructor
	 */
	NetworkEntity(const NetworkEntity&) : mNode(0), mRegistered(false) { }

};

template <typename EventType>
bool NetworkEntity::sendEvent(const NetworkEvent<EventType>& event, bool secret) const {
	ZCom_BitStream* stream = new ZCom_BitStream();
	event.serialize(stream);

	eZCom_NodeRole role = mNode->getRole();
	if (role == eZCom_RoleAuthority) {
		if (secret) {
			return mNode->sendEvent(eZCom_ReliableOrdered, ZCOM_REPRULE_AUTH_2_OWNER, stream);
		} else {
			return mNode->sendEvent(eZCom_ReliableOrdered, ZCOM_REPRULE_AUTH_2_ALL, stream);
		}
	} else if (role == eZCom_RoleOwner) {
		return mNode->sendEvent(eZCom_ReliableOrdered, ZCOM_REPRULE_OWNER_2_AUTH, stream);
	}
	// Proxy should not send events for this entity
	return false;
}

}

#endif
