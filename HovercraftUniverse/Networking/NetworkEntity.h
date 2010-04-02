#ifndef NETWORKENTITY_H_
#define NETWORKENTITY_H_

#define ZCOM_REPFLAG_SETUPAUTODELETE   (1L << 6)

#include "NetworkEvent.h"
#include "NetworkIDManager.h"
#include <OgreVector3.h>
#include <zoidcom/zoidcom_node.h>
#include <string>

namespace HovUni {

/**
 * This class represents a network entity.
 *
 * @author Olivier Berghmans
 */
class NetworkEntity
{
protected:
	/** The network node */
	ZCom_Node* mNode;

	/** The estimated number of replicators */
	unsigned short mReplicatorNr;

	/** Whether the entity is registered to the network */
	bool mRegistered;

	/** Whether the entity is deleted on the network */
	bool mDeleted;

public:
	/**
	 * Constructor
	 *
	 * @param replicators the estimated number of replicators for this entity
	 */
	NetworkEntity(unsigned short replicators);

	/**
	 * Destructor
	 */
	virtual ~NetworkEntity();

	/**
	 * Register the node for the network
	 *
	 * @param id the zoidcom class ID
	 * @param control the zoidcom control
	 * @param announce whether the announcement data should be set (Use this on server only)
	 */
	void networkRegister(ZCom_ClassID id, ZCom_Control* control, bool announce = false);

	/**
	 * Register the node for the network
	 *
	 * @param idmanager the network ID manager
	 * @param name the registered class name
	 * @param announce whether the announcement data should be set (Use this on server only)
	 */
	void networkRegister(NetworkIDManager* idmanager, std::string name, bool announce = false);

	/**
	 * Register a singleton object on the network.
	 *
	 * @param id the zoidcom class ID
	 * @param control the zoidcom control
	 * @param authority whether we are the authority of this object or not (server only)
	 */
	void networkRegisterUnique(ZCom_ClassID id, ZCom_Control* control, bool authority = false);

	/**
	 * Register a singleton object on the network.
	 *
	 * @param idmanager the network ID manager
	 * @param name the registered class name
	 * @param authority whether we are the authority of this object or not (server only)
	 */
	void networkRegisterUnique(NetworkIDManager* idmanager, std::string name, bool authority = false);

	/**
	 * Check whether the entity is registered for the network
	 *
	 * @return true if the entity is registered
	 */
	bool isRegistered() const;

	/**
	 * Check whether the entity is deleted on the network
	 *
	 * @return true if the entity was deleted
	 */
	bool isDeleted() const;

	/**
	 * Process the events waiting for this entity. This method
	 * should be called regularly because otherwise events for
	 * this entity will stay in the queue.
	 *
	 * @param timeSince the time since the last process of the events
	 */
	void processEvents(float timeSince);

	/**
	 * Send an event for this entity
	 *
	 * @param event the network event
	 * @param secret false if the data may be send to all proxies
	 * @return result of the send operation
	 */
	template <typename EventType, int N>
	bool sendEvent(const NetworkEvent<EventType, N>& event, bool secret = false) const;

	/**
	 * Send an event for this entity
	 *
	 * @param event the network event
	 * @param id the ID to send to
	 * @return result of the send operation
	 */
	template <typename EventType, int N>
	bool sendEventDirect(const NetworkEvent<EventType, N>& event, ZCom_ConnID id) const;

	/**
	 * Get the network node. You should probably not be calling this.
	 *
	 * @return the network node
	 */
	ZCom_Node* getNetworkNode();

	/**
	 * Add a replicator interceptor
	 *
	 * @param interceptor The interceptor to add
	 */
	void setReplicationInterceptor(ZCom_NodeReplicationInterceptor* interceptor);

private:
	/**
	 * Hide the copy constructor
	 */
	NetworkEntity(const NetworkEntity&) : mNode(0), mRegistered(false) { }

	/**
	 * A callback that should be implemented so that events for
	 * this entity are handled in a good way. Normally this method
	 * would first parse the stream to an event and then process
	 * the event.
	 *
	 * @param type off event
	 * @param role of remote
	 * @param connection id of remote
	 * @param stream the bitstream containing the event
	 * @param timeSince the time since the last processing of the events
	 */
	virtual void parseEvents(eZCom_Event type, eZCom_NodeRole remote_role, ZCom_ConnID conn_id, ZCom_BitStream* stream, float timeSince) = 0;

protected:


	/**
	 * A callback that should be implemented so the replicators for this
	 * entity can be set up. In case the number of replicators given to the
	 * constructor is zero, this callback can be implemented as empty.
	 */
	virtual void setupReplication() = 0;

	/**
	 * A callback that should be implemented so the announcement data for this
	 * entity can be set.
	 *
	 * @param stream the bitstream where the data can be set
	 */
	virtual void setAnnouncementData(ZCom_BitStream* stream) = 0;


	/**
	 * Add a float to the replicated variabels
	 *
	 * @param value The float to replicate
	 */
	void replicateFloat(float* value, zU8 mantissaBits = 23, zU8 flags = ZCOM_REPFLAG_MOSTRECENT, zU8 rules = ZCOM_REPRULE_AUTH_2_ALL, zS16 minDelay = 0, zS16 maxDelay = 10);
	
	/**
	 * Add a vector to the replicated variabels
	 *
	 * @param vector The vector to replicate
	 */
	void replicateOgreVector3(Ogre::Vector3* vector, zU8 mantissaBits = 23, zU8 flags = ZCOM_REPFLAG_MOSTRECENT, zU8 rules = ZCOM_REPRULE_AUTH_2_ALL, zU8 interceptID = 0, zS16 minDelay = 0, zS16 maxDelay = 10, bool autoDelete = true);

	/**
	 * Add a quaternion to the replicated variabels
	 *
	 * @param qut the quaternion to replicate
	 */
	void replicateOgreQuaternion(Ogre::Quaternion* quat, zU8 mantissaBits = 23, zU8 flags = ZCOM_REPFLAG_MOSTRECENT, zU8 rules = ZCOM_REPRULE_AUTH_2_ALL, zU8 interceptID = 0, zS16 minDelay = 0, zS16 maxDelay = 10, bool autoDelete = true);

	/**
	 * Add a string to the replicated variabels
	 *
	 * @param str the string to replicate
	 */
	void replicateString(Ogre::String * str, zU8 flags = ZCOM_REPFLAG_MOSTRECENT, zU8 rules = ZCOM_REPRULE_AUTH_2_ALL, zU8 interceptID = 0, zS16 minDelay = 0, zS16 maxDelay = 10, bool autoDelete = true);


};

template <typename EventType, int N>
bool NetworkEntity::sendEvent(const NetworkEvent<EventType, N>& event, bool secret) const {
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

template <typename EventType, int N>
bool NetworkEntity::sendEventDirect(const NetworkEvent<EventType, N>& event, ZCom_ConnID id) const {
	ZCom_BitStream* stream = new ZCom_BitStream();
	event.serialize(stream);
	return mNode->sendEventDirect(eZCom_ReliableOrdered, stream, id);
}

}

#endif
