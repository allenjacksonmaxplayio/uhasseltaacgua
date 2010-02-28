#include <Common/Base/hkBase.h>
#include <Common/Base/System/hkBaseSystem.h>

#include "EntityType.h"
#include "GravityPhantom.h"
#include "PlanetGravityAction.h"

namespace HovUni {

GravityPhantom::GravityPhantom( hkpRigidBody* body, const hkAabb& aabb, const hkpCollidable* hullCollidable, hkUint32 collisionFilterInfo )
		: hkpAabbPhantom( aabb, collisionFilterInfo), mPlanetBody(body), mHullCollidable(hullCollidable) {
}

GravityPhantom::~GravityPhantom(void)
{
}

void GravityPhantom::addOverlappingCollidable( hkpCollidable* handle )
{
	hkpRigidBody* theBody = hkGetRigidBody( handle );

	if( theBody && (theBody->getMotionType() != hkpMotion::MOTION_FIXED) && (EntityType::getEntityType(theBody) != EntityType::PLANET )  )
	{
		hkBool actionFound = false;

		for( int i = 0; i < theBody->getNumActions(); i++ )
		{
			if( theBody->getAction(i)->getUserData() == PlanetGravityAction::HK_SPHERE_ACTION_ID )
			{
				if( static_cast<PlanetGravityAction*>( theBody->getAction(i) )->accessPhantomId()
					== reinterpret_cast<hkUlong>( this ) )
				{
					// Do not add action if one already exists for this rigid body
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

void GravityPhantom::removeOverlappingCollidable( hkpCollidable* handle )
{
	hkpRigidBody* theBody = hkGetRigidBody( handle );
	hkBool actionFound = false;

	if( theBody != HK_NULL )
	{
		for( int i = 0; i < theBody->getNumActions(); i++ )
		{
			// Is there already a PlanetGravityAction on the planet?
			if( theBody->getAction(i)->getUserData() == PlanetGravityAction::HK_SPHERE_ACTION_ID )
			{
				if( static_cast<PlanetGravityAction*>( theBody->getAction(i) )->accessPhantomId()
					== reinterpret_cast<hkUlong>( this ) )
				{
					if( !actionFound )
					{
						theBody->getWorld()->removeActionImmediately( theBody->getAction(i) );
						actionFound = true;
					}
					else
					{
						HK_ASSERT2( 0x0, 0, "Add remove not synchronized.\n" );
					}
				}
			}
		}
	}

	hkpAabbPhantom::removeOverlappingCollidable( handle );
}

}