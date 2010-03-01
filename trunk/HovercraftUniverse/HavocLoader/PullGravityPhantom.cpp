#include <Common/Base/hkBase.h>
#include <Common/Base/System/hkBaseSystem.h>

#include "EntityType.h"
#include "PullGravityPhantom.h"
#include "PullPlanetGravityAction.h"

namespace HovUni {

PullGravityPhantom::PullGravityPhantom( hkpRigidBody* body, const hkAabb& aabb, const hkpCollidable* hullCollidable, hkUint32 collisionFilterInfo )
		: hkpAabbPhantom( aabb, collisionFilterInfo), mPlanetBody(body), mHullCollidable(hullCollidable) {
}

PullGravityPhantom::~PullGravityPhantom(void)
{
}

void PullGravityPhantom::addOverlappingCollidable( hkpCollidable* handle )
{
	hkpRigidBody* theBody = hkGetRigidBody( handle );

	if( theBody && (theBody->getMotionType() != hkpMotion::MOTION_FIXED) && (EntityType::getEntityType(theBody) != EntityType::PLANET )  )
	{
		hkBool actionFound = false;

		for( int i = 0; i < theBody->getNumActions(); i++ )
		{
			if( theBody->getAction(i)->getUserData() == PullPlanetGravityAction::HK_SPHERE_ACTION_ID )
			{
				if( static_cast<PullPlanetGravityAction*>( theBody->getAction(i) )->accessPhantomId() == reinterpret_cast<hkUlong>( this ) )
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
			PullPlanetGravityAction* newGravity = new PullPlanetGravityAction( mPlanetBody, theBody, mHullCollidable, reinterpret_cast<hkUlong>( this ) );
			theBody->getWorld()->addAction( newGravity );
			newGravity->removeReference();
		}

	}

	hkpAabbPhantom::addOverlappingCollidable( handle );
}

void PullGravityPhantom::removeOverlappingCollidable( hkpCollidable* handle )
{
	hkpRigidBody* theBody = hkGetRigidBody( handle );

	if( theBody != HK_NULL )
	{
		for( int i = 0; i < theBody->getNumActions(); i++ )
		{
			// Is there already a PullPlanetGravityAction on the planet?
			if( theBody->getAction(i)->getUserData() == PullPlanetGravityAction::HK_SPHERE_ACTION_ID )
			{
				if( static_cast<PullPlanetGravityAction*>( theBody->getAction(i) )->accessPhantomId() == reinterpret_cast<hkUlong>( this ) )
				{
					theBody->getWorld()->removeAction( theBody->getAction(i) );
				}
			}
		}
	}

	hkpAabbPhantom::removeOverlappingCollidable( handle );
}

}