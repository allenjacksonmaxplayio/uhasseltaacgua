#include "DummyHovercraftPlayerController.h"
#include "KeyManager.h"
#include <OgreLogManager.h>

namespace HovUni {

DummyHovercraftPlayerController::DummyHovercraftPlayerController(void) : mMovingLeft(false), mMovingForward(false),
		mMovingRight(false), mMovingBackward(false) {
	// Fetch input manager object
	mInputManager = InputManager::getSingletonPtr();
	mInputManager->addKeyListener(this, "DummyHovercraftPlayerController");
}

DummyHovercraftPlayerController::~DummyHovercraftPlayerController(void) {
	// Remove key listener from controller
	mInputManager->removeKeyListener("DummyHovercraftPlayerController");
}

Ogre::Vector3 DummyHovercraftPlayerController::getDirection() {
	// Process moves
	Ogre::Vector3 accumulatedDirection = Ogre::Vector3::ZERO;
	if (mMovingLeft) { accumulatedDirection += Ogre::Vector3(-1.0, 0.0, 0.0); }
	if (mMovingForward) { accumulatedDirection += Ogre::Vector3(0.0, 0.0, -1.0); }
	if (mMovingRight) { accumulatedDirection += Ogre::Vector3(1.0, 0.0, 0.0); }
	if (mMovingBackward) { accumulatedDirection += Ogre::Vector3(0.0, 0.0, 1.0); }

	// No movement
	return accumulatedDirection.normalisedCopy();
}

Ogre::Vector3 DummyHovercraftPlayerController::getOrientationChange() {
	// TODO Process keyboard
	// TODO Return results
	return Ogre::Vector3(0.0, 0.0, 0.0);
}

bool DummyHovercraftPlayerController::keyPressed(const OIS::KeyEvent & e) { 
	// Process possibly resulting move
	ControllerActionType action = mInputManager->getKeyManager()->getAction(e.key);
	switch (action) {
		case ACCELERATE:
			mMovingForward = true;
			break;
		case BRAKE:
			mMovingBackward = true;
			break;
		case TURNLEFT:
			mMovingLeft = true;
			break;
		case TURNRIGHT:
			mMovingRight = true;
			break;
		default:
			break;
	}
	
	// Succes
	return true; 
}

bool DummyHovercraftPlayerController::keyReleased(const OIS::KeyEvent & e) { 
	ControllerActionType action = mInputManager->getKeyManager()->getAction(e.key);
	// Clear movement for that key
	switch (action) {
		case ACCELERATE:
			mMovingForward = false;
			break;
		case BRAKE:
			mMovingBackward = false;
			break;
		case TURNLEFT:
			mMovingLeft = false;
			break;
		case TURNRIGHT:
			mMovingRight = false;
			break;
		default:
			break;
	}

	// Succes
	return true; 
}

}