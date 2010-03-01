#include "HoverCraftUniverseWorld.h"

#include "EntityType.h"
#include "GravityPhantom.h"
#include "PhantomTrackAction.h"
#include "PushGravityPhantom.h"


#include <Physics/Collide/Filter/Group/hkpGroupFilterSetup.h>

namespace HovUni {

HoverCraftUniverseWorld * HoverCraftUniverseWorld::world = 0;

HoverCraftUniverseWorld::HoverCraftUniverseWorld(void)
{
	world = this;
}

HoverCraftUniverseWorld::~HoverCraftUniverseWorld(void)
{
}

void HoverCraftUniverseWorld::load ( const char * filename ){
	//load the world	
	AbstractHavocWorld::load(filename);

	//do our post processing step
	mPhysicsWorld->markForWrite();

	mPhysicsWorld->setGravity( hkVector4::getZero() );

	// Set up the collision filter
	{
		hkpGroupFilter* filter = new hkpGroupFilter();
		filter->disableCollisionsBetween(1, 1);
		mPhysicsWorld->setCollisionFilter(filter);
		filter->removeReference();
	}

	// Go through all loaded rigid bodies
	for( int i = 0; i < mPhysicsData->getPhysicsSystems().getSize(); i++ )
	{
		const hkArray<hkpRigidBody*>& bodies = mPhysicsData->getPhysicsSystems()[i]->getRigidBodies();
		for( int j = 0; j < bodies.getSize(); j++ )
		{
			hkString rbName( bodies[j]->getName() );

			// If the rb is a planet (name is "planet*")
			if( rbName.beginsWith( "planet" ) )
			{
				// If the body is a representation of a gravitational field (name: "*GravField"),
				//  remove it from the simulation.
				if( rbName.endsWith( "GravField" ) )
				{
					mPhysicsWorld->removeEntity( bodies[j] );
				}
				// Otherwise, it's actually a planet.
				else
				{
					hkAabb currentAabb;
					const hkpCollidable* hullCollidable = HK_NULL;

					// Find the planet's gravity field
					hkpRigidBody* planetRigidBody = bodies[j];

					//Set that it is a planet
					EntityType::setEntityType(planetRigidBody,EntityType::PLANET);

					hkString gravFieldRbName;
					gravFieldRbName.printf( "%sGravField", rbName.cString() );
					hkpRigidBody* gravFieldRigidBody = mPhysicsData->findRigidBodyByName( gravFieldRbName.cString() );

					// If there's a GravField rigid body, then grab its collidable to be used for gravity calculation.
					if( gravFieldRigidBody )
					{
						hullCollidable = gravFieldRigidBody->getCollidable();
						gravFieldRigidBody->getCollidable()->getShape()->getAabb( gravFieldRigidBody->getTransform(), 0.0f, currentAabb );
					}
					else
					{
						planetRigidBody->getCollidable()->getShape()->getAabb( planetRigidBody->getTransform(), 0.0f, currentAabb );
					}

					//add gravity field PULL
					{
						// Scale up the planet's gravity field's AABB so it goes beyond the planet
						hkVector4 extents;
						extents.setSub4( currentAabb.m_max, currentAabb.m_min );
						hkInt32 majorAxis = extents.getMajorAxis();
						hkReal maxExtent = extents( majorAxis );
						maxExtent *= 0.4f;

						// Scale the AABB's extents
						hkVector4 extension;
						extension.setAll( maxExtent );
						currentAabb.m_max.add4( extension );
						currentAabb.m_min.sub4( extension );

						// Attach a gravity phantom to the planet so it can catch objects which come close
						GravityPhantom* gravityAabbPhantom = new GravityPhantom( planetRigidBody, currentAabb, hullCollidable );
						mPhysicsWorld->addPhantom( gravityAabbPhantom );
						gravityAabbPhantom->removeReference();

						// Add a tracking action to the phantom so it follows the planet. This allows support for non-fixed motion type planets
						if (planetRigidBody->getMotion()->getType() != hkpMotion::MOTION_FIXED)
						{
							PhantomTrackAction* trackAction = new PhantomTrackAction( planetRigidBody, gravityAabbPhantom );
							mPhysicsWorld->addAction( trackAction );
							trackAction->removeReference();
						}
					}
					//add gravity field PUSH
					{
						// Scale up the planet's gravity field's AABB so it goes beyond the planet
						hkVector4 extents;
						extents.setSub4( currentAabb.m_max, currentAabb.m_min );
						hkInt32 majorAxis = extents.getMajorAxis();
						hkReal maxExtent = extents( majorAxis );
						maxExtent *= 0.1f;

						// Scale the AABB's extents
						hkVector4 extension;
						extension.setAll( maxExtent );
						currentAabb.m_max.add4( extension );
						currentAabb.m_min.sub4( extension );

						// Attach a gravity phantom to the planet so it can catch objects which come close
						PushGravityPhantom* gravityAabbPhantom = new PushGravityPhantom( planetRigidBody, currentAabb, hullCollidable );
						mPhysicsWorld->addPhantom( gravityAabbPhantom );
						gravityAabbPhantom->removeReference();

						// Add a tracking action to the phantom so it follows the planet. This allows support for non-fixed motion type planets
						if (planetRigidBody->getMotion()->getType() != hkpMotion::MOTION_FIXED)
						{
							PhantomTrackAction* trackAction = new PhantomTrackAction( planetRigidBody, gravityAabbPhantom );
							mPhysicsWorld->addAction( trackAction );
							trackAction->removeReference();
						}
					}
				}
			}
			else if ( rbName.beginsWith( "StartPos" ) ){
				//keep the position and orientation
				hkVector4 pos = bodies[j]->getPosition();
				hkQuaternion rot = bodies[j]->getRotation();

				//remove it from simulation
				mPhysicsWorld->removeEntity( bodies[j] );
			}
			if( rbName.endsWith( "HOVER" ) ) {
				EntityType::setEntityType(bodies[j],EntityType::CHARACTER);
			}

			// Update collision filter so that needless CollColl3 agents are not created.
			// For example, turrets  and geometry marked as "static" (such as the swing)
			//  should never collide with a planet, nor each other.
			if(  ( rbName.beginsWith( "planet" ) && !rbName.endsWith( "GravField" ) ) )
			{
				bodies[j]->setCollisionFilterInfo( hkpGroupFilter::calcFilterInfo( 1 ) );

				// Destroy or create agents (according to new quality type). This also removes Toi events.
				mPhysicsWorld->updateCollisionFilterOnEntity(bodies[j], HK_UPDATE_FILTER_ON_ENTITY_FULL_CHECK, HK_UPDATE_COLLECTION_FILTER_PROCESS_SHAPE_COLLECTIONS);
			}
		}
	}

	mPhysicsWorld->unmarkForWrite();
}

}
