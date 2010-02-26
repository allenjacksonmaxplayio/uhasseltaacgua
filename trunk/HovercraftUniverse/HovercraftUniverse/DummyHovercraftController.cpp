#include "DummyHovercraftController.h"
#include "BasicEntityEvent.h"

namespace HovUni {

DummyHovercraftController::~DummyHovercraftController() {

}

std::vector<ControllerEvent*> DummyHovercraftController::getEvents() {
	std::vector<ControllerEvent*> events;
	Ogre::Vector3 direction = getDirection();
	Ogre::Vector3 orientation = getOrientationChange();

	// Only send an event when there really is an event
	if ((direction.length() != 0) || (orientation.length() != 0)) {
		events.push_back(new BasicEntityEvent(direction, orientation));
	}
	return events;
}

}