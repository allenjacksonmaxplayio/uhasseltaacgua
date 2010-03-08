#include <Common/Base/hkBase.h>
#include <Common/Base/System/hkBaseSystem.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>

#include "HavokEntityType.h"
#include "BoostPhantom.h"

namespace HovUni {

BoostPhantom::BoostPhantom(const hkAabb& aabb, hkReal boost ):
	hkpAabbPhantom( aabb, 0), mBoost(boost)
{
}

BoostPhantom::~BoostPhantom(void)
{
}

void BoostPhantom::addOverlappingCollidable( hkpCollidable* handle )
{	
	hkpRigidBody* rb = hkGetRigidBody(handle);

	if ( (rb != HK_NULL) && HavokEntityType::isEntityType(rb,HavokEntityType::CHARACTER ) ){
		//TODO make it boost
	}

	hkpAabbPhantom::addOverlappingCollidable( handle );
}

void BoostPhantom::removeOverlappingCollidable( hkpCollidable* handle )
{
	hkpAabbPhantom::removeOverlappingCollidable( handle );
}

}