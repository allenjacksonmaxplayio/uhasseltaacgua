//Havok
#include <Common/Base/hkBase.h>
#include <Common/Base/System/hkBaseSystem.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>

#include "EntityCollisionPrevention.h"

//Havok Framework
#include "Havok.h"
#include "HavokEntity.h"
#include "HavokEntityType.h"

namespace HovUni {

EntityCollisionBinder::EntityCollisionBinder( hkpRigidBody* trackedBody, hkpAabbPhantom* phantomToUpdate , hkReal offset ):
	hkpUnaryAction(trackedBody), mPhantom(phantomToUpdate), mOffset(-1.0f*offset) {
}

EntityCollisionBinder::~EntityCollisionBinder() {
}

void EntityCollisionBinder::applyAction( const hkStepInfo& stepInfo )
{
	// Find the new center to move to
	hkVector4 newCenter = getRigidBody()->getPosition();

	hkRotation ro;
	ro.set(getRigidBody()->getRotation());
	hkVector4 forward = ro.getColumn(2);
	forward.mul4(mOffset);

	newCenter.add4(forward);

	// Grab the halfextents of the phantom's AABB
	hkVector4 halfExtents;
	halfExtents.setSub4( mPhantom->getAabb().m_max, mPhantom->getAabb().m_min );
	halfExtents.mul4( 0.5f );

	// Create a new AABB for the phantom, of the same size
	hkAabb newAabb;
	newAabb.m_min.setSub4( newCenter, halfExtents );
	newAabb.m_max.setAdd4( newCenter, halfExtents );

	// Update the phantom's AABB so it encloses the rigid body
	mPhantom->setAabb( newAabb );
}

/////////////////

EntityCollisionPhantom::EntityCollisionPhantom(const hkAabb& aabb, HavokEntity * entity):
	hkpAabbPhantom( aabb, 0), mEntity(entity) {
}

EntityCollisionPhantom::~EntityCollisionPhantom(void){
}


void EntityCollisionPhantom::addOverlappingCollidable( hkpCollidable* handle ){
	hkpRigidBody* rb = hkGetRigidBody(handle);

	//if something enters bounding box that is't the planet
	if ( (rb != HK_NULL) && !HavokEntityType::isEntityType(rb,HavokEntityType::PLANET ) ) {
		//TODO send event
		std::cout << "WATCH OUT" << std::endl;
	}
}

void EntityCollisionPhantom::removeOverlappingCollidable( hkpCollidable* handle ){
	hkpRigidBody* rb = hkGetRigidBody(handle);

	//if something leaves bounding box that is't the planet
	if ( (rb != HK_NULL) && !HavokEntityType::isEntityType(rb,HavokEntityType::PLANET ) ) {
		//TODO send event
		std::cout << "PHEW" << std::endl;
	}
}

}
