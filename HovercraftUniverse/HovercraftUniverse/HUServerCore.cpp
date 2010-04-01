#include "HUServerCore.h"
#include "ServerLoader.h"
#include "EntityRegister.h"

namespace HovUni {

HUServerCore::HUServerCore() : NetworkServer(2375, 2376, "HUServer"), mEntityManager(0), mIDManager(0) {
	// Create and store entity manager
	mEntityManager = EntityManager::getServerSingletonPtr();
	mIDManager = NetworkIDManager::getServerSingletonPtr();
	mIDManager->setControl(this);
	EntityRegister::registerAll(*mIDManager);
	ZCom_setUpstreamLimit(0, 0);

	// Create lobby
	mLobby = new Lobby(new ServerLoader());
	// Register lobby
	mLobby->networkRegisterUnique(mIDManager->getID(Lobby::getClassName()), this, true);
}

HUServerCore::~HUServerCore() {
	delete mLobby;
	mLobby;
}

void HUServerCore::process() {
	NetworkServer::process();
	mLobby->process();
}

bool HUServerCore::ZCom_cbConnectionRequest(ZCom_ConnID id, ZCom_BitStream& request, ZCom_BitStream& reply) {
	// Accept a connection if lobby isn't full
	return mLobby->onConnectAttempt(id);
}

void HUServerCore::ZCom_cbConnectionSpawned(ZCom_ConnID id) {
	ZCom_requestDownstreamLimit(id, 60, 600);

	// Notice the lobby of new connection
	mLobby->onConnect(id);
}

void HUServerCore::ZCom_cbConnectionClosed(ZCom_ConnID id, eZCom_CloseReason reason, ZCom_BitStream& reasondata) {
	// Connection closed
	mLobby->onDisconnect(id);
}

void HUServerCore::ZCom_cbDataReceived(ZCom_ConnID id, ZCom_BitStream& data) {

}

bool HUServerCore::ZCom_cbZoidRequest(ZCom_ConnID id, zU8 requested_level, ZCom_BitStream& reason) {
	// Only accept level 1
	if (requested_level == 1) {
		return true;
	} else {
		return false;
	}
}

void HUServerCore::ZCom_cbZoidResult(ZCom_ConnID id, eZCom_ZoidResult result, zU8 new_level, ZCom_BitStream& reason) {
	// Result of zoid request
}

}