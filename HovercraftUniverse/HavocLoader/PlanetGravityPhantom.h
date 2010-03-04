#ifndef PLANETGRAVITYPHANTOM_H
#define PLANETGRAVITYPHANTOM_H

#include <Physics/Dynamics/Phantom/hkpAabbPhantom.h>

namespace HovUni {

class PlanetGravityPhantom : public hkpAabbPhantom
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

	/**
	 * Constructor
	 * @param the planet
	 * @param aabb
	 * @param hullCollidable
	 * @param collisionFilterInfo
	 */
	PlanetGravityPhantom(hkpRigidBody* planet, const hkAabb& aabb, const hkpCollidable* hullCollidable, hkUint32 collisionFilterInfo = 0);

	virtual ~PlanetGravityPhantom(void);

	virtual void addOverlappingCollidable( hkpCollidable* handle );

	virtual void removeOverlappingCollidable( hkpCollidable* handle );
};

}

#endif
