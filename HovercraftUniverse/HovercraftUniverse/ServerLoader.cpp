#include "ServerLoader.h"
#include "HoverCraftUniverseWorld.h"
#include "HavokEntityType.h"

#include <Physics/Dynamics/Entity/hkpRigidBody.h>
#include <Common/Base/Math/Matrix/hkTransform.h>

#include "ParseException.h"
#include "EntityDescription.h"

// Phantom for planets
#include "PlanetGravityPhantom.h"

// Phantoms entities
#include "CheckpointPhantom.h"
#include "StartPhantom.h"
#include "BoostPhantom.h"
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

ServerLoader::ServerLoader(HoverCraftUniverseWorld * world, ServerCore * server, char const * path):
	mHovercraftWorld(world), mPath(path), mExternalitem(0), mNodeparameters(0), mEntityparameters(0), mServer(server)
{
}

ServerLoader::~ServerLoader(void)
{
}

void ServerLoader::onSceneUserData(const Ogre::String& userDataReference, const Ogre::String& userData) {
	if ( !userData.empty() ){
		EntityDescription desc("Track","TODO",Ogre::Vector3::ZERO,Ogre::Quaternion::IDENTITY);
		UserDataFactory::getSingleton().parseUserData(userData /*, desc TODO PJ, This function only requires 1 argument */);
	}
}

void ServerLoader::onNode( OgreMax::Types::NodeParameters& nodeparameters, std::vector<OgreMax::Types::NodeAnimation> * animation, const OgreMax::Types::NodeParameters* parent) {
	mNodeparameters = &nodeparameters;
	if ( !nodeparameters.extraData.isNull() && !nodeparameters.extraData->userData.empty() ){
		EntityDescription desc(nodeparameters.name,"TODO",nodeparameters.position,nodeparameters.orientation);
		UserDataFactory::getSingleton().parseUserData(nodeparameters.extraData->userData /*, desc TODO PJ, This function only requires 1 argument */);
	}
	mNodeparameters = 0;
}

void ServerLoader::onEntity( OgreMax::Types::EntityParameters& entityparameters, const OgreMax::Types::Attachable * parent ) {
	mEntityparameters = &entityparameters;
	if ( !entityparameters.extraData.isNull() && !entityparameters.extraData->userData.empty() ){
		EntityDescription desc(entityparameters.name,"TODO",mNodeparameters->position,mNodeparameters->orientation);
		UserDataFactory::getSingleton().parseUserData(entityparameters.extraData->userData /*, desc TODO PJ, This function only requires 1 argument */);
	}
	mEntityparameters = 0;
}

void ServerLoader::onExternal( OgreMax::Types::ExternalItem& externalitem){
	mExternalitem = &externalitem;
	if ( !externalitem.userData.empty() ){
		EntityDescription desc(externalitem.name,"TODO",externalitem.position,externalitem.rotation);
		UserDataFactory::getSingleton().parseUserData(externalitem.userData /*, desc TODO PJ does not compile */);
	}
	mExternalitem = 0;
}

void ServerLoader::FinishedLoad( bool success ){
	if (mHovercraftWorld->mPhysicsWorld != HK_NULL )
		mHovercraftWorld->mPhysicsWorld->unmarkForWrite();
}

void ServerLoader::onTrack( Ogre::SharedPtr<Track> track ) {

	Ogre::String filename = Ogre::String(mPath) + track->getPhysicsFileName();

	const char * physicsfile = filename.c_str();
	if ( mHovercraftWorld->load(physicsfile) ){
		//load our physics file
		mHovercraftWorld->mPhysicsWorld->markForWrite();		
	}
	else {
		//loading failed
		throw ParseException();
	}

	hkVector4 zero;
	mHovercraftWorld->mStartPositions.setSize(track->getMaximumPlayers(),zero);
}

void ServerLoader::onAsteroid( Ogre::SharedPtr<Asteroid> asteroid ) {

	if ( mEntityparameters == 0 ){
		//THROW EXCEPTION (this should be an enitity)
		throw ParseException();
	}
	
	//Get the name of the asteroid
	const char * asteroidname = mEntityparameters->name.c_str();

	// Find the planet
	hkpRigidBody* planetRigidBody = mHovercraftWorld->mPhysicsData->findRigidBodyByName( asteroidname );

	if ( planetRigidBody == HK_NULL ) {
		//THROW EXCEPTION (no sush name found)
		throw ParseException();
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
}

void ServerLoader::onStart( Ogre::SharedPtr<Start> start ) {
	if ( !mExternalitem ){
		//THROW EXCEPTION (this should be an external item)
		throw ParseException();
	}

	//Create a phantom that handles this
	hkAabb aabb;

	setBox(aabb, mExternalitem->position, mExternalitem->rotation, mExternalitem->scale );

	StartPhantom * phantom = new StartPhantom(	aabb );	
	mHovercraftWorld->mPhysicsWorld->addPhantom( phantom );
	phantom->removeReference();
}

void ServerLoader::onStartPosition( Ogre::SharedPtr<StartPosition> startposition ) {
	if ( !mExternalitem ){
		//THROW EXCEPTION (this should be an external item)
		throw ParseException();
	}
	
	hkVector4 position(mExternalitem->position.x, mExternalitem->position.y, mExternalitem->position.z);
	int pos = startposition->getPlayerNumber();
	mHovercraftWorld->mStartPositions[pos] = position;	
}

void ServerLoader::onCheckPoint( Ogre::SharedPtr<CheckPoint> checkpoint ) {
	if ( !mExternalitem ){
		//THROW EXCEPTION (this should be an external item)
		throw ParseException();
	}

	//Create a phantom that handles this
	hkAabb aabb;

	setBox(aabb, mExternalitem->position, mExternalitem->rotation, mExternalitem->scale );

	hkString name(checkpoint->getName().c_str());
	hkInt32 number = checkpoint->getNumber();

	CheckpointPhantom * checkpointphantom = new CheckpointPhantom(	aabb, name, number);	
	mHovercraftWorld->mPhysicsWorld->addPhantom( checkpointphantom );
	checkpointphantom->removeReference();

}

void ServerLoader::onFinish( Ogre::SharedPtr<Finish> finish ) {
	if ( !mExternalitem ){
		//THROW EXCEPTION (this should be an external item)
		throw ParseException();
	}	

	//Create a phantom that handles this
	hkAabb aabb;

	setBox(aabb, mExternalitem->position, mExternalitem->rotation, mExternalitem->scale );

	FinishPhantom * phantom = new FinishPhantom( aabb );
	mHovercraftWorld->mPhysicsWorld->addPhantom( phantom );
	phantom->removeReference();
}

void ServerLoader::onHoverCraft( Ogre::SharedPtr<Hovercraft> hovercraft ) {
	//TODO add hovercraft	
}

void ServerLoader::onPortal( Ogre::SharedPtr<Portal> portal ) {
	if ( !mExternalitem ){
		//THROW EXCEPTION (this should be an external item)
		throw ParseException();
	}	

	//Create a phantom that handles this
	hkAabb aabb;

	setBox(aabb, mExternalitem->position, mExternalitem->rotation, mExternalitem->scale );

	PortalPhantom * phantom = new PortalPhantom( aabb );
	mHovercraftWorld->mPhysicsWorld->addPhantom( phantom );
	phantom->removeReference();
}

void ServerLoader::onBoost( Ogre::SharedPtr<Boost> boost ) {
	if ( !mExternalitem ){
		//THROW EXCEPTION (this should be an external item)
		throw ParseException();
	}

	//Create a phantom that handles this
	hkAabb aabb;

	setBox(aabb, mExternalitem->position, mExternalitem->rotation, mExternalitem->scale );

	hkReal boostvalue = boost->getBoost();

	BoostPhantom * phantom = new BoostPhantom( aabb, boostvalue );	
	mHovercraftWorld->mPhysicsWorld->addPhantom( phantom );
	phantom->removeReference();
}

void ServerLoader::onPowerupSpawn( Ogre::SharedPtr<PowerupSpawn> powerupspawn ) {
	if ( !mExternalitem ){
		//THROW EXCEPTION (this should be an external item)
		throw ParseException();
	}

	hkVector4 position(mExternalitem->position.x, mExternalitem->position.y, mExternalitem->position.z);

	if ( mHovercraftWorld->mPowerupPositions.getSize() == mHovercraftWorld->mPowerupPositions.getCapacity() ){
		mHovercraftWorld->mPowerupPositions.expandBy(32);
	}
	
	mHovercraftWorld->mPowerupPositions.pushBack(position);
}

void ServerLoader::onResetSpawn( Ogre::SharedPtr<ResetSpawn> spawn ) {
	if ( !mExternalitem ){
		//THROW EXCEPTION (this should be an external item)
		throw ParseException();
	}

	hkVector4 position(mExternalitem->position.x, mExternalitem->position.y, mExternalitem->position.z);

	if ( mHovercraftWorld->mResetPositions.getSize() == mHovercraftWorld->mResetPositions.getCapacity() ){
		mHovercraftWorld->mResetPositions.expandBy(32);
	}
	
	mHovercraftWorld->mResetPositions.pushBack(position);
}


}
