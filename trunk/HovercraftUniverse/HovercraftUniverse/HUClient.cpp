#include "HUClient.h"
#include "HUApplication.h"
#include "ClientLoader.h"
#include "EntityRegister.h"

#include "HovercraftPlayerController.h"
#include "HovercraftAIController.h"

#include "Lobby.h"
#include "PlayerSettings.h"

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

HUClient::HUClient(const char* name, unsigned int port) : NetworkClient(name, port), mEntityManager(0), mIDManager(0), mLobby(0) {
	//Initialize the chat client
	mChatClient = new ChatClient("Player", name);

	initialize();
}

HUClient::HUClient() : NetworkClient(2376), mEntityManager(0), mIDManager(0), mLobby(0) {
	//Initialize the chat client
	mChatClient = new ChatClient("Player");
	
	initialize();
}

HUClient::~HUClient() {
	delete mChatClient;
}

void HUClient::initialize() {
	// Create and store entity manager
	mEntityManager = EntityManager::getClientSingletonPtr();
	mIDManager = new NetworkIDManager(this);
	EntityRegister::registerAll(*mIDManager);
	ZCom_setUpstreamLimit(0, 0);
}

void HUClient::process() {
	NetworkClient::process();
	mChatClient->process();
}

void HUClient::ZCom_cbConnectResult(ZCom_ConnID id, eZCom_ConnectResult result, ZCom_BitStream& reply) {
	if (result == eZCom_ConnAccepted) {
		// Connection accepted, so request zoid level
		ZCom_requestDownstreamLimit(id, 60, 600);
		ZCom_requestZoidMode(id, 1);
	} else {
		// Connection failed
		return;
	}
}

void HUClient::ZCom_cbConnectionClosed(ZCom_ConnID id, eZCom_CloseReason reason, ZCom_BitStream& reasondata) {
	// Connection closed
}

void HUClient::ZCom_cbDataReceived(ZCom_ConnID id, ZCom_BitStream& data) {
	// Data received
}  

void HUClient::ZCom_cbZoidResult(ZCom_ConnID id, eZCom_ZoidResult result, zU8 new_level, ZCom_BitStream& reason) {
	if (result == eZCom_ZoidEnabled) {
		// Requested zoid level was confirmed
	} else {
		// Requested zoid level denied
	}
}

void HUClient::ZCom_cbNodeRequest_Dynamic(ZCom_ConnID id, ZCom_ClassID requested_class, ZCom_BitStream* announcedata, eZCom_NodeRole role, ZCom_NodeID net_id) {
	// Receive and create the entity
	Ogre::String name("");

	//Lobby
	if (requested_class == mIDManager->getID(Lobby::getClassName())) {
		// Lobby received (upon connect)
		mLobby = new Lobby(0);
		mLobby->networkRegister(requested_class, this);
		HUApplication::msPreparationLoader->registerLoader(mLobby->getTrackFilename());
	} 
	else if ( requested_class == mIDManager->getID(PlayerSettings::getClassName()) ){
		// Player (TODO do something with it)
		PlayerSettings * ent = new PlayerSettings(announcedata);
		ent->networkRegister(requested_class,this);
	}	
	//Entities
	else if ( requested_class == mIDManager->getID(Asteroid::getClassName()) ){
		Asteroid * ent = new Asteroid(announcedata);
		ent->networkRegister(requested_class,this);
		mEntityManager->registerEntity(ent);
		name = ent->getName();
	} else if ( requested_class == mIDManager->getID(CheckPoint::getClassName()) ){
		CheckPoint * ent = new CheckPoint(announcedata);
		ent->networkRegister(requested_class,this);
		mEntityManager->registerEntity(ent);
		name = ent->getName();
	} else if ( requested_class == mIDManager->getID(Start::getClassName()) ){
		Start * ent = new Start(announcedata);
		ent->networkRegister(requested_class,this);
		mEntityManager->registerEntity(ent);
		name = ent->getName();
	} else if ( requested_class == mIDManager->getID(StartPosition::getClassName()) ){
		StartPosition * ent = new StartPosition(announcedata);
		ent->networkRegister(requested_class,this);
		mEntityManager->registerEntity(ent);
		name = ent->getName();
	} else if ( requested_class == mIDManager->getID(Finish::getClassName()) ){
		Finish * ent = new Finish(announcedata);
		ent->networkRegister(requested_class,this);	
		mEntityManager->registerEntity(ent);
		name = ent->getName();
	} else if ( requested_class == mIDManager->getID(ResetSpawn::getClassName()) ){
		ResetSpawn * ent = new ResetSpawn(announcedata);
		ent->networkRegister(requested_class,this);
		mEntityManager->registerEntity(ent);
		name = ent->getName();
	} else if ( requested_class == mIDManager->getID(PowerupSpawn::getClassName()) ){
		PowerupSpawn * ent = new PowerupSpawn(announcedata);
		ent->networkRegister(requested_class,this);
		mEntityManager->registerEntity(ent);
		name = ent->getName();
	} else if ( requested_class == mIDManager->getID(SpeedBoost::getClassName()) ){	
		SpeedBoost * ent = new SpeedBoost(announcedata);
		ent->networkRegister(requested_class,this);
		mEntityManager->registerEntity(ent);
		name = ent->getName();
	} else if ( requested_class == mIDManager->getID(Portal::getClassName()) ){
		Portal * ent = new Portal(announcedata);
		ent->networkRegister(requested_class,this);
		mEntityManager->registerEntity(ent);
		name = ent->getName();
	} else if ( requested_class == mIDManager->getID(Hovercraft::getClassName()) ){
		Hovercraft * ent = 0;
		
		if (role == eZCom_RoleOwner) {
			ent = new Hovercraft(announcedata);
			ent->setController(new HovercraftPlayerController());
		}else {
			ent = new Hovercraft(announcedata);
			HovercraftAIController* ai = new HovercraftAIController("scripts/AI/Pathfinding.lua");
			ent->setController(ai);
			ai->initialize();	
		}	
		
		HovercraftRepresentation * test = new HovercraftRepresentation(ent,HUApplication::msSceneMgr,"hover1.mesh","General",true,true,500,"hover1.material",std::vector<Ogre::String>());
		RepresentationManager::getSingletonPtr()->addEntityRepresentation(test);

		ent->networkRegister(requested_class,this);	
		mEntityManager->registerEntity(ent);

		if (role == eZCom_RoleOwner) {
			mEntityManager->trackEntity(ent->getName());
		}
	}

	if ( !name.empty() ){
		// Now that we have created the entity, notify the client preparation loader of the arrival
		HUApplication::msPreparationLoader->update(name);
	}

}

void HUClient::start() {
	if (mLobby) {
		mLobby->start();
	}
}

}
