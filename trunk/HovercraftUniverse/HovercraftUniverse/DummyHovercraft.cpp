#include "DummyHovercraft.h"
#include "DummyHovercraftController.h"
#include "DummyHovercraftPlayerController.h"
#include "BasicEntityEvent.h"
#include <OgreLogManager.h>

namespace HovUni {

DummyHovercraft::DummyHovercraft(void) : Entity("hovercraft", "vehicles", true, Ogre::Vector3(0.0, 40.0, 0.0), 
												Ogre::Vector3(0.0, 0.0, -1.0), 1.0f / 60.0f), mMovingStatus(0) {
	// Already initialized
}

DummyHovercraft::~DummyHovercraft(void) {
	// Empty
}

void DummyHovercraft::process(float timeSince) {
	if (mMovingStatus && (timeSince > 0.0f) && (mNode->getRole() == eZCom_RoleAuthority)) {
		Ogre::Vector3 accumulatedDirection = Ogre::Vector3::ZERO;
		if (mMovingStatus->moveLeft()) { accumulatedDirection += Ogre::Vector3(-1.0, 0.0, 0.0); }
		if (mMovingStatus->moveForward()) { accumulatedDirection += Ogre::Vector3(0.0, 0.0, -1.0); }
		if (mMovingStatus->moveRight()) { accumulatedDirection += Ogre::Vector3(1.0, 0.0, 0.0); }
		if (mMovingStatus->moveBackward()) { accumulatedDirection += Ogre::Vector3(0.0, 0.0, 1.0); }
		accumulatedDirection.normalise();
	
		changePosition(getPosition() + accumulatedDirection * timeSince * 100);
	}
}

void DummyHovercraft::processEventsServer(ControllerEvent* event) {
	// Save the new event in the moving status
	BasicEntityEvent* movestatus = dynamic_cast<BasicEntityEvent*>(event);
	if (movestatus) {
		mMovingStatus = new BasicEntityEvent(*movestatus);
	}
}

void DummyHovercraft::processEventsOwner(ControllerEvent* event) {
	// Owner cannot receive events in this entity
}

void DummyHovercraft::processEventsOther(ControllerEvent* event) {
	// Other cannot receive events in this entity
}

}