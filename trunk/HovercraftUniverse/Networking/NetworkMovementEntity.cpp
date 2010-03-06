#include "NetworkMovementEntity.h"

namespace HovUni {

NetworkMovementEntity::NetworkMovementEntity(unsigned short replicators) : NetworkEntity(replicators + 3) {
	mPosition[0] = 0;
	mPosition[1] = 0;
	mPosition[2] = 0;
}

NetworkMovementEntity::~NetworkMovementEntity(void) {

}

void NetworkMovementEntity::getPosition(float* pos) const {
	pos[0] = mPosition[0];
	pos[1] = mPosition[1];
	pos[2] = mPosition[2];
}

void NetworkMovementEntity::setPosition(float* pos) {
	mPosition[0] = pos[0];
	mPosition[1] = pos[1];
	mPosition[2] = pos[2];
}

void NetworkMovementEntity::setupReplication() {
	mNode->addInterpolationFloat(&mPosition[0], 23, ZCOM_REPFLAG_MOSTRECENT, ZCOM_REPRULE_AUTH_2_ALL, 50.0f);
	mNode->addInterpolationFloat(&mPosition[1], 23, ZCOM_REPFLAG_MOSTRECENT, ZCOM_REPRULE_AUTH_2_ALL, 50.0f);
	mNode->addInterpolationFloat(&mPosition[2], 23, ZCOM_REPFLAG_MOSTRECENT, ZCOM_REPRULE_AUTH_2_ALL, 50.0f);

	// Callback for other replicators
	addReplicators();
}

}