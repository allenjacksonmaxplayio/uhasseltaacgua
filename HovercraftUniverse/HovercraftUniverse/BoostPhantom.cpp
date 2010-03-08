#include <Common/Base/hkBase.h>
#include <Common/Base/System/hkBaseSystem.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>

#include "HavokEntityType.h"
#include "BoostPhantom.h"
#include "Havok.h"

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
		Character * character = Havok::getSingleton().getCharacter(rb->getName());	
		if ( character != HK_NULL ){
     			hkVector4 boost = character->mForward;
			boost.mul4(mBoost);
			rb->applyLinearImpulseAsCriticalOperation(boost);
		}
	}

	hkpAabbPhantom::addOverlappingCollidable( handle );
}

void BoostPhantom::removeOverlappingCollidable( hkpCollidable* handle )
{
	hkpAabbPhantom::removeOverlappingCollidable( handle );
}

}