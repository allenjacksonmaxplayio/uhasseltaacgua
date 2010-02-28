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
}

ServerCore::~ServerCore() {

}

void ServerCore::process() {
	NetworkServer::process();
	std::vector<Entity*> entities = mEntityManager->getAllEntities();
	for (std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it) {
		Entity* entity = *it;
		entity->processEvents();
	}
}

bool ServerCore::ZCom_cbConnectionRequest(ZCom_ConnID id, ZCom_BitStream& request, ZCom_BitStream& reply) {
	// Accept each connection
	return true;
}

void ServerCore::ZCom_cbConnectionSpawned(ZCom_ConnID id) {
	ZCom_requestDownstreamLimit(id, 60, 600);

	// TODO Move somewhere else
	DummyHovercraft * hovercraft = new DummyHovercraft();
	hovercraft->networkRegister(mIDManager->getID("DummyHovercraft"), this);
	hovercraft->getNetworkNode()->setOwner(id, true);
	mEntityManager->registerEntity(hovercraft);
}

void ServerCore::ZCom_cbConnectionClosed(ZCom_ConnID id, eZCom_CloseReason reason, ZCom_BitStream& reasondata) {
	// Connection closed
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