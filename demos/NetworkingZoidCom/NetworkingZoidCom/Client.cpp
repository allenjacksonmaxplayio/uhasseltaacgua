#include "StdAfx.h"
#include "Client.h"
#include "Tree.h"
#include "Player.h"

Client::Client() : mExit(false), mPlayer(0) {
}

Client::~Client() {
}

bool Client::canExit() const {
	return mExit;
}

void Client::moveUp() {
	ZCom_BitStream* event = new ZCom_BitStream();
	event->addString("Move Up");
	event->addInt(3, 8);
	if (mPlayer->getNetworkNode()->sendEvent(eZCom_Unreliable, ZCOM_REPRULE_OWNER_2_AUTH, event)) {
		cout << "Sent Move Up as ";
		switch (mPlayer->getNetworkNode()->getRole()) {
			case eZCom_RoleAuthority:
				cout << "Authority" << endl;
				break;
			case eZCom_RoleOwner:
				cout << "Owner" << endl;
				break;
			case eZCom_RoleProxy:
				cout << "Proxy" << endl;
				break;
			default:
				break;
		}
	}
}

void Client::addEntity(Entity* entity) {
	mEntities.push_back(entity);
}

void Client::update() {
	for (vector<Entity*>::iterator it = mEntities.begin(); it != mEntities.end(); ++it) {
		(*it)->processNodeEvents();
	}
}

void Client::ZCom_cbConnectResult(ZCom_ConnID id, eZCom_ConnectResult result, ZCom_BitStream& reply) {
	if (result == eZCom_ConnAccepted) {
		cout << "Connection established. The reply was: " << reply.getStringStatic() << endl;
		ZCom_requestZoidMode(id, 1);
	} else {
		cout << "Connection failed. The reply was: " << reply.getStringStatic() << endl;
		return;
	}
}

void Client::ZCom_cbConnectionClosed(ZCom_ConnID id, eZCom_CloseReason reason, ZCom_BitStream& reasondata) {
	cout << "Connection to server closed. Exiting..." << endl;
	mExit = true;
}

void Client::ZCom_cbDataReceived(ZCom_ConnID id, ZCom_BitStream& data) {
	cout << "Received a string: " << data.getStringStatic() << endl;
}  

void Client::ZCom_cbZoidResult(ZCom_ConnID id, eZCom_ZoidResult result, zU8 new_level, ZCom_BitStream& reason) {
	if (result == eZCom_ZoidEnabled) {
		cout << "Zoidlevel " << (int) new_level << " entered" << endl;
	} else {
		cout << "Failed entering Zoidlevel " << new_level << endl;
	}
}

void Client::ZCom_cbNodeRequest_Dynamic(ZCom_ConnID id, ZCom_ClassID requested_class, ZCom_BitStream* announcedata, eZCom_NodeRole role, ZCom_NodeID net_id) {
	if (requested_class == Tree::getClassID()) {
		Tree* tree = new Tree(this);
		addEntity(tree);
		cout << "Tree created with role ";
	} else if (requested_class == Player::getClassID()) {
		if (role == eZCom_RoleOwner) {
			mPlayer = new Player(this);
			addEntity(mPlayer);
			cout << "Own player created with role ";
		} else {
			addEntity(new Player(this));
			cout << "Player created with role ";
		}
	}

	if (role == eZCom_RoleAuthority) {
		cout << "Authority" << endl;
	} else if (role == eZCom_RoleOwner) {
		cout << "Owner" << endl;
	} else if (role == eZCom_RoleProxy) {
		cout << "Proxy" << endl;
	} else {
		cout << "Undefined" << endl;
	}

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

