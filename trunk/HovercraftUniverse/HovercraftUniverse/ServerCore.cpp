#include "ServerCore.h"
#include "DummyHovercraft.h"
#include "EntityRegister.h"

namespace HovUni {

ServerCore::ServerCore() : NetworkServer(3040, 3041), mEntityManager(0), mIDManager(0) {
	// Create and store entity manager
	mEntityManager = EntityManager::getServerSingletonPtr();
	mIDManager = new NetworkIDManager(this);
	EntityRegister::registerAll(*mIDManager);
	ZCom_setUpstreamLimit(0, 0);

	//register loby
	mLobby.networkRegister(mIDManager->getID("Lobby"), this);
}

ServerCore::~ServerCore() {
}

void ServerCore::process() {
	NetworkServer::process();
}

bool ServerCore::ZCom_cbConnectionRequest(ZCom_ConnID id, ZCom_BitStream& request, ZCom_BitStream& reply) {
	// Accept a connection if loby isn't full
	return mLobby.onConnectAttempt();
}

void ServerCore::ZCom_cbConnectionSpawned(ZCom_ConnID id) {
	ZCom_requestDownstreamLimit(id, 60, 600);

	mLobby.onConnect(id);

	// TODO Move somewhere else
	DummyHovercraft * hovercraft = new DummyHovercraft();
	hovercraft->networkRegister(mIDManager->getID("DummyHovercraft"), this);
	hovercraft->getNetworkNode()->setOwner(id, true);
	mEntityManager->registerEntity(hovercraft);
}

void ServerCore::ZCom_cbConnectionClosed(ZCom_ConnID id, eZCom_CloseReason reason, ZCom_BitStream& reasondata) {
	// Connection closed
	mLobby.onDisconnect(id);
}

void ServerCore::ZCom_cbDataReceived(ZCom_ConnID id, ZCom_BitStream& data) {

}

bool ServerCore::ZCom_cbZoidRequest(ZCom_ConnID id, zU8 requested_level, ZCom_BitStream& reason) {
	// Only accept level 1
	if (requested_level == 1) {
		return true;
	} else {
		return false;
	}
}

void ServerCore::ZCom_cbZoidResult(ZCom_ConnID id, eZCom_ZoidResult result, zU8 new_level, ZCom_BitStream& reason) {
	// Result of zoid request
}

}