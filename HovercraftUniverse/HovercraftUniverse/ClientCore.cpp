#include "ClientCore.h"
#include "Application.h"
#include "ClientLoader.h"
#include "DummyHovercraft.h"
#include "DummyHovercraftPlayerController.h"
#include "DummyHovercraftAIController.h"
#include "DummyHovercraftRepresentation.h"
#include "EntityRegister.h"

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

ClientCore::ClientCore(const char* name,unsigned int port) : NetworkClient(name,port), mEntityManager(0), mIDManager(0), mLobby(0) {
	initialize();
}

ClientCore::ClientCore() : NetworkClient(3041), mEntityManager(0), mIDManager(0), mLobby(0) {
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
	if (requested_class == mIDManager->getID(Lobby::getClassName())) {
		// Lobby received (upon connect)
		mLobby = new Lobby(new ClientLoader());
		mLobby->networkRegister(requested_class, this);
	}
/*
	if ( requested_class == mIDManager->getID(Asteroid::getName()) ){
		Asteroid * entity = new Asteroid();
		entity->networkRegister(requested_class,this);
	}
	if ( requested_class == mIDManager->getID(CheckPoint::getName()) ){
		CheckPoint * entity = new CheckPoint();
		entity->networkRegister(requested_class,this);
	}
	if ( requested_class == mIDManager->getID(Start::getName()) ){
		Start * entity = new Start();
		entity->networkRegister(requested_class,this);
	}
	if ( requested_class == mIDManager->getID(StartPosition::getName()) ){
		StartPosition * entity = new StartPosition();
		entity->networkRegister(requested_class,this);
	}
	if ( requested_class == mIDManager->getID(Finish::getName()) ){
		Finish * entity = new Finish();
		entity->networkRegister(requested_class,this);	
	}
	if ( requested_class == mIDManager->getID(ResetSpawn::getName()) ){
		StartPosition * entity = new ResetSpawn();
		entity->networkRegister(requested_class,this);
	}
	if ( requested_class == mIDManager->getID(PowerupSpawn::getName()) ){
		Finish * entity = new PowerupSpawn();
		entity->networkRegister(requested_class,this);	
	}
	if ( requested_class == mIDManager->getID(SpeedBoost::getName()) ){
		StartPosition * entity = new SpeedBoost();
		entity->networkRegister(requested_class,this);
	}
	if ( requested_class == mIDManager->getID(Portal::getName()) ){
		Finish * entity = new Portal();
		entity->networkRegister(requested_class,this);	
	}*/

	if (requested_class == mIDManager->getID("DummyHovercraft")) {
		DummyHovercraft* hovercraft = new DummyHovercraft();
		hovercraft->networkRegister(requested_class, this);
		mEntityManager->registerEntity(hovercraft);
		DummyHovercraftRepresentation * hovercraftRep = new DummyHovercraftRepresentation(hovercraft, Application::msSceneMgr);
		RepresentationManager::getSingletonPtr()->addEntityRepresentation(hovercraftRep);

		if (role == eZCom_RoleOwner) {
			//hovercraft->setController(new DummyHovercraftAIController("scripts/AI/SimpleAI.lua"));
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
