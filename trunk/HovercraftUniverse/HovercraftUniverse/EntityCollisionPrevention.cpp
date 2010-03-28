//Havok
#include <Common/Base/hkBase.h>
#include <Common/Base/System/hkBaseSystem.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>

#include "EntityCollisionPrevention.h"

//Havok Framework
#include "HavokEntity.h"
#include "HavokEntityType.h"

namespace HovUni {

EntityCollisionPrevention::EntityCollisionPrevention(const hkAabb& aabb, HavokEntity * entity):
	hkpAabbPhantom( aabb, 0), mEntity(entity) {
}

EntityCollisionPrevention::~EntityCollisionPrevention(void){
}

void EntityCollisionPrevention::addOverlappingCollidable( hkpCollidable* handle ){
	hkpRigidBody* rb = hkGetRigidBody(handle);

	//if something enters bounding box that is't the planet
	if ( (rb != HK_NULL) && !HavokEntityType::isEntityType(rb,HavokEntityType::PLANET ) ) {
		//TODO send event
	}
}

void EntityCollisionPrevention::removeOverlappingCollidable( hkpCollidable* handle ){
	hkpRigidBody* rb = hkGetRigidBody(handle);

	//if something leaves bounding box that is't the planet
	if ( (rb != HK_NULL) && !HavokEntityType::isEntityType(rb,HavokEntityType::PLANET ) ) {
		//TODO send event
	}
}

}
