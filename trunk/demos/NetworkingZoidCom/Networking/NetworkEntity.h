#ifndef NETWORKENTITY_H_
#define NETWORKENTITY_H_

#define ZCOM_REPFLAG_SETUPAUTODELETE   (1L << 6)

#include "Event.h"
#include <string>
#include <zoidcom/zoidcom_node.h>

using std::string;

namespace HovUni {

/**
 * This class represents an entity.
 *
 * @author Olivier Berghmans
 */
class NetworkEntity
{
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
	 * Process the events waiting for this entity. This method
	 * should be called regularly because otherwise events for
	 * this entity will stay in the queue.
	 */
	void processEvents();

	/**
	 * A callback that should be implemented so that events for
	 * this entity are handled in a good way. Normally this method
	 * would first parse the stream to an event and then process
	 * the event.
	 *
	 * @param stream the bitstream containing the event
	 */
	virtual void parseEntityEvents(ZCom_BitStream* stream) = 0;

	/**
	 * Get the network node. You should probably not be calling this.
	 *
	 * @return the network node
	 */
	ZCom_Node* getNetworkNode();

protected:
	/** The network node */
	ZCom_Node* mNode;

	/** Indicator whether server deleted this object */
	bool mDeleteMe;

};

}

#endif
