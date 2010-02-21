#include "DummyHovercraftPlayerController.h"
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
	if (mMovingLeft) { return Ogre::Vector3(-1.0, 0.0, 0.0); }
	if (mMovingForward) { return Ogre::Vector3(0.0, 0.0, -1.0); }
	if (mMovingRight) { return Ogre::Vector3(1.0, 0.0, 0.0); }
	if (mMovingBackward) { return Ogre::Vector3(0.0, 0.0, 1.0); }

	// No movement
	return Ogre::Vector3(0.0, 0.0, 0.0);
}

Ogre::Vector3 DummyHovercraftPlayerController::getOrientationChange() {
	// TODO Process keyboard
	// TODO Return results
	return Ogre::Vector3(0.0, 0.0, 0.0);
}

bool DummyHovercraftPlayerController::keyPressed(const OIS::KeyEvent & e) { 
	// Process possibly resulting move
	switch (e.key) {
		case OIS::KC_LEFT:
			mMovingLeft = true;
			break;
		case OIS::KC_UP:
			mMovingForward = true;
			break;
		case OIS::KC_RIGHT:
			mMovingRight = true;
			break;
		case OIS::KC_DOWN:
			mMovingBackward = true;
			break;
		default:
			break;
	}
	
	// Succes
	return true; 
}

bool DummyHovercraftPlayerController::keyReleased(const OIS::KeyEvent & e) { 
	// Clear movement for that key
	switch (e.key) {
	case OIS::KC_LEFT:
		mMovingLeft = false;
		break;
	case OIS::KC_UP:
		mMovingForward = false;
		break;
	case OIS::KC_RIGHT:
		mMovingRight = false;
		break;
	case OIS::KC_DOWN:
		mMovingBackward = false;
		break;
	default:
		break;
	}

	// Succes
	return true; 
}

}