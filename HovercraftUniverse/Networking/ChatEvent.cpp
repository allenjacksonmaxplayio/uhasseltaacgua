#include "ChatEvent.h"

namespace HovUni {

ChatEvent::ChatEvent(ChatEventType type, const std::string& line) :
	NetworkEvent<ChatEventType, ChatEventTypeSize> (type), mLine(line) {

}

ChatEvent::~ChatEvent() {

}

std::string ChatEvent::getLine() const {
	return mLine;
}

}
