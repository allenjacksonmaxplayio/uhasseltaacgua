#include "StdAfx.h"
#include "Server.h"

namespace HovUni {

Server::Server(const unsigned port, const unsigned internalport) : mServerPort(port), mInternalPort(internalport) {
	ZCom_setDebugName("Server");

	// Create and initialize network sockets (UDP, UDP port, internal socket port)
	bool result = ZCom_initSockets(true, mServerPort, mInternalPort);

	if (!result) {
		exit(255);
		// TODO Throw exception
	}

}

Server::~Server() {

}

void Server::process() {
	ZCom_processInput();
	ZCom_processOutput();
}

bool Server::ZCom_cbConnectionRequest(ZCom_ConnID id, ZCom_BitStream& request, ZCom_BitStream& reply) {
	return true;
}

void Server::ZCom_cbConnectionSpawned(ZCom_ConnID id) {

}

void Server::ZCom_cbConnectionClosed(ZCom_ConnID id, eZCom_CloseReason reason, ZCom_BitStream& reasondata) {

}

void Server::ZCom_cbDataReceived(ZCom_ConnID id, ZCom_BitStream& data) {

}

bool Server::ZCom_cbZoidRequest(ZCom_ConnID id, zU8 requested_level, ZCom_BitStream& reason) {
	return false;
}

void Server::ZCom_cbZoidResult(ZCom_ConnID id, eZCom_ZoidResult result, zU8 new_level, ZCom_BitStream& reason) {

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

}
