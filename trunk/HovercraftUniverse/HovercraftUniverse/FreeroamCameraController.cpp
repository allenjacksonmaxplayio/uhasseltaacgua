#include "FreeroamCameraController.h"
#include <OgreLogManager.h>

namespace HovUni {

FreeroamCameraController::FreeroamCameraController() : mMovingLeft(false), mMovingForward(false),
		mMovingRight(false), mMovingBackward(false), mMovingUp(false), mMovingDown(false), mMouseRelativeX(0.0),
		mMouseRelativeY(0.0) {
	// Fetch input manager object and add listeners
	mInputManager = InputManager::getSingletonPtr();
	mInputManager->addKeyListener(this, "FreeroamCameraController");
	mInputManager->addMouseListener(this, "FreeroamCameraController");
}

FreeroamCameraController::~FreeroamCameraController() {
	// Remove listeners from controller
	mInputManager->removeKeyListener("FreeroamCameraController");
	mInputManager->removeMouseListener("FreeroamCameraController");
}

std::vector<ControllerEvent*> FreeroamCameraController::getEvents() {
	// These events are really not interesting for network transfer and thus, this method should not be called
	assert (false);

	// Return empty vector
	return std::vector<ControllerEvent*>();
}

Ogre::Vector3 FreeroamCameraController::getDirection() {
	// Process moves
	Ogre::Vector3 accumulatedDirection = Ogre::Vector3::ZERO;
	if (mMovingLeft) { accumulatedDirection += Ogre::Vector3(-1.0, 0.0, 0.0); }
	if (mMovingForward) { accumulatedDirection += Ogre::Vector3(0.0, 0.0, -1.0); }
	if (mMovingRight) { accumulatedDirection += Ogre::Vector3(1.0, 0.0, 0.0); }
	if (mMovingBackward) { accumulatedDirection += Ogre::Vector3(0.0, 0.0, 1.0); }
	if (mMovingUp) { accumulatedDirection += Ogre::Vector3(0.0, 1.0, 0.0); }
	if (mMovingDown) { accumulatedDirection += Ogre::Vector3(0.0, -1.0, 0.0); }

	// No movement
	return accumulatedDirection.normalisedCopy();
}

Ogre::Degree FreeroamCameraController::getYaw() {
	// Relative X to return
	Ogre::Real mouseRelativeX = mMouseRelativeX;

	// Clear relative X
	mMouseRelativeX = 0.0;

	// Return yaw
	return Ogre::Degree((Ogre::Real) -0.13 * mouseRelativeX);
}

Ogre::Degree FreeroamCameraController::getPitch() {
	// Relative Y to return
	Ogre::Real mouseRelativeY = mMouseRelativeY;

	// Clear relative Y
	mMouseRelativeY = 0.0;

	// Return pitch
	return Ogre::Degree((Ogre::Real) -0.13 * mouseRelativeY);
}

bool FreeroamCameraController::keyPressed(const OIS::KeyEvent & e) { 
	// Process possibly resulting move
	switch (e.key) {
		case OIS::KC_A:
			mMovingLeft = true;
			break;
		case OIS::KC_W:
			mMovingForward = true;
			break;
		case OIS::KC_D:
			mMovingRight = true;
			break;
		case OIS::KC_S:
			mMovingBackward = true;
			break;
		case OIS::KC_E:
			mMovingUp = true;
			break;
		case OIS::KC_Q:
			mMovingDown = true;
			break;
		default:
			break;
	}
	
	// Succes
	return true; 
}

bool FreeroamCameraController::keyReleased(const OIS::KeyEvent & e) { 
	// Clear movement for that key
	switch (e.key) {
		case OIS::KC_A:
			mMovingLeft = false;
			break;
		case OIS::KC_W:
			mMovingForward = false;
			break;
		case OIS::KC_D:
			mMovingRight = false;
			break;
		case OIS::KC_S:
			mMovingBackward = false;
			break;
		case OIS::KC_E:
			mMovingUp = false;
			break;
		case OIS::KC_Q:
			mMovingDown = false;
			break;
		default:
			break;
	}

	// Succes
	return true; 
}

bool FreeroamCameraController::mouseMoved(const OIS::MouseEvent & e) { 
	// Handle mouse movements of camera
	mMouseRelativeX += mInputManager->getMouse()->getMouseState().X.rel;
	mMouseRelativeY += mInputManager->getMouse()->getMouseState().Y.rel;

	return true; 
}

bool FreeroamCameraController::mousePressed(const OIS::MouseEvent & e, OIS::MouseButtonID id) { 
	return true;
}
bool FreeroamCameraController::mouseReleased(const OIS::MouseEvent & e, OIS::MouseButtonID id) { 
	return true; 
}

}