#ifndef HK_SIMPLE_GRAVITY_PHANTOM_H
#define HK_SIMPLE_GRAVITY_PHANTOM_H

#include <Physics/Dynamics/Phantom/hkpAabbPhantom.h>

class hkpCollidable;
class hkpRigidBody;

// This phantom surrounds a planet and adds the simple gravity action to overlapping bodies
// It sets the action userdata to be this phantom so that it knows which action to remove. 
class SimpleGravityPhantom : public hkpAabbPhantom
{
	public:
		SimpleGravityPhantom( hkpRigidBody* body, const hkAabb& aabb, const hkpCollidable* hullCollidable, hkUint32 collisionFilterInfo = 0 )
		  : hkpAabbPhantom( aabb, collisionFilterInfo), m_body(body), m_hullCollidable(hullCollidable) {}

		  // Adds the action to overlapping rigid bodies
		  virtual void addOverlappingCollidable( hkpCollidable* handle );

		  // Removes the action from rigid bodies as they leave
		  virtual void removeOverlappingCollidable( hkpCollidable* handle );

	private:
		// Rigid body representing the planet
		hkpRigidBody* m_body;

		// Collidable representing the gravitational field
		const hkpCollidable* m_hullCollidable;
};

#endif  // HK_SIMPLE_GRAVITY_PHANTOM_H
