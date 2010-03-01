#ifndef PUSHPLANETGRAVITYACTION_H
#define PUSHPLANETGRAVITYACTION_H

#include <Physics/Dynamics/Action/hkpUnaryAction.h>

namespace HovUni {

class PushPlanetGravityAction : public hkpUnaryAction
{
	private:

		/**
		 * Planet to which we are being attracted
		 */
		hkpRigidBody* mPlanetBody;

		/**
		 * The collidable representing the gravitational field
		 */
		const hkpCollidable* mHullCollidable;

		/**
		 * Phantom ID, if a phantom has been associated with this action then we have this ID so that
		 * we can search through a body's actions and update values as necessary
		 */
		hkUlong mPhantomId;

		/**
		 * Max Acceleration used for objects inside innerRadius
		 */
		hkReal mGravityForce;

public:

	static const hkUlong HK_SPHERE_ACTION_ID = 0x28022978;

	/**
	 * Constructor
	 * @param planetBody
	 * @param satellite
	 * @param hullCollidable
	 * @param phantomId, 0 for no phantomID
	 * @param maxAcceleration
	 */
	PushPlanetGravityAction( hkpRigidBody* planetBody, hkpRigidBody* satellite, const hkpCollidable* hullCollidable, hkUlong phantomId, hkReal maxAcceleration = 200.0f );

	/**
	 * Get the phantom ID
	 * @return phantom ID
	 */
	inline hkUlong& accessPhantomId() {
		return mPhantomId;
	}

private:

	virtual void applyAction( const hkStepInfo& stepInfo );

	virtual hkpAction* clone( const hkArray<hkpEntity*>& newEntities, const hkArray<hkpPhantom*>& newPhantoms ) const { return HK_NULL; }


};

}

#endif
