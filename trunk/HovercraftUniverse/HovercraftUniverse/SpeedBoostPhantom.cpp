#include <Common/Base/hkBase.h>
#include <Common/Base/System/hkBaseSystem.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>

#include "HavokEntityType.h"
#include "SpeedBoostPhantom.h"
#include "Havok.h"

namespace HovUni {

SpeedBoostPhantom::SpeedBoostPhantom(const hkAabb& aabb, SpeedBoost * boost ):
	hkpAabbPhantom( aabb, 0), mBoost(boost)
{
}

SpeedBoostPhantom::~SpeedBoostPhantom(void)
{
}

void SpeedBoostPhantom::addOverlappingCollidable( hkpCollidable* handle )
{	
	hkpRigidBody* rb = hkGetRigidBody(handle);

	if ( (rb != HK_NULL) && HavokEntityType::isEntityType(rb,HavokEntityType::CHARACTER ) ){
		Character * character = Havok::getSingleton().getCharacter(rb->getName());	
		if ( character != HK_NULL ){
     		hkVector4 boost = character->getForward();
			boost.mul4(mBoost->getBoost());
			rb->applyLinearImpulseAsCriticalOperation(boost);
		}
	}

	hkpAabbPhantom::addOverlappingCollidable( handle );
}

void SpeedBoostPhantom::removeOverlappingCollidable( hkpCollidable* handle )
{
	hkpAabbPhantom::removeOverlappingCollidable( handle );
}

}