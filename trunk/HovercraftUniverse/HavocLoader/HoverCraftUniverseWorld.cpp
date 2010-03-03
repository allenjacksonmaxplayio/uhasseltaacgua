#include "HoverCraftUniverseWorld.h"

#include "EntityType.h"
#include "PhantomTrackAction.h"
#include "PullGravityPhantom.h"
#include "PushGravityPhantom.h"

#include <Physics/Collide/Filter/Group/hkpGroupFilterSetup.h>

#include "CustomOgreMaxSceneCallback.h"
#include "UserDataCallback.h"

namespace HovUni {

class CustomLoader : public UserDataCallback, public CustomOgreMaxSceneCallback {
public:
	CustomLoader() {
	}

	
	virtual void onSceneFile( const Ogre::String& fileName, Ogre::String& resourceGroupName){
	}
	
	virtual void onResourceLocation ( const Ogre::String& name, const Ogre::String& type, bool recursive) {
	}

	virtual void StartedLoad(){
		//TODO notify clients??
	}

	virtual void onExternalUserData( OgreMax::Types::ExternalUserData& externalud) {
	}

	virtual void onSceneUserData(const Ogre::String& userDataReference, const Ogre::String& userData) {
		//TODO parse Track usedata
	}

	virtual void onExternal( OgreMax::Types::ExternalItem& externalitem){
		//HERE WE NEED TO WORK
		//UserDataFactory::getInstance().parse(externalitem)
	}

	virtual void FinishedLoad( bool success ){
		//TODO notify clients??
	}

	virtual void UpdatedLoadProgress( Ogre::Real progress ){
		//TODO notify clients??
	}

	//Scene info: nobody cares about this
	virtual void onSceneData( const OgreMax::Version& formatVersion, const OgreMax::Version& minOgreVersion, const OgreMax::Version& ogreMaxVersion, const Ogre::String& author, const Ogre::String& application, OgreMax::Types::UpAxis upAxis, Ogre::Real unitsPerMeter, const Ogre::String& unitType) {}

	//Sky systems: nobody cares about this

	virtual void onSkyBox( OgreMax::Types::SkyBoxParameters& skyBoxParameters, std::vector<OgreMax::Types::NodeAnimation> * animation ) {
	}

	virtual void onSkyDome( OgreMax::Types::SkyDomeParameters& skyDomeParameters, std::vector<OgreMax::Types::NodeAnimation> * animation) {
	}

	virtual void onSkyPlane( OgreMax::Types::SkyPlaneParameters& skyPlaneParameters, std::vector<OgreMax::Types::NodeAnimation> * animation) {
	}

	//Enviroment: nobody cares about this

	virtual void onClipping( Ogre::Real environmentNear, Ogre::Real environmentFar){
	}

	virtual void onFog ( OgreMax::Types::FogParameters& fog ){
	}

	virtual void onAmbientColour( const Ogre::ColourValue& colour ){
	}

	virtual void onShadowProperties( OgreMax::Types::ShadowParameters& parameter ){
	}

	virtual void onBackgroundColour( const Ogre::ColourValue& colour ){
	}

	//Nodes

	virtual void onRootNode ( const Ogre::Vector3& position, const Ogre::Quaternion& rotation, const Ogre::Vector3& scale ) {
	}

	virtual void onNode( OgreMax::Types::NodeParameters& nodeparameters, std::vector<OgreMax::Types::NodeAnimation> * animation, const OgreMax::Types::NodeParameters* parent) {
	}

	//Movables

	virtual void onEntity( OgreMax::Types::EntityParameters& entityparameters, const OgreMax::Types::Attachable * parent ) {
		//TODO ??
	}

	virtual void onLight( OgreMax::Types::LightParameters& light, const OgreMax::Types::Attachable * parent) {}
        
	virtual void onCamera(OgreMax::Types::CameraParameters& params, const OgreMax::Types::Attachable * parent ) {}

	virtual void onBillboardSet( OgreMax::Types::BillboardSetParameters& bilboardsetparameters, std::vector<OgreMax::Types::Billboard>& billboardset, std::vector<OgreMax::Types::CustomParameter>& customParameters, const OgreMax::Types::Attachable * parent ) {}

	virtual void onParticleSystem( OgreMax::Types::ParticleSystemParameters& particleSystem, const OgreMax::Types::Attachable * parent) {}

	virtual void onPlane( OgreMax::Types::PlaneParameters planeparameters, const OgreMax::Types::Attachable * parent) {}

	//Custom objects

	virtual void onAsteroid( Asteroid * asteroid ) {
		//TODO add asteroid
	};

	virtual void onStart( Start * start ) {
		//TODO add start
	};

	virtual void onStartPosition( StartPosition * startposition ) {
		//TODO add startpos	
	}

	virtual void onCheckPoint( CheckPoint * checkpoint ) {
		//TODO add checkpoint	
	};

	virtual void onFinish( Finish * finish ) {
		//TODO add finish	
	};

	virtual void onHoverCraft( Hovercraft * hovercraft ) {
		//TODO add hovercraft	
	};

	virtual void onTrack( Track * track ) {
		//TODO load havoc file of track	
	};

	virtual void onPortal( Portal * portal ) {
		//TODO create havoc portal	
	};

	virtual void onBoost( Boost * boost ) {
		//TODO create havoc boost
	};

	virtual void onPowerupSpawn( PowerupSpawn * powerupspawn ) {
		//TODO create havoc powerup spawn	
	};

	virtual void onResetSpawn( ResetSpawn * spawn ) {
		//TODO create havoc reset spawn
	};
};


HoverCraftUniverseWorld::HoverCraftUniverseWorld(hkReal timestep):
	AbstractHavocWorld(timestep)
{
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
						PullGravityPhantom* gravityAabbPhantom = new PullGravityPhantom( planetRigidBody, currentAabb, hullCollidable );
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
/*
					//add gravity field PUSH
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
					}*/
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
