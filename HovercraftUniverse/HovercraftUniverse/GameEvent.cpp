#include "GameEvent.h"

namespace HovUni {

GameEvent::GameEvent(GameEventType type) : NetworkEvent<GameEventType, GameEventTypeSize>(type) {

}

GameEvent::~GameEvent() {

}

/*
 * Simple game events
 */
HOVUNI_GAMEEVENT_DEFINITION(StartTrackEvent, startTrack)

}