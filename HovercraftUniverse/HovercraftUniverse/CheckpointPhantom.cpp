#include <Common/Base/hkBase.h>
#include <Common/Base/System/hkBaseSystem.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>

#include "CheckpointPhantom.h"
#include "HavocEntityType.h"

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

	if ( (rb != HK_NULL) && HavocEntityType::isEntityType(rb,HavocEntityType::CHARACTER ) ){
		//TODO make it pass the checkpoint
	}


	hkpAabbPhantom::addOverlappingCollidable( handle );
}

void CheckpointPhantom::removeOverlappingCollidable( hkpCollidable* handle )
{
	hkpAabbPhantom::removeOverlappingCollidable( handle );
}

}