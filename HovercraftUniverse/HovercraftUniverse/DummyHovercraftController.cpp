#include "DummyHovercraftController.h"

namespace HovUni {

DummyHovercraftController::DummyHovercraftController() : mLast(false, false, false, false) {

}

DummyHovercraftController::~DummyHovercraftController() {

}

std::vector<ControllerEvent*> DummyHovercraftController::getEvents() {
	std::vector<ControllerEvent*> events;
	BasicEntityEvent current(moveForward(), moveBackward(), moveLeft(), moveRight());

	// Only send an event when there is a change
	if (!(current == mLast)) {
		events.push_back(new BasicEntityEvent(current));
		mLast = current;
	}
	return events;
}

}