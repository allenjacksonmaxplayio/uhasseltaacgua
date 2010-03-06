#include "NetworkEntity.h"

namespace HovUni {

NetworkEntity::NetworkEntity(unsigned short replicators) : mNode(0), mReplicatorNr(replicators), mRegistered(false) {
	mNode = new ZCom_Node();
}

NetworkEntity::~NetworkEntity() {
	if (mNode) {
		delete mNode;
		mNode = 0;
	}
}

void NetworkEntity::networkRegister(ZCom_ClassID id, ZCom_Control* control) {
	// Set up replication
	mNode->beginReplicationSetup(mReplicatorNr);
	setupReplication();
	mNode->endReplicationSetup();

	// Register to node
	mNode->registerNodeDynamic(id, control);
	mRegistered = true;
}

bool NetworkEntity::isRegistered() const {
	return mRegistered;
}

void NetworkEntity::processEvents(float timeSince) {
	while (mNode->checkEventWaiting()) {
		eZCom_Event type;
		eZCom_NodeRole remote_role;
		ZCom_ConnID conn_id;

		ZCom_BitStream* data = mNode->getNextEvent(&type, &remote_role, &conn_id);

		/*if (remote_role == eZCom_RoleAuthority && type == eZCom_EventRemoved) {
			mDeleteMe = true;
		} else*/
		if (type == eZCom_EventUser) {
			// Delegate to the user events callback
			parseEvents(data, timeSince);
		}
	}
}

ZCom_Node* NetworkEntity::getNetworkNode() {
	return mNode;
}

}
