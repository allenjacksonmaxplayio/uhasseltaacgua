#include "GameEventParser.h"

namespace HovUni {

GameEventParser::~GameEventParser() {

}

GameEvent* GameEventParser::parse(ZCom_BitStream* stream) {
	GameEventType type = GameEvent::readType(stream);

	switch (type) {
		case startTrack:
			return StartTrackEvent::parse(stream);
			break;
		default:
			// TODO exception
			return 0;
			break;
	}
}

}