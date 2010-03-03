#ifndef PUSHGRAVITYPHANTOM_H
#define PUSHGRAVITYPHANTOM_H

#include <Physics/Dynamics/Phantom/hkpAabbPhantom.h>

namespace HovUni {

class PushGravityPhantom : public hkpAabbPhantom
{
private:
	
	/**
	 * Rigid body representing the planet
	 */
	hkpRigidBody* mPlanetBody;

	/**
	 * Collidable representing the gravitational field
	 */
	const hkpCollidable * mHullCollidable;

public:
	PushGravityPhantom(hkpRigidBody* planet, const hkAabb& aabb, const hkpCollidable* hullCollidable, hkUint32 collisionFilterInfo = 0);
	
	virtual ~PushGravityPhantom(void);

	virtual void addOverlappingCollidable( hkpCollidable* handle );

	virtual void removeOverlappingCollidable( hkpCollidable* handle );
};

}

#endif
