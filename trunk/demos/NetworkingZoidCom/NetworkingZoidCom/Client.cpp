#include "StdAfx.h"
#include "Client.h"
#include <sstream>

namespace HovUni {

Client::Client(const char* name, const unsigned port) : mServerName(name), mConnectPort(port) {
	initialize(true);
}

Client::Client(const unsigned port) : mServerName(0), mConnectPort(port) {
	initialize(false);
}


Client::~Client() {

}

void Client::initialize(bool remote) {
	ZCom_setDebugName("Client");

	// Create and initialize network sockets (UDP, UDP port, internal socket port)
	bool result = ZCom_initSockets(true, 0, (remote ? 0 : 1));

	if (!result) {
		exit(255);
		// TODO Throw exception
	}

	// New scope to assure server_addr gets out of scope before zcom could be deleted
	{
		// Construct server address
		ZCom_Address server_addr;
		if (remote) {
			std::stringstream ss;
			ss << mServerName << ":" << mConnectPort << endl;
			server_addr.setAddress(eZCom_AddressUDP, 0, ss.str().c_str());
		} else {
			server_addr.setType(eZCom_AddressLocal);
			server_addr.setPort(mConnectPort);
		}
		// Connect
		ZCom_ConnID connection_id = ZCom_Connect(server_addr, 0);
	}
}

void Client::process() {
	ZCom_processInput();
	ZCom_processOutput();
}

void Client::ZCom_cbConnectResult(ZCom_ConnID id, eZCom_ConnectResult result, ZCom_BitStream& reply) {

}

void Client::ZCom_cbConnectionClosed(ZCom_ConnID id, eZCom_CloseReason reason, ZCom_BitStream& reasondata) {

}

void Client::ZCom_cbDataReceived(ZCom_ConnID id, ZCom_BitStream& data) {

}  

void Client::ZCom_cbZoidResult(ZCom_ConnID id, eZCom_ZoidResult result, zU8 new_level, ZCom_BitStream& reason) {

}

void Client::ZCom_cbNodeRequest_Dynamic(ZCom_ConnID id, ZCom_ClassID requested_class, ZCom_BitStream* announcedata, eZCom_NodeRole role, ZCom_NodeID net_id) {

}

void Client::ZCom_cbNodeRequest_Tag(ZCom_ConnID id, ZCom_ClassID requested_class, ZCom_BitStream* announcedata, eZCom_NodeRole role, zU32 tag) {

}

bool Client::ZCom_cbDiscoverRequest(const ZCom_Address& addr, ZCom_BitStream& request, ZCom_BitStream& reply) {
	return false;
}

void Client::ZCom_cbDiscovered(const ZCom_Address& addr, ZCom_BitStream& reply) {

}

//
// Server only callbacks
//
bool Client::ZCom_cbConnectionRequest(ZCom_ConnID id, ZCom_BitStream& request, ZCom_BitStream& reply) {
	return false;
}

void Client::ZCom_cbConnectionSpawned(ZCom_ConnID id) {

}

bool Client::ZCom_cbZoidRequest(ZCom_ConnID id, zU8 requested_level, ZCom_BitStream& reason) {
	return false;
}

}