#include <Common/Base/hkBase.h>
#include <Common/Base/System/hkBaseSystem.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>

#include "CheckpointPhantom.h"
#include "HavokEntityType.h"
#include "Havok.h"

namespace HovUni {

CheckpointPhantom::CheckpointPhantom(const hkAabb& aabb, hkString name, hkInt32 nummer ):
	hkpAabbPhantom( aabb, 0), mName(name), mNummer(nummer)
{
}

CheckpointPhantom::~CheckpointPhantom(void)
{
}

void CheckpointPhantom::addOverlappingCollidable( hkpCollidable* handle )
{
	hkpRigidBody* rb = hkGetRigidBody(handle);

	if ( (rb != HK_NULL) && HavokEntityType::isEntityType(rb,HavokEntityType::CHARACTER ) ){
		//TODO make it pass the checkpoin
		Character * character = Havok::getSingleton().getCharacter(rb->getName());
	}

	hkpAabbPhantom::addOverlappingCollidable( handle );
}

void CheckpointPhantom::removeOverlappingCollidable( hkpCollidable* handle )
{
	hkpRigidBody* rb = hkGetRigidBody(handle);

	if ( (rb != HK_NULL) && HavokEntityType::isEntityType(rb,HavokEntityType::CHARACTER ) ){

	}

	hkpAabbPhantom::removeOverlappingCollidable( handle );
}

}