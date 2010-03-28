#ifndef ENTITY_COLLISION_PREVENTION_H
#define ENTITY_COLLISION_PREVENTION_H

#include <Physics/Dynamics/Phantom/hkpAabbPhantom.h>

namespace HovUni {

class HavokEntity;

class EntityCollisionPrevention : public hkpAabbPhantom
{
private:

	HavokEntity * mEntity;	

public:

	/**
	 * Constructor
	 * @param aabb, the bounding box
	 */
	EntityCollisionPrevention(const hkAabb& aabb, HavokEntity * entity);

	~EntityCollisionPrevention(void);

	virtual void addOverlappingCollidable( hkpCollidable* handle );

	virtual void removeOverlappingCollidable( hkpCollidable* handle );
};

}

#endif