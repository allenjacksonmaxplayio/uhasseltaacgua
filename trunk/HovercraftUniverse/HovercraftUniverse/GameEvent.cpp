#include "GameEvent.h"

namespace HovUni {

GameEvent::GameEvent(GameEventType type) : NetworkEvent<GameEventType>(type) {

}

GameEvent::~GameEvent(void) {

}

/*
 * Simple game events
 */
HOVUNI_GAMEEVENT_DEFINITION(StartTrackEvent, startTrack)

}