#include "ChatClient.h"
#include "Exception.h"

namespace HovUni {

ChatClient::ChatClient(const std::string& username, const char* name, unsigned int port) :
	NetworkClient(name, port, "ChatClient"), mChat(0), mIDManager(0), mUser(username) {
	initialize();
}

ChatClient::ChatClient(const std::string& username) :
	NetworkClient(2378), mChat(0), mIDManager(0), mUser(username) {
	initialize();
}

ChatClient::~ChatClient() {

}

void ChatClient::initialize() {
	mIDManager = new NetworkIDManager(this);
	mIDManager->registerClass(ChatEntity::getClassName());
	ZCom_setUpstreamLimit(0, 0);
}

void ChatClient::registerListener(ChatListener* listener) {
	if (mChat) {
		mChat->registerListener(listener);
	} else {
		mListeners.push_back(listener);
	}
}

void ChatClient::process() {
	NetworkClient::process();
	if (mChat) {
		mChat->processEvents(0.0f);
	}
}

void ChatClient::setUsername(const std::string& username) {
	mUser = username;
}

void ChatClient::sendText(const std::string& line) {
	if (mChat) {
		mChat->sendLine(mUser, line);
	}
}

void ChatClient::ZCom_cbConnectResult(ZCom_ConnID id, eZCom_ConnectResult result,
		ZCom_BitStream& reply) {
	if (result == eZCom_ConnAccepted) {
		// Connection accepted, so request zoid level
		ZCom_requestZoidMode(id, 1);
	} else {
		// Connection failed
		THROW(NetworkException, "Connection failed");
		return;
	}
}

void ChatClient::ZCom_cbConnectionClosed(ZCom_ConnID id, eZCom_CloseReason reason,
		ZCom_BitStream& reasondata) {
	// Connection closed
}

void ChatClient::ZCom_cbDataReceived(ZCom_ConnID id, ZCom_BitStream& data) {
	// Data received
}

void ChatClient::ZCom_cbZoidResult(ZCom_ConnID id, eZCom_ZoidResult result, zU8 new_level,
		ZCom_BitStream& reason) {
	if (result == eZCom_ZoidEnabled) {
		// Requested zoid level was confirmed
	} else {
		// Requested zoid level denied
	}
}

void ChatClient::ZCom_cbNodeRequest_Dynamic(ZCom_ConnID id, ZCom_ClassID requested_class,
		ZCom_BitStream* announcedata, eZCom_NodeRole role, ZCom_NodeID net_id) {
	if (requested_class == mIDManager->getID(ChatEntity::getClassName())) {
		// Lobby received (upon connect)
		mChat = new ChatEntity();
		mChat->networkRegister(requested_class, this);

		for (std::vector<ChatListener*>::iterator it = mListeners.begin(); it != mListeners.end(); ++it) {
			mChat->registerListener(*it);
		}
		mListeners.clear();
	}
}

}
