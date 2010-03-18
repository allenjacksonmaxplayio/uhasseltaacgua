#include "DummyHovercraft.h"
#include "DummyHovercraftController.h"
#include "DummyHovercraftPlayerController.h"
#include "BasicEntityEvent.h"
#include <OgreLogManager.h>

namespace HovUni {

DummyHovercraft::DummyHovercraft(void) : Entity("hovercraft", "vehicles", true, Ogre::Vector3(0.0, 4.0, 0.0), 
												Ogre::Vector3(1.0, 0.0,-1.0),Ogre::Vector3(0.0, 1.0, 0.0),"", 1.0f / 60.0f,0), mMovingStatus(0), mTilt(0.0f), mSpeed(0.0f) {
	// Already initialized
}

DummyHovercraft::~DummyHovercraft(void) {
	// Empty
}

void DummyHovercraft::process(float timeSince) {
	if (mMovingStatus && (timeSince > 0.0f) && (mNode->getRole() == eZCom_RoleAuthority)) {
		float accumulatedRotation = 0.0f;
		float accumulatedTilt = mTilt;
		

		// calculate new direction
		if (mMovingStatus->moveLeft()) { 
			// check direction, we won't allow turning without moving
			if (mMovingStatus->moveForward()) {
				accumulatedRotation += 2.0f;
			} else if (mMovingStatus->moveBackward()) {
				accumulatedRotation -= 2.0f;
			}
			// set tilt
			if ((mMovingStatus->moveForward() || mMovingStatus->moveBackward()) && mTilt > -20.0f) {
				mTilt -= 0.5f;
				if (mTilt > 0.5f) {
					mTilt -= 1.0f;
				}
			}
		}
		if (mMovingStatus->moveRight()) { 
			// check direction, we won't allow turning without moving
			if (mMovingStatus->moveForward()) {
				accumulatedRotation -= 2.0f;
			} else if (mMovingStatus->moveBackward()) {
				accumulatedRotation += 2.0f;
			}
			// set tilt
			if ((mMovingStatus->moveForward() || mMovingStatus->moveBackward()) && mTilt < 20.0f) {
				mTilt += 0.5f;
				if (mTilt < -0.5f) {
					mTilt += 1.0f;
				}
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
			mSpeed += 0.5f;
		}
		if (mMovingStatus->moveBackward()) { 
			mSpeed -= 0.8f;
		}
		// limit speed to 30
		if (mSpeed > 30.0f) {
			mSpeed = 30.0f;
		} else if (mSpeed < -10.0f) {
			mSpeed = -10.0f;
		}
		if (!mMovingStatus->moveForward() && !mMovingStatus->moveBackward()) {
			mSpeed *= 0.9f;
		}
	
		changePosition(getPosition() + getOrientation() * timeSince * mSpeed);
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