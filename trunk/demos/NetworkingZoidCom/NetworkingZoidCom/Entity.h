#ifndef ENTITY_H_
#define ENTITY_H_

#define ZCOM_REPFLAG_SETUPAUTODELETE   (1L << 6)
#include <zoidcom/zoidcom_node.h>
#include <string>
using std::string;

namespace HovUni {

/**
 * This class represents an entity.
 *
 * @author Olivier Berghmans
 */
class Entity
{
public:
	/**
	 * Constructor
	 */
	Entity();

	/**
	 * Destructor
	 */
	virtual ~Entity();

	/**
	 * Process the events waiting for this entity. This method
	 * should be called regularly because otherwise events for
	 * this entity will stay in the queue.
	 */
	void processEvents();

	/**
	 * A callback that should be implemented so that events for
	 * this entity are handled in a good way.
	 *
	 * @param event the event that occurred
	 */
	virtual void processEntityEvents(const string& event) = 0;

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
