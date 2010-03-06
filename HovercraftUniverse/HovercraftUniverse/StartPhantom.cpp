#include <Common/Base/hkBase.h>
#include <Common/Base/System/hkBaseSystem.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>

#include "StartPhantom.h"
#include "HavocEntityType.h"

namespace HovUni {

StartPhantom::StartPhantom(const hkAabb& aabb ):
	hkpAabbPhantom( aabb, 0)
{
}

StartPhantom::~StartPhantom(void)
{
}

void StartPhantom::addOverlappingCollidable( hkpCollidable* handle )
{
	hkpRigidBody* rb = hkGetRigidBody(handle);

	if ( (rb != HK_NULL) && HavocEntityType::isEntityType(rb,HavocEntityType::CHARACTER ) ){
		//TODO make it pass start
	}

	hkpAabbPhantom::addOverlappingCollidable( handle );
}

void StartPhantom::removeOverlappingCollidable( hkpCollidable* handle )
{
	hkpAabbPhantom::removeOverlappingCollidable( handle );
}

}