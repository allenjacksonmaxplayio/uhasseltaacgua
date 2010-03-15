#include "NetworkEntity.h"

#include "OgreVector3_Replicator.h"
#include "String_Replicator.h"
#include "OgreQuaternion_Replicator.h"

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

void NetworkEntity::networkRegister(NetworkIDManager* idmanager, std::string name) {
	networkRegister(idmanager->getID(name), idmanager->getControl());
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

void NetworkEntity::replicateFloat(float* value, zU8 mantissaBits, zU8 flags, zU8 rules, zS16 minDelay, zS16 maxDelay) {
	mNode->addReplicationFloat(value, mantissaBits, flags, rules, minDelay, maxDelay);
}

void NetworkEntity::replicateOgreVector3(Ogre::Vector3* vector, zU8 mantissaBits, zU8 flags, zU8 rules, zU8 interceptID, zS16 minDelay, zS16 maxDelay, bool autoDelete) {
	mNode->addReplicator(new OgreVector3_Replicator(vector, mantissaBits, flags, rules, interceptID, minDelay, maxDelay), autoDelete);
}

void NetworkEntity::replicateOgreQuaternion(Ogre::Quaternion* quat, zU8 mantissaBits, zU8 flags, zU8 rules, zU8 interceptID, zS16 minDelay, zS16 maxDelay, bool autoDelete) {
	mNode->addReplicator(new OgreQuaternion_Replicator(quat, mantissaBits, flags, rules, interceptID, minDelay, maxDelay), autoDelete);
}

}
