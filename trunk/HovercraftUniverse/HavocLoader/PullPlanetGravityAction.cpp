#include "PlanetGravityAction.h"
#include "EntityType.h"
#include "HoverCraftUniverseWorld.h"

#include <Physics/Collide/Query/Collector/PointCollector/hkpClosestCdPointCollector.h>
#include <Physics/Collide/Agent/hkpProcessCollisionInput.h>
#include <Physics/Collide/Dispatch/hkpCollisionDispatcher.h>

namespace HovUni {

PlanetGravityAction::PlanetGravityAction( hkpRigidBody* planetBody, hkpRigidBody* satellite, const hkpCollidable* hullCollidable, hkUlong phantomId, hkReal maxAcceleration ):
		hkpUnaryAction(satellite), 
		mPlanetBody(planetBody), 
		mHullCollidable(hullCollidable), 
		mPhantomId(phantomId), 
		mGravityForce(maxAcceleration)
{
	setUserData( HK_SPHERE_ACTION_ID );
}

void PlanetGravityAction::applyAction( const hkStepInfo& stepInfo )
{
	hkpRigidBody* rb = getRigidBody();

	// Sets forceDir to be the difference of m_center and rb->getCenterOfMassInWorld().
	hkVector4 forceDir;

	hkpCollisionInput input = *getWorld()->getCollisionInput();
	hkpClosestCdPointCollector collector;
	hkpShapeType a = rb->getCollidable()->getShape()->getType();
	input.m_tolerance = 1.0f;

	do {
		// Use mHullCollidable for gravity calculations if available.
		// GetClosestPoints() should provide a gravity vector
		if( mHullCollidable == HK_NULL)
		{
			hkpShapeType b = mPlanetBody->getCollidable()->getShape()->getType();
			hkpCollisionDispatcher::GetClosestPointsFunc getClosestPoints = getWorld()->getCollisionDispatcher()->getGetClosestPointsFunc( a, b );
			getClosestPoints( *rb->getCollidable(), *mPlanetBody->getCollidable(), input, collector );
		}
		else
		{
			hkpShapeType b = mHullCollidable->getShape()->getType();
			hkpCollisionDispatcher::GetClosestPointsFunc getClosestPoints = getWorld()->getCollisionDispatcher()->getGetClosestPointsFunc( a, b );
			getClosestPoints( *rb->getCollidable(), *mHullCollidable, input, collector );	
		}

		// Grow the tolerance until we get a hit.
		input.m_tolerance = input.m_tolerance * 2.0f;
	} while( !collector.hasHit() );

	// Flip the normal of the getClosestPoints() result
	forceDir.setMul4( -1.0f, collector.getHitContact().getNormal() );
	forceDir.normalize3();
	forceDir.zeroElement( 3 );

	// Set force to be direction multiplied by magnitude multiplied by mass.
	hkVector4 force;
	force.setMul4( rb->getMass() * mGravityForce, forceDir );

	// Apply the gravity force.
	//if( EntityType::getEntityType(rb) == EntityType::CHARACTER )
	//{
		/*hkVector4 newUp(forceDir);
		newUp.setNeg4(forceDir);
		newUp.normalize3();

		// Only change gravity if the change isn't negligible
		if( PlanetGravityDemo::m_worldUp.dot3(newUp) < 1e-6f)
		{
			// don't reorient character when it has an invalid rotational axis
			//  (this may happen the first few frames)
			if( PlanetGravityDemo::m_characterRigidBody->getRigidBody()->getRotation().hasValidAxis())
			{
				hkRotation rbRotation; rbRotation.set(PlanetGravityDemo::m_characterRigidBody->getRigidBody()->getRotation());
				hkVector4& oldForward = rbRotation.getColumn(0);
				hkVector4 newRot; newRot.setCross(oldForward, newUp);
 				PlanetGravityDemo::m_characterForward.setCross(newUp, newRot);
 				PlanetGravityDemo::m_characterForward.normalize3();
			}
		}

		PlanetGravityDemo::m_worldUp = newUp;
	}
	else
	{*/
		rb->applyForce( stepInfo.m_deltaTime, force );
	//}
}

}

