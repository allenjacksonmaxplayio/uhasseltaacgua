#ifndef NETWORKMOVEMENTENTITY_H_
#define NETWORKMOVEMENTENTITY_H_

#include "NetworkEntity.h"
#include "NetworkMovementInput.h"

namespace HovUni {

/**
 * This class represents a network entity that has a position and can
 * include movement.
 *
 * @author Olivier Berghmans
 */
class NetworkMovementEntity: public NetworkEntity, public ZCom_MoveUpdateListener<zFloat> {
private:
	/** The position */
	float mPosition[3];

	/** The velocity */
	float mVelocity[3];

	/** The movement replicator */
	ZCom_Replicate_Movement<zFloat, 3>* mMoveRep;

	/** The last input received */
	NetworkMovementInput mLastInput;

	/** The time of the last received update */
    zU32 mCurrentTime;

    /** The accumulated simulation time */
    zU32 mAccumTime;

public:
	/**
	 * Constructor
	 *
	 * @param replicators the estimated number of replicators for this entity
	 */
	NetworkMovementEntity(unsigned short replicators = 0);

	/**
	 * Destructor
	 */
	~NetworkMovementEntity();

	/**
	 * Update the network movement entity
	 */
	void update();

private:
	/**
	 * @see NetworkEntity::setReplication()
	 */
	void setupReplication();

	/**
	 * @see ZCom_MoveUpdateListener<zFloat>::correctionReceived(zFloat* pos, zFloat* vel, zFloat* acc, bool teleport, zU32 estimatedTimeSent)
	 */
	virtual void correctionReceived(zFloat* pos, zFloat* vel, zFloat* acc, bool teleport, zU32 estimatedTimeSent);

	/**
	 * @see ZCom_MoveUpdateListener<zFloat>::inputSent(ZCom_BitStream& inputstream)
	 */
	virtual void inputSent(ZCom_BitStream& inputstream);

	/**
	 * @see ZCom_MoveUpdateListener<zFloat>::inputUpdated(ZCom_BitStream& inputstream, bool inputChanged, zU32 clientTime, zU32 estimatedTimeSent)
	 */
	virtual void inputUpdated(ZCom_BitStream& inputstream, bool inputChanged, zU32 clientTime, zU32 estimatedTimeSent);

	/**
	 * @see ZCom_MoveUpdateListener<zFloat>::updateReceived(ZCom_BitStream& inputstream, zFloat* pos, zFloat* vel, zFloat* acc, zU32 estimatedTimeSent)
	 */
	virtual void updateReceived(ZCom_BitStream& inputstream, zFloat* pos, zFloat* vel, zFloat* acc, zU32 estimatedTimeSent);

};

}

#endif
