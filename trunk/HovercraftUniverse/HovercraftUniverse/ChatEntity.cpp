#include "ChatEntity.h"
#include "NetworkIDManager.h"
#include "ChatEventParser.h"
#include "TextEvent.h"
#include <iostream>

namespace HovUni {

std::string ChatEntity::getClassName() { 
	return "ChatEntity";
}

ChatEntity::ChatEntity(unsigned size) : NetworkEntity(0), mSize(size) {

}

ChatEntity::~ChatEntity() {

}

void ChatEntity::sendLine(const string& user, const string& line) {
	sendEvent(TextEvent(user, line));
}

void ChatEntity::parseEvents(ZCom_BitStream* stream, float timeSince) {
	ChatEventParser p;
	ChatEvent* event = p.parse(stream);
	eZCom_NodeRole role = mNode->getRole();
	switch(role) {
		case eZCom_RoleAuthority:
			processEventsServer(event);
			break;
		default:
			processEventsClient(event);
			break;
	}
	delete event;
}

void ChatEntity::processEventsServer(ChatEvent* event) {
	// Save the new event in the moving status
	TextEvent* text = dynamic_cast<TextEvent*>(event);
	if (text) {
		addLine(text->getLine());
		sendEvent(*text);
	}
}

void ChatEntity::processEventsClient(ChatEvent* event) {
	// Save the new event in the moving status
	TextEvent* text = dynamic_cast<TextEvent*>(event);
	if (text) {
		addLine(text->getLine());
		std::cout << "CHAT: " << text->getLine() << std::endl;
	}
}

void ChatEntity::setupReplication() {

}

void ChatEntity::addLine(const std::string& line) {
	if (mList.size() == mSize) {
		mList.erase(mList.begin());
	}
	mList.push_back(line);
}

}