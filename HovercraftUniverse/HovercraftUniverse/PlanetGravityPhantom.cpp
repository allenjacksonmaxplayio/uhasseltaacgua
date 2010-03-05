#include <Common/Base/hkBase.h>
#include <Common/Base/System/hkBaseSystem.h>

#include "HavocEntityType.h"
#include "PlanetGravityPhantom.h"
#include "PlanetGravityAction.h"

namespace HovUni {

PlanetGravityPhantom::PlanetGravityPhantom( hkpRigidBody* body, const hkAabb& aabb, const hkpCollidable* hullCollidable, hkUint32 collisionFilterInfo )
		: hkpAabbPhantom( aabb, collisionFilterInfo), mPlanetBody(body), mHullCollidable(hullCollidable) {
}

PlanetGravityPhantom::~PlanetGravityPhantom(void)
{
}

void PlanetGravityPhantom::addOverlappingCollidable( hkpCollidable* handle )
{
	hkpRigidBody* theBody = hkGetRigidBody( handle );

	if( theBody && (theBody->getMotionType() != hkpMotion::MOTION_FIXED) && (HavocEntityType::getEntityType(theBody) != HavocEntityType::PLANET )  )
	{
		hkBool actionFound = false;

		for( int i = 0; i < theBody->getNumActions(); i++ )
		{
			if( theBody->getAction(i)->getUserData() == PlanetGravityAction::HK_SPHERE_ACTION_ID )
			{
				if( static_cast<PlanetGravityAction*>( theBody->getAction(i) )->accessPhantomId() == reinterpret_cast<hkUlong>( this ) )
				{
					//Do not add action if one already exists for this rigid body
					actionFound = true;
					break;
				}
			}
		}

		if( !actionFound )
		{
			// Add an action
			PlanetGravityAction* newGravity = new PlanetGravityAction( mPlanetBody, theBody, mHullCollidable, reinterpret_cast<hkUlong>( this ) );
			theBody->getWorld()->addAction( newGravity );
			newGravity->removeReference();
		}

	}

	hkpAabbPhantom::addOverlappingCollidable( handle );
}

void PlanetGravityPhantom::removeOverlappingCollidable( hkpCollidable* handle )
{
	hkpRigidBody* theBody = hkGetRigidBody( handle );

	if( theBody != HK_NULL )
	{
		for( int i = 0; i < theBody->getNumActions(); i++ )
		{
			// Is there already a PullPlanetGravityAction on the planet?
			if( theBody->getAction(i)->getUserData() == PlanetGravityAction::HK_SPHERE_ACTION_ID )
			{
				if( static_cast<PlanetGravityAction*>( theBody->getAction(i) )->accessPhantomId() == reinterpret_cast<hkUlong>( this ) )
				{
					theBody->getWorld()->removeAction( theBody->getAction(i) );
				}
			}
		}
	}

	hkpAabbPhantom::removeOverlappingCollidable( handle );
}

}