#include <Common/Base/hkBase.h>
#include <Common/Base/System/hkBaseSystem.h>

#include <stdio.h>

#include "EntityType.h"
#include "PushGravityPhantom.h"
#include "PushPlanetGravityAction.h"


namespace HovUni {

PushGravityPhantom::PushGravityPhantom(hkpRigidBody* body, const hkAabb& aabb, const hkpCollidable* hullCollidable, hkUint32 collisionFilterInfo)
	: hkpAabbPhantom( aabb, collisionFilterInfo), mPlanetBody(body), mHullCollidable(hullCollidable)
{
}

PushGravityPhantom::~PushGravityPhantom(void)
{
}

void PushGravityPhantom::addOverlappingCollidable( hkpCollidable* handle )
{
	hkpRigidBody* theBody = hkGetRigidBody( handle );

	if( theBody && (EntityType::getEntityType(theBody) == EntityType::CHARACTER )  )
	{
		hkBool actionFound = false;
		printf("NAME: %s", theBody->getName());
	
		for( int i = 0; i < theBody->getNumActions(); i++ )
		{
			if( theBody->getAction(i)->getUserData() == PushPlanetGravityAction::HK_SPHERE_ACTION_ID )
			{
				if( static_cast<PushPlanetGravityAction*>( theBody->getAction(i) )->accessPhantomId()
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
			PushPlanetGravityAction* newGravity = new PushPlanetGravityAction( mPlanetBody, theBody, mHullCollidable, reinterpret_cast<hkUlong>( this ) );
			theBody->getWorld()->addAction( newGravity );
			newGravity->removeReference();
		}
	}	

	hkpAabbPhantom::addOverlappingCollidable( handle );
}



void PushGravityPhantom::removeOverlappingCollidable( hkpCollidable* handle )
{
	hkpRigidBody* theBody = hkGetRigidBody( handle );
	hkBool actionFound = false;

	if( theBody != HK_NULL )
	{
		for( int i = 0; i < theBody->getNumActions(); i++ )
		{
			// Is there already a PlanetGravityAction on the planet?
			if( theBody->getAction(i)->getUserData() == PushPlanetGravityAction::HK_SPHERE_ACTION_ID )
			{
				if( static_cast<PushPlanetGravityAction*>( theBody->getAction(i) )->accessPhantomId()
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
