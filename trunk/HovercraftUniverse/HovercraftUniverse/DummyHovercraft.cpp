#include "DummyHovercraft.h"
#include "DummyHovercraftController.h"
#include "DummyHovercraftPlayerController.h"
#include "BasicEntityEvent.h"
#include <OgreLogManager.h>

namespace HovUni {

DummyHovercraft::DummyHovercraft(void) : Entity("hovercraft", "vehicles", true, Ogre::Vector3(0.0, 40.0, 0.0), 
												Ogre::Vector3(1.0, 0.0,-1.0),"", 1.0f / 60.0f,0), mMovingStatus(0) {
	// Already initialized
}

DummyHovercraft::~DummyHovercraft(void) {
	// Empty
}

void DummyHovercraft::process(float timeSince) {
	if (mMovingStatus && (timeSince > 0.0f) && (mNode->getRole() == eZCom_RoleAuthority)) {
		Ogre::Vector3 accumulatedDirection = Ogre::Vector3::ZERO;
		float accumulatedRotation = 0.0f;
		
		// calculate new direction
		if (mMovingStatus->moveLeft()) { accumulatedRotation += 0.01f; }
		if (mMovingStatus->moveRight()) { accumulatedRotation -= 0.01f; }

		Ogre::Quaternion quat = Ogre::Quaternion(Ogre::Radian(Ogre::Real(accumulatedRotation)), Ogre::Vector3::UNIT_Y);
		changeOrientation(quat);

		// move forward and/or backward
		if (mMovingStatus->moveForward()) { accumulatedDirection += getOrientation(); }
		if (mMovingStatus->moveBackward()) { accumulatedDirection -= getOrientation(); }
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