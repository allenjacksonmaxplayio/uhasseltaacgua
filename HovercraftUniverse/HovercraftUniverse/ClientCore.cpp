#include "ClientCore.h"
#include "Application.h"
#include "ClientLoader.h"
#include "DummyHovercraft.h"
#include "DummyHovercraftPlayerController.h"
#include "DummyHovercraftAIController.h"
#include "DummyHovercraftRepresentation.h"
#include "EntityRegister.h"

#include "HovercraftPlayerController.h"
#include "HovercraftAIController.h"

#include "AsteroidRepresentation.h"
#include "BoostRepresentation.h"
#include "CheckPointRepresentation.h"
#include "FinishRepresentation.h"
#include "HovercraftRepresentation.h"
#include "PortalRepresentation.h"
#include "StartRepresentation.h"
#include "TrackRepresentation.h"

#include "Start.h"
#include "Finish.h"
#include "Asteroid.h"
#include "Hovercraft.h"
#include "CheckPoint.h"
#include "StartPosition.h"
#include "SpeedBoost.h"
#include "Portal.h"
#include "PowerupSpawn.h"
#include "ResetSpawn.h"

namespace HovUni {

ClientCore::ClientCore(const char* name, unsigned int port) : NetworkClient(name, port), mEntityManager(0), mIDManager(0), mLobby(0) {
	initialize();
}

ClientCore::ClientCore() : NetworkClient(2376), mEntityManager(0), mIDManager(0), mLobby(0) {
	initialize();
}

ClientCore::~ClientCore() {

}

void ClientCore::initialize() {
	// Create and store entity manager
	mEntityManager = EntityManager::getClientSingletonPtr();
	mIDManager = new NetworkIDManager(this);
	EntityRegister::registerAll(*mIDManager);
	ZCom_setUpstreamLimit(0, 0);
}

void ClientCore::process() {
	NetworkClient::process();
}

void ClientCore::ZCom_cbConnectResult(ZCom_ConnID id, eZCom_ConnectResult result, ZCom_BitStream& reply) {
	if (result == eZCom_ConnAccepted) {
		// Connection accepted, so request zoid level
		ZCom_requestDownstreamLimit(id, 60, 600);
		ZCom_requestZoidMode(id, 1);
	} else {
		// Connection failed
		return;
	}
}

void ClientCore::ZCom_cbConnectionClosed(ZCom_ConnID id, eZCom_CloseReason reason, ZCom_BitStream& reasondata) {
	// Connection closed
}

void ClientCore::ZCom_cbDataReceived(ZCom_ConnID id, ZCom_BitStream& data) {
	// Data received
}  

void ClientCore::ZCom_cbZoidResult(ZCom_ConnID id, eZCom_ZoidResult result, zU8 new_level, ZCom_BitStream& reason) {
	if (result == eZCom_ZoidEnabled) {
		// Requested zoid level was confirmed
	} else {
		// Requested zoid level denied
	}
}

void ClientCore::ZCom_cbNodeRequest_Dynamic(ZCom_ConnID id, ZCom_ClassID requested_class, ZCom_BitStream* announcedata, eZCom_NodeRole role, ZCom_NodeID net_id) {
	// Receive and create the entity
	Ogre::String name("");
	if (requested_class == mIDManager->getID(Lobby::getClassName())) {
		// Lobby received (upon connect)
		mLobby = new Lobby(0);
		mLobby->networkRegister(requested_class, this);
		Application::msPreparationLoader->registerLoader(mLobby->getTrackFilename());
	} else if ( requested_class == mIDManager->getID(Asteroid::getClassName()) ){
		name = announcedata->getString();
		Ogre::String entity(announcedata->getString());
		float processinterval = announcedata->getFloat(4);

		float x = announcedata->getFloat(4);
		float y = announcedata->getFloat(4);
		float z = announcedata->getFloat(4);

		float rx = announcedata->getFloat(4);
		float ry = announcedata->getFloat(4);
		float rz = announcedata->getFloat(4);
		float rw = announcedata->getFloat(4);

		Asteroid * ent = new Asteroid(name,Ogre::Vector3(x,y,z),Ogre::Quaternion(rx,ry,rz,rw),entity,processinterval);
		ent->networkRegister(requested_class,this);

		mEntityManager->registerEntity(ent);
	} else if ( requested_class == mIDManager->getID(CheckPoint::getClassName()) ){
		name = announcedata->getString();
		Ogre::String entity(announcedata->getString());
		float processinterval = announcedata->getFloat(4);

		float x = announcedata->getFloat(4);
		float y = announcedata->getFloat(4);
		float z = announcedata->getFloat(4);

		float rx = announcedata->getFloat(4);
		float ry = announcedata->getFloat(4);
		float rz = announcedata->getFloat(4);
		float rw = announcedata->getFloat(4);

		CheckPoint * ent = new CheckPoint(name,Ogre::Vector3(x,y,z),Ogre::Quaternion(rx,ry,rz,rw),entity,processinterval);
		ent->networkRegister(requested_class,this);

		mEntityManager->registerEntity(ent);
	} else if ( requested_class == mIDManager->getID(Start::getClassName()) ){
		name = announcedata->getString();
		Ogre::String entity(announcedata->getString());
		float processinterval = announcedata->getFloat(4);

		float x = announcedata->getFloat(4);
		float y = announcedata->getFloat(4);
		float z = announcedata->getFloat(4);

		float rx = announcedata->getFloat(4);
		float ry = announcedata->getFloat(4);
		float rz = announcedata->getFloat(4);
		float rw = announcedata->getFloat(4);

		Start * ent = new Start(name,Ogre::Vector3(x,y,z),Ogre::Quaternion(rx,ry,rz,rw),entity,processinterval);
		ent->networkRegister(requested_class,this);

		mEntityManager->registerEntity(ent);
	} else if ( requested_class == mIDManager->getID(StartPosition::getClassName()) ){
		name = announcedata->getString();
		Ogre::String entity(announcedata->getString());
		float processinterval = announcedata->getFloat(4);

		float x = announcedata->getFloat(4);
		float y = announcedata->getFloat(4);
		float z = announcedata->getFloat(4);

		float rx = announcedata->getFloat(4);
		float ry = announcedata->getFloat(4);
		float rz = announcedata->getFloat(4);
		float rw = announcedata->getFloat(4);

		StartPosition * ent = new StartPosition(name,Ogre::Vector3(x,y,z),Ogre::Quaternion(rx,ry,rz,rw),processinterval);
		ent->networkRegister(requested_class,this);

		mEntityManager->registerEntity(ent);
	} else if ( requested_class == mIDManager->getID(Finish::getClassName()) ){
		name = announcedata->getString();
		Ogre::String entity(announcedata->getString());
		float processinterval = announcedata->getFloat(4);

		float x = announcedata->getFloat(4);
		float y = announcedata->getFloat(4);
		float z = announcedata->getFloat(4);

		float rx = announcedata->getFloat(4);
		float ry = announcedata->getFloat(4);
		float rz = announcedata->getFloat(4);
		float rw = announcedata->getFloat(4);

		Finish * ent = new Finish(name,Ogre::Vector3(x,y,z),Ogre::Quaternion(rx,ry,rz,rw),entity,processinterval);
		ent->networkRegister(requested_class,this);	

		mEntityManager->registerEntity(ent);
	} else if ( requested_class == mIDManager->getID(ResetSpawn::getClassName()) ){
		name = announcedata->getString();
		Ogre::String entity(announcedata->getString());
		float processinterval = announcedata->getFloat(4);

		float x = announcedata->getFloat(4);
		float y = announcedata->getFloat(4);
		float z = announcedata->getFloat(4);

		float rx = announcedata->getFloat(4);
		float ry = announcedata->getFloat(4);
		float rz = announcedata->getFloat(4);
		float rw = announcedata->getFloat(4);

		ResetSpawn * ent = new ResetSpawn(name,Ogre::Vector3(x,y,z),Ogre::Quaternion(rx,ry,rz,rw),processinterval);
		ent->networkRegister(requested_class,this);

		mEntityManager->registerEntity(ent);
	} else if ( requested_class == mIDManager->getID(PowerupSpawn::getClassName()) ){
		name = announcedata->getString();
		Ogre::String entity(announcedata->getString());
		float processinterval = announcedata->getFloat(4);

		float x = announcedata->getFloat(4);
		float y = announcedata->getFloat(4);
		float z = announcedata->getFloat(4);

		float rx = announcedata->getFloat(4);
		float ry = announcedata->getFloat(4);
		float rz = announcedata->getFloat(4);
		float rw = announcedata->getFloat(4);

		PowerupSpawn * ent = new PowerupSpawn(name,Ogre::Vector3(x,y,z),Ogre::Quaternion(rx,ry,rz,rw),entity,processinterval);
		ent->networkRegister(requested_class,this);	

		mEntityManager->registerEntity(ent);
	} else if ( requested_class == mIDManager->getID(SpeedBoost::getClassName()) ){
		name = announcedata->getString();
		Ogre::String entity(announcedata->getString());
		float processinterval = announcedata->getFloat(4);

		float x = announcedata->getFloat(4);
		float y = announcedata->getFloat(4);
		float z = announcedata->getFloat(4);

		float rx = announcedata->getFloat(4);
		float ry = announcedata->getFloat(4);
		float rz = announcedata->getFloat(4);
		float rw = announcedata->getFloat(4);

		SpeedBoost * ent = new SpeedBoost(name,Ogre::Vector3(x,y,z),Ogre::Quaternion(rx,ry,rz,rw),entity,processinterval);
		ent->networkRegister(requested_class,this);

		mEntityManager->registerEntity(ent);
	} else if ( requested_class == mIDManager->getID(Portal::getClassName()) ){
		name = announcedata->getString();
		Ogre::String entity(announcedata->getString());
		float processinterval = announcedata->getFloat(4);

		float x = announcedata->getFloat(4);
		float y = announcedata->getFloat(4);
		float z = announcedata->getFloat(4);

		float rx = announcedata->getFloat(4);
		float ry = announcedata->getFloat(4);
		float rz = announcedata->getFloat(4);
		float rw = announcedata->getFloat(4);

		Portal * ent = new Portal(name,Ogre::Vector3(x,y,z),Ogre::Quaternion(rx,ry,rz,rw),entity,processinterval);
		ent->networkRegister(requested_class,this);	

		mEntityManager->registerEntity(ent);
	} else if ( requested_class == mIDManager->getID(Hovercraft::getClassName()) ){
 		name = announcedata->getString();
		Ogre::String entity(announcedata->getString());
		float processinterval = announcedata->getFloat(4);

		float x = announcedata->getFloat(4);
		float y = announcedata->getFloat(4);
		float z = announcedata->getFloat(4);

		float rx = announcedata->getFloat(4);
		float ry = announcedata->getFloat(4);
		float rz = announcedata->getFloat(4);
		float rw = announcedata->getFloat(4);

		Hovercraft * ent = 0;
		
		if (role == eZCom_RoleOwner) {
			ent = new Hovercraft(name,true,Ogre::Vector3(x,y,z),Ogre::Quaternion(rx,ry,rz,rw),entity,processinterval);
			ent->setController(new HovercraftPlayerController());
		}else {
			ent = new Hovercraft(name,false,Ogre::Vector3(x,y,z),Ogre::Quaternion(rx,ry,rz,rw),entity,processinterval);
			HovercraftAIController* ai = new HovercraftAIController("scripts/AI/SimpleAI.lua");
			ent->setController(ai);
			ai->initialize();	
		}	
		
		ent->networkRegister(requested_class,this);	
		mEntityManager->registerEntity(ent);


	}

	// Now that we have created the entity, notify the client preparation loader of the arrival
	Application::msPreparationLoader->update(name);

	// Handle dummy hovercraft
	// TODO Remove this as soon as possible
	if (requested_class == mIDManager->getID("DummyHovercraft")) {
		DummyHovercraft* hovercraft = new DummyHovercraft();
		hovercraft->networkRegister(requested_class, this);
		mEntityManager->registerEntity(hovercraft);
		vector<Ogre::String> subMaterials;
		DummyHovercraftRepresentation * hovercraftRep = new DummyHovercraftRepresentation(hovercraft, Application::msSceneMgr, "cube.mesh", 
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, true, true, 10000.0, "dirt.jpg", subMaterials);
		RepresentationManager::getSingletonPtr()->addEntityRepresentation(hovercraftRep);

		if (role == eZCom_RoleOwner) {
			//DummyHovercraftAIController* ai = new DummyHovercraftAIController("scripts/AI/SimpleAI.lua");
			//hovercraft->setController(ai);
			//ai->initialize();
			hovercraft->setController(new DummyHovercraftPlayerController());
		}
	}
}

void ClientCore::start() {
	if (mLobby) {
		mLobby->start();
	}
}

}
