#include "ClientCore.h"
#include "Application.h"
#include "ClientLoader.h"
#include "DummyHovercraft.h"
#include "DummyHovercraftPlayerController.h"
#include "DummyHovercraftAIController.h"
#include "DummyHovercraftRepresentation.h"
#include "EntityRegister.h"

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
