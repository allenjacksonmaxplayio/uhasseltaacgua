#ifndef GAMEEVENTTYPE_H_
#define GAMEEVENTTYPE_H_

namespace HovUni {

/**
 * This is an event type for game events.
 *
 * @author Olivier Berghmans
 */
enum GameEventType {
	startTrack,
	onJoin,
	onLeave
	// Make sure to adjust the amount below
};

/** The amount of event types, used for compressing in the network */
static const unsigned GameEventTypeSize = 3;

}

#endif
