#include "ChatEventParser.h"
#include "TextEvent.h"
#include "NotifyEvent.h"

namespace HovUni {

ChatEventParser::~ChatEventParser() {

}

ChatEvent* ChatEventParser::parse(ZCom_BitStream* stream) {
	ChatEventType type = ChatEvent::readType(stream);

	switch (type) {
	case textLine:
		return TextEvent::parse(stream);
		break;
	case notifyLine:
		return NotifyEvent::parse(stream);
		break;
	default:
		// TODO exception
		return 0;
		break;
	}
}

}
