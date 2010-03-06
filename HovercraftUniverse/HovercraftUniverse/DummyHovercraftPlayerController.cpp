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

bool DummyHovercraftPlayerController::moveForward() const {
	return mMovingForward;
}

bool DummyHovercraftPlayerController::moveBackward() const {
	return mMovingBackward;
}

bool DummyHovercraftPlayerController::moveLeft() const {
	return mMovingLeft;
}

bool DummyHovercraftPlayerController::moveRight() const {
	return mMovingRight;
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