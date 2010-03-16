#include "DummyHovercraft.h"
#include "DummyHovercraftController.h"
#include "DummyHovercraftPlayerController.h"
#include "BasicEntityEvent.h"
#include <OgreLogManager.h>

namespace HovUni {

DummyHovercraft::DummyHovercraft(void) : Entity("hovercraft", "vehicles", true, Ogre::Vector3(0.0, 40.0, 0.0), 
												Ogre::Vector3(1.0, 0.0,-1.0),Ogre::Vector3(0.0, 1.0, 0.0),"", 1.0f / 60.0f,0), mMovingStatus(0), mTilt(0.0f) {
	// Already initialized
}

DummyHovercraft::~DummyHovercraft(void) {
	// Empty
}

void DummyHovercraft::process(float timeSince) {
	if (mMovingStatus && (timeSince > 0.0f) && (mNode->getRole() == eZCom_RoleAuthority)) {
		Ogre::Vector3 accumulatedDirection = Ogre::Vector3::ZERO;
		float accumulatedRotation = 0.0f;
		float accumulatedTilt = mTilt;
		

		// calculate new direction
		if (mMovingStatus->moveLeft()) { 
			// check direction, we won't allow turning without moving
			if (mMovingStatus->moveForward()) {
				accumulatedRotation += 1.0f;
			} else if (mMovingStatus->moveBackward()) {
				accumulatedRotation -= 1.0f;
			}
			// set tilt
			if ((mMovingStatus->moveForward() || mMovingStatus->moveBackward()) && mTilt > -20.0f) {
				mTilt -= 0.5f;
			}
		}
		if (mMovingStatus->moveRight()) { 
			// check direction, we won't allow turning without moving
			if (mMovingStatus->moveForward()) {
				accumulatedRotation -= 1.0f;
			} else if (mMovingStatus->moveBackward()) {
				accumulatedRotation += 1.0f;
			}
			// set tilt
			if ((mMovingStatus->moveForward() || mMovingStatus->moveBackward()) && mTilt < 20.0f) {
				mTilt += 0.5f;
			}
		}
		// if not turning, lower tilt
		if ((!mMovingStatus->moveLeft() && !mMovingStatus->moveRight()) || 
					((mMovingStatus->moveLeft() || mMovingStatus->moveRight()) && (!mMovingStatus->moveForward() && !mMovingStatus->moveBackward()))) {
			mTilt *= 0.9f;
		}
		

		// calculate orientation
		// TODO: Should be the UpVector, but in the tilt test this would give weird results...
		//Ogre::Quaternion quat = Ogre::Quaternion(Ogre::Degree(Ogre::Real(accumulatedRotation)), getUpVector());
		Ogre::Quaternion rotation = Ogre::Quaternion(Ogre::Degree(Ogre::Real(accumulatedRotation)), Ogre::Vector3::UNIT_Y);
		changeOrientation(rotation);

		//calculate tilt
		accumulatedTilt = mTilt - accumulatedTilt;
		Ogre::Quaternion tilt = Ogre::Quaternion(Ogre::Degree(Ogre::Real(accumulatedTilt)), getOrientation());
		changeOrientation(tilt);

		

		// move forward and/or backward
		if (mMovingStatus->moveForward()) { 
			accumulatedDirection += getOrientation(); 
		}
		if (mMovingStatus->moveBackward()) { 
			accumulatedDirection -= getOrientation(); 
		}
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