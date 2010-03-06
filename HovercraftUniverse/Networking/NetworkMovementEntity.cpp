#include "NetworkMovementEntity.h"

namespace HovUni {

NetworkMovementEntity::NetworkMovementEntity(unsigned short replicators) : NetworkEntity(replicators + 1) {

}

NetworkMovementEntity::~NetworkMovementEntity(void) {

}

void NetworkMovementEntity::update() {
	switch (mNode->getRole())
	{
	case eZCom_RoleOwner:
		break;
	case eZCom_RoleProxy:
		mMoveRep->getExtrapolatedPosition(0, mPosition);
		mMoveRep->getExtrapolatedVelocity(0, mVelocity);
		break;
	default:
		break;
	}
}

void NetworkMovementEntity::setupReplication() {
	// create the movement replicator
	mMoveRep = new ZCom_Replicate_Movement<zFloat, 3>(23, ZCOM_REPFLAG_MOSTRECENT|ZCOM_REPFLAG_SETUPPERSISTS, ZCOM_REPRULE_OWNER_2_AUTH|ZCOM_REPRULE_AUTH_2_PROXY);

	// Set a low error threshold
	((ZCom_RSetupMovement<zFloat>*) mMoveRep->getSetup())->setConstantErrorThreshold(0);

	// Set interpolation time to 50 ms
	((ZCom_RSetupMovement<zFloat>*) mMoveRep->getSetup())->setInterpolationTime(50);

	// Apply timescale
	// TODO improve timescale
	mMoveRep->setTimeScale(0.05f);

	// Add the replicator
	mNode->addReplicator(mMoveRep, true);

	// Set update listener
	mMoveRep->setUpdateListener(this);

	// TODO callback for other replicators
}

void NetworkMovementEntity::correctionReceived(zFloat* pos, zFloat* vel, zFloat* acc, bool teleport, zU32 estimatedTimeSent) {
	// Correction received by authority (Appears on: Owner).

	// Delete simulation time
	mAccumTime = 0;

	// Set object to corrected position
	memcpy(mPosition, pos, sizeof(mPosition));

	// Set object to corrected velocity
	memcpy(mVelocity, vel, sizeof(mVelocity));

	NetworkMovementInput input;
	zU32 time;
	zU32 currenttime = 0;
	void* iter = 0;
	while (true) {
		// Get the next move
		ZCom_BitStream* inputstream = mMoveRep->getNextInputHistoryEntry(&time, &iter);

		// Process until time of next input
		if ((currenttime > 0) && (time - currenttime > 0)) {
			// TODO update physics
		}

		if (!inputstream) {
			// No more moves
			break;
		}

		input.unpack(*inputstream);
		// Apply input
		// TODO apply

		currenttime = time;
	}
}

void NetworkMovementEntity::inputSent(ZCom_BitStream& inputstream) {
	// The input bitstream has just been sent to the authority (Appears on: Owner).

	NetworkMovementInput input;

	// Unpack again
	input.unpack(inputstream);

	// Apply input
	// TODO apply

	// Remember last input we sent to determine if new input is different
	mLastInput = input;
}

void NetworkMovementEntity::inputUpdated(ZCom_BitStream& inputstream, bool inputChanged, zU32 clientTime, zU32 estimatedTimeSent) {
	// New input data arrived from owner. (Appears on: Auth).

	NetworkMovementInput input;

	if (inputChanged) {
		// The input change so unpack and update
		input.unpack(inputstream);
		mLastInput = input;
	} else {
		// The input did not change so use the last input
		input = mLastInput;
	}

	// Check whether we had this update already
	if (clientTime <= mCurrentTime) {
		return;
	}

	// Update object for the time that passed
	// TODO Check for speedhack
	if (mCurrentTime > 0) {
		// TODO update physics
	}

	// Tell the movement replicator about new state
	mMoveRep->updateState(mPosition, mVelocity, 0, false);

	// Remember the time
	mCurrentTime = clientTime;

	// Apply input
	// TODO apply
}

void NetworkMovementEntity::updateReceived(ZCom_BitStream& inputstream, zFloat* pos, zFloat* vel, zFloat* acc, zU32 estimatedTimeSent) {
	// Update received by authority. (Appears on: Proxy).
}

}