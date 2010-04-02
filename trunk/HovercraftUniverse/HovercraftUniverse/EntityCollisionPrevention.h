#ifndef ENTITY_COLLISION_PREVENTION_H
#define ENTITY_COLLISION_PREVENTION_H

#include <Physics/Dynamics/Phantom/hkpAabbPhantom.h>
#include <Physics/Dynamics/Action/hkpUnaryAction.h>

namespace HovUni {

class HavokEntity;
class EntityCollisionPhantom;

/**
 * Class that binds an Entity Collision System to the entity
 */
class EntityCollisionBinder : public hkpUnaryAction {

private:

	hkpAabbPhantom * mPhantom;

	hkReal mOffset;

public:

	/**
	 * Constructor
	 * @param collisionPrevention
	 */
	EntityCollisionBinder( hkpRigidBody* trackedBody, hkpAabbPhantom* phantomToUpdate, hkReal offset );

	~EntityCollisionBinder();

private:

	virtual void applyAction( const hkStepInfo& stepInfo );

	virtual hkpAction* clone( const hkArray<hkpEntity*>& newEntities, const hkArray<hkpPhantom*>& newPhantoms ) const { 
		return HK_NULL; 
	}

};

/**
 * Phantom used to detect incomming objects, must be placed in front of entity
 */
class EntityCollisionPhantom : public hkpAabbPhantom
{
private:

	//The entity
	HavokEntity * mEntity;	

public:

	/**
	 * Constructor, creates a Collision phantom.
	 * This will not add the phantom to the world and will not bind the phantom to the entity!
	 * Use the bind method for this.
	 *
	 * @param aabb, the bounding box
	 */
	EntityCollisionPhantom(const hkAabb& aabb, HavokEntity * entity);

	~EntityCollisionPhantom(void);

	virtual void addOverlappingCollidable( hkpCollidable* handle );

	virtual void removeOverlappingCollidable( hkpCollidable* handle );

};

}

#endif