#include "GameEventParser.h"

#include "StateEvent.h"
#include "OnJoinEvent.h"
#include "OnLeaveEvent.h"
#include "InitEvent.h"
#include "CheckpointEvent.h"

namespace HovUni {

GameEventParser::~GameEventParser() {

}

GameEvent* GameEventParser::parse(ZCom_BitStream* stream) {
	GameEventType type = GameEvent::readType(stream);

	switch (type) {
	case init:
		return InitEvent::parse(stream);
	case stateChange:
		return StateEvent::parse(stream);
	case startTrack:
		return StartTrackEvent::parse(stream);
	case onJoin:
		return OnJoinEvent::parse(stream);
	case onLeave:
		return OnLeaveEvent::parse(stream);
	case checkPoint:
		return CheckpointEvent::parse(stream);
	default:
		return 0;
		break;
	}
}

}
