#include "CustomOgreMaxScene.h"
#include "Exception.h"
#include "EntityDescription.h"

#include "GameEntities.h"

//Lobby
#include "Lobby.h"
#include "NetworkIDManager.h"
#include "EntityManager.h"

// Physics
#include "Havok.h"
#include <Physics/Dynamics/Entity/hkpRigidBody.h>
#include <Common/Base/Math/Matrix/hkTransform.h>
#include "HoverCraftUniverseWorld.h"
#include "PlanetGravityPhantom.h"
#include "HavokEntityType.h"
#include "CheckpointPhantom.h"
#include "StartPhantom.h"
#include "SpeedBoostPhantom.h"
#include "FinishPhantom.h"
#include "PortalPhantom.h"
#include "PowerupPhantom.h"

namespace {

	void setBox ( hkAabb& aabb, const Ogre::Vector3& position, const Ogre::Quaternion& rotation, const Ogre::Vector3& scale  ){
		hkVector4 t(position.x, position.y, position.z);
		hkQuaternion q(rotation.x, rotation.y, rotation.z, rotation.w);
		
		hkTransform tr(q,t);
		
		hkVector4 pos;
		
		pos.set(scale.x * 5, scale.y * 5, scale.z * 5);
		aabb.m_max.setTransformedPos(tr,pos);

		pos.set(scale.x * -5, scale.y * -5, scale.z * -5);
		aabb.m_min.setTransformedPos(tr,pos);
	}
}

namespace HovUni {

ServerLoader::ServerLoader(): mHovercraftWorld(0)
{
}

ServerLoader::~ServerLoader(void)
{
}

void ServerLoader::load ( const Ogre::String& filename ){
	Havok::start(filename.c_str(),this);
}

void ServerLoader::onSceneUserData(const Ogre::String& userDataReference, const Ogre::String& userData) {
	if ( !userData.empty() ){
		EntityDescription desc("Track",Ogre::Vector3::ZERO,Ogre::Quaternion::IDENTITY);
		UserDataFactory::getSingleton().parseUserData(userData , desc);
	}
}

void ServerLoader::onExternal( OgreMax::Types::ExternalItem& externalitem){
	mExternalitem = &externalitem;
	if ( !externalitem.userData.empty() ){
		EntityDescription desc(externalitem.name,externalitem.position,externalitem.rotation);
		UserDataFactory::getSingleton().parseUserData(externalitem.userData , desc );
	}
	mExternalitem = 0;
}

void ServerLoader::FinishedLoad( bool success ){

	if ( success ){
		//add players
		const Lobby::playermap& map = mLobby->getPlayers();

		int j = 0;
		for ( Lobby::playermap::const_iterator i = map.begin(); i != map.end(); i++ ){

			Ogre::String name = i->second->getPlayerName().c_str() + Ogre::String("_") + Ogre::StringConverter::toString(j);
			Ogre::Vector3 position(mHovercraftWorld->mStartPositions[j](0),mHovercraftWorld->mStartPositions[j](1),mHovercraftWorld->mStartPositions[j](2));

			Hovercraft * craft = new Hovercraft(name,false,position,Ogre::Quaternion::IDENTITY,"TODO",1.0f/60.0f);
			
			mHovercraftWorld->addCharacter(craft,j);
			
			craft->getNetworkNode()->setOwner(i->first, true);			
			EntityManager::getServerSingletonPtr()->registerEntity(craft);
			craft->networkRegister(NetworkIDManager::getServerSingletonPtr(), Hovercraft::getClassName(),true);

			

			j++;
		}	
	
	}


	if (mHovercraftWorld->mPhysicsWorld != HK_NULL )
		mHovercraftWorld->mPhysicsWorld->unmarkForWrite();
}

void ServerLoader::onTrack( Track * track ) {

	//TODO USE OGRE RESOURCES

	Ogre::String filename = ".\\levels\\" + track->getPhysicsFileName();

	mHovercraftWorld = Havok::getSingletonPtr();

	const char * physicsfile = filename.c_str();
	if ( mHovercraftWorld->load(physicsfile) ){
		//load our physics file
		mHovercraftWorld->mPhysicsWorld->markForWrite();		
	}
	else {
		//loading failed
		THROW(ParseException, "Could not load our physics file.");
	}

	hkVector4 zero;
	mHovercraftWorld->mStartPositions.setSize(track->getMaximumPlayers(),zero);

	delete track;
}

void ServerLoader::onAsteroid( Asteroid * asteroid ) {

	if ( mExternalitem == 0 ){
		THROW(ParseException, "This should be an external item.");
	}
	
	//Get the entity name of the asteroid
	Ogre::String entityname = asteroid->getOgreEntity();

	// Find the planet
	hkpRigidBody* planetRigidBody = mHovercraftWorld->mPhysicsData->findRigidBodyByName( entityname.c_str() );

	if ( planetRigidBody == HK_NULL ) {
		THROW(ParseException, "No such name found.");
	}

	//Set that it is a planet
	HavokEntityType::setEntityType(planetRigidBody,HavokEntityType::PLANET);
	
	//add gravity field PULL
	{
		hkAabb currentAabb;
		const hkpCollidable* hullCollidable = HK_NULL;
		planetRigidBody->getCollidable()->getShape()->getAabb( planetRigidBody->getTransform(), 0.0f, currentAabb );

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
		PlanetGravityPhantom* gravityphantom = new PlanetGravityPhantom( planetRigidBody, currentAabb, hullCollidable );
		mHovercraftWorld->mPhysicsWorld->addPhantom( gravityphantom );
		gravityphantom->removeReference();
	}

	//add to entity manager
	EntityManager::getServerSingletonPtr()->registerEntity(asteroid);

	
	//network register asteroid
	asteroid->networkRegister(NetworkIDManager::getServerSingletonPtr(), Asteroid::getClassName(),true);
}

void ServerLoader::onStart( Start * start ) {
	if ( !mExternalitem ){
		THROW(ParseException, "This should be an external item.");
	}

	//Create a phantom that handles this
	hkAabb aabb;
	setBox(aabb, mExternalitem->position, mExternalitem->rotation, mExternalitem->scale );
	StartPhantom * phantom = new StartPhantom(aabb, start );	
	mHovercraftWorld->mPhysicsWorld->addPhantom( phantom );
	phantom->removeReference();

	//add to entity manager
	EntityManager::getServerSingletonPtr()->registerEntity(start);

	//network register asteroid
	start->networkRegister(NetworkIDManager::getServerSingletonPtr(), Start::getClassName(),true);
}

void ServerLoader::onStartPosition( StartPosition * startposition ) {
	if ( !mExternalitem ){
		THROW(ParseException, "This should be an external item.");
	}
	
	//add start position
	hkVector4 position(mExternalitem->position.x, mExternalitem->position.y, mExternalitem->position.z);
	int pos = startposition->getPlayerNumber();
	mHovercraftWorld->mStartPositions[pos] = position;	

	//add to entity manager
	EntityManager::getServerSingletonPtr()->registerEntity(startposition);

	//network register asteroid
	startposition->networkRegister(NetworkIDManager::getServerSingletonPtr(), StartPosition::getClassName(),true);
}

void ServerLoader::onCheckPoint( CheckPoint * checkpoint ) {
	if ( !mExternalitem ){
		THROW(ParseException, "This should be an external item.");
	}

	//Create a phantom that handles this
	hkAabb aabb;
	setBox(aabb, mExternalitem->position, mExternalitem->rotation, mExternalitem->scale );
	CheckpointPhantom * checkpointphantom = new CheckpointPhantom(	aabb, checkpoint);	
	mHovercraftWorld->mPhysicsWorld->addPhantom( checkpointphantom );
	checkpointphantom->removeReference();

	//add to entity manager
	EntityManager::getServerSingletonPtr()->registerEntity(checkpoint);

	//network register asteroid
	checkpoint->networkRegister(NetworkIDManager::getServerSingletonPtr(), CheckPoint::getClassName(),true);
}

void ServerLoader::onFinish( Finish * finish ) {
	if ( !mExternalitem ){
		THROW(ParseException, "This should be an external item.");
	}

	//Create a phantom that handles this
	hkAabb aabb;
	setBox(aabb, mExternalitem->position, mExternalitem->rotation, mExternalitem->scale );
	FinishPhantom * phantom = new FinishPhantom( aabb, finish );
	mHovercraftWorld->mPhysicsWorld->addPhantom( phantom );
	phantom->removeReference();

	//add to entity manager
	EntityManager::getServerSingletonPtr()->registerEntity(finish);
	
	//network register asteroid
	finish->networkRegister(NetworkIDManager::getServerSingletonPtr(), Finish::getClassName(),true);
}

void ServerLoader::onHoverCraft( Hovercraft * hovercraft ) {
	//TODO add hovercraft	

	delete hovercraft;
}

void ServerLoader::onPortal( Portal * portal ) {
	if ( !mExternalitem ){
		THROW(ParseException, "This should be an external item.");
	}	

	//Create a phantom that handles this
	hkAabb aabb;
	setBox(aabb, mExternalitem->position, mExternalitem->rotation, mExternalitem->scale );
	PortalPhantom * phantom = new PortalPhantom( aabb, portal );
	mHovercraftWorld->mPhysicsWorld->addPhantom( phantom );
	phantom->removeReference();

	//add to entity manager
	EntityManager::getServerSingletonPtr()->registerEntity(portal);
	
	//network register asteroid
	portal->networkRegister(NetworkIDManager::getServerSingletonPtr(), Portal::getClassName(),true);	
}

void ServerLoader::onBoost( SpeedBoost * boost ) {
	if ( !mExternalitem ){
		THROW(ParseException, "This should be an external item.");
	}

	//Create a phantom that handles this
	hkAabb aabb;
	setBox(aabb, mExternalitem->position, mExternalitem->rotation, mExternalitem->scale );
	SpeedBoostPhantom * phantom = new SpeedBoostPhantom( aabb, boost );	
	mHovercraftWorld->mPhysicsWorld->addPhantom( phantom );
	phantom->removeReference();

	//add to entity manager
	EntityManager::getServerSingletonPtr()->registerEntity(boost);
	
	//network register asteroid
	boost->networkRegister(NetworkIDManager::getServerSingletonPtr(), SpeedBoost::getClassName(),true);	
}

void ServerLoader::onPowerupSpawn( PowerupSpawn * powerupspawn ) {
	if ( !mExternalitem ){
		THROW(ParseException, "This should be an external item.");
	}

	//add powerup spawn
	hkVector4 position(mExternalitem->position.x, mExternalitem->position.y, mExternalitem->position.z);
	if ( mHovercraftWorld->mPowerupPositions.getSize() == mHovercraftWorld->mPowerupPositions.getCapacity() ){
		mHovercraftWorld->mPowerupPositions.expandBy(32);
	}	
	mHovercraftWorld->mPowerupPositions.pushBack(position);

	//add to entity manager
	EntityManager::getServerSingletonPtr()->registerEntity(powerupspawn);

	
	//network register asteroid
	powerupspawn->networkRegister(NetworkIDManager::getServerSingletonPtr(), PowerupSpawn::getClassName(),true);	
}

void ServerLoader::onResetSpawn( ResetSpawn * spawn ) {
	if ( !mExternalitem ){
		THROW(ParseException, "This should be an external item.");
	}

	//add reset spawn
	hkVector4 position(mExternalitem->position.x, mExternalitem->position.y, mExternalitem->position.z);
	if ( mHovercraftWorld->mResetPositions.getSize() == mHovercraftWorld->mResetPositions.getCapacity() ){
		mHovercraftWorld->mResetPositions.expandBy(32);
	}	
	mHovercraftWorld->mResetPositions.pushBack(position);

	//add to entity manager
	EntityManager::getServerSingletonPtr()->registerEntity(spawn);
	
	//network register asteroid
	spawn->networkRegister(NetworkIDManager::getServerSingletonPtr(), ResetSpawn::getClassName(),true);	
}


}
