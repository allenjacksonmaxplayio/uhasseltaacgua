#include "NetworkMovementEntity.h"
#include "OgreVector3_Replicator.h"

namespace HovUni {

NetworkMovementEntity::NetworkMovementEntity(unsigned short replicators) : NetworkEntity(replicators + 3), mPosition(0.0f, 0.0f, 0.0f) {
}

NetworkMovementEntity::~NetworkMovementEntity(void) {

}

Ogre::Vector3 NetworkMovementEntity::getPosition() const {
	return mPosition;
}

void NetworkMovementEntity::setPosition(float* pos) {
	mPosition.x = pos[0];
	mPosition.y = pos[1];
	mPosition.z = pos[2];
}

void NetworkMovementEntity::setupReplication() {
	//TODO: min and max delay should be defined, not magic number...
	OgreVector3_Replicator* repli = new OgreVector3_Replicator(&mPosition, 23, ZCOM_REPFLAG_MOSTRECENT, ZCOM_REPRULE_AUTH_2_ALL, 0, 0, 10);
	mNode->addReplicator(repli, true);

	// Callback for other replicators
	addReplicators();
}

}