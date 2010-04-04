#include "HovercraftController.h"
#include "Hovercraft.h"

namespace HovUni {

HovercraftController::HovercraftController() : mLast(false, false, false, false) {

}

HovercraftController::~HovercraftController() {

}

std::vector<ControllerEvent*> HovercraftController::getEvents() {
	std::vector<ControllerEvent*> events;
	BasicEntityEvent current(moveForward(), moveBackward(), turnLeft(), turnRight());

	// Only send an event when there is a change
	if (!(current == mLast)) {
		events.push_back(new BasicEntityEvent(current));
		mLast = current;
	}
	return events;
}

}
