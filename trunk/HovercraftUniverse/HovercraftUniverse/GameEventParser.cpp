#include "GameEventParser.h"

#include "OnJoinEvent.h"
#include "onLeaveEvent.h"

namespace HovUni {

GameEventParser::~GameEventParser() {

}

GameEvent* GameEventParser::parse(ZCom_BitStream* stream) {
	GameEventType type = GameEvent::readType(stream);

	switch (type) {
		case startTrack:
			return StartTrackEvent::parse(stream);
		case onJoin:
			return OnJoinEvent::parse(stream);
		case onLeave:
			return OnLeaveEvent::parse(stream);
		default:
			return 0;
			break;
	}
}

}