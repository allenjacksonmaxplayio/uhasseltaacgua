#include "StdAfx.h"
#include "Server.h"
#include "Tree.h"
#include "Player.h"

Server::Server(void) { }

Server::~Server(void) { }

void Server::addEntity(Entity* entity) {
	mEntities.push_back(entity);
}

void Server::update() {
	for (vector<Entity*>::iterator it = mEntities.begin(); it != mEntities.end(); ++it) {
		(*it)->processNodeEvents();
	}
}

bool Server::ZCom_cbConnectionRequest(ZCom_ConnID id, ZCom_BitStream& request, ZCom_BitStream& reply) {
	cout << "A client requested connection - the new id is [" << id << "]." << endl;
	//// get the password
	//const char *password = request.getStringStatic();
	//// compare it
	//if (password && strlen(password) > 0 && strcmp("let_me_in", password) == 0) {
	//	cout << "Connection Accepted." << endl;
	//	reply.addString("Password Correct.");
	//	// accept connection
	//	return true;
	//} else {
	//	reply.addString("Password Wrong.");
	//	cout << "Connection Denied." << endl;
	//	// deny connection
	//	return false;
	//}
	return true;
}

void Server::ZCom_cbConnectionSpawned(ZCom_ConnID id) {
	cout << "New connection with id [" << id << "]" << endl;
	Player* player = new Player(this);
	player->getNetworkNode()->setOwner(id, true);
	mEntities.push_back(player);
}

void Server::ZCom_cbConnectionClosed(ZCom_ConnID id, eZCom_CloseReason reason, ZCom_BitStream& reasondata) {
	cout << "Connection with id [" << id << "] closed" << endl;
}

void Server::ZCom_cbDataReceived(ZCom_ConnID id, ZCom_BitStream& data) {
	cout << "Received a string: " << data.getStringStatic() << endl;
}

bool Server::ZCom_cbZoidRequest(ZCom_ConnID id, zU8 requested_level, ZCom_BitStream& reason) {
	if (requested_level == 1) {
		return true;
	} else {
		return false;
	}
}

void Server::ZCom_cbZoidResult(ZCom_ConnID id, eZCom_ZoidResult result, zU8 new_level, ZCom_BitStream& reason) {
	if (result == eZCom_ZoidEnabled) {
		cout << "Zoidlevel " << (int) new_level << " entered" << endl;
	} else {
		cout << "Failed entering Zoidlevel " << new_level << endl;
	}

}

bool Server::ZCom_cbDiscoverRequest(const ZCom_Address& addr, ZCom_BitStream& request, ZCom_BitStream& reply) {
	return false;
}

void Server::ZCom_cbDiscovered(const ZCom_Address& addr, ZCom_BitStream& reply) {

}

//
// Client only callbacks
//
void Server::ZCom_cbConnectResult(ZCom_ConnID id, eZCom_ConnectResult result, ZCom_BitStream& reply) {

}

void Server::ZCom_cbNodeRequest_Dynamic(ZCom_ConnID id, ZCom_ClassID requested_class, ZCom_BitStream* announcedata, eZCom_NodeRole role, ZCom_NodeID net_id) {

}

void Server::ZCom_cbNodeRequest_Tag(ZCom_ConnID id, ZCom_ClassID requested_class, ZCom_BitStream* announcedata, eZCom_NodeRole role, zU32 tag) {

}

