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

public:

	/**
	 * Constructor
	 * @param collisionPrevention
	 */
	EntityCollisionBinder( EntityCollisionPhantom * collisionPrevention );

	~EntityCollisionBinder();

private:

	EntityCollisionPhantom * mCollisionPrevention;

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

	friend class EntityCollisionBinder;

	//The entity
	HavokEntity * mEntity;	

	//The bind action, this action binds the phantom to the entity
	EntityCollisionBinder * mBinder;

public:

	/**
	 * Constructor
	 * @param aabb, the bounding box
	 */
	EntityCollisionPhantom(const hkAabb& aabb, HavokEntity * entity);

	~EntityCollisionPhantom(void);

	virtual void addOverlappingCollidable( hkpCollidable* handle );

	virtual void removeOverlappingCollidable( hkpCollidable* handle );


};

}

#endif