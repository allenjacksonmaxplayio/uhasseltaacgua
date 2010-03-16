#include <Common/Base/hkBase.h>
#include <Common/Base/System/hkBaseSystem.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>

#include "FinishPhantom.h"
#include "HavokEntityType.h"

namespace HovUni {

FinishPhantom::FinishPhantom(const hkAabb& aabb ):
	hkpAabbPhantom( aabb, 0)
{
}

FinishPhantom::~FinishPhantom(void)
{
}

void FinishPhantom::addOverlappingCollidable( hkpCollidable* handle )
{
	hkpRigidBody* rb = hkGetRigidBody(handle);

	if ( (rb != HK_NULL) && HavokEntityType::isEntityType(rb,HavokEntityType::CHARACTER ) ) {
		//TODO make it pass finish
	}

	hkpAabbPhantom::addOverlappingCollidable( handle );
}

void FinishPhantom::removeOverlappingCollidable( hkpCollidable* handle )
{
	hkpAabbPhantom::removeOverlappingCollidable( handle );
}

}