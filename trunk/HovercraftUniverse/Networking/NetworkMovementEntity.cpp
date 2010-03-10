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
	replicateOgreVector3(&mPosition);

	// Callback for other replicators
	addReplicators();
}

}