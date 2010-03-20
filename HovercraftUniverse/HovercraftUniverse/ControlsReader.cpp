#include "ControlsReader.h"
#include "KeyManager.h"
#include "CameraControllerActionType.h"
#include "ControllerActionType.h"

namespace HovUni {

ControlsReader::ControlsReader(InputManager * ipm): mInputManager(ipm) {
	KeyManager * keys = mInputManager->getKeyManager();
	
	// register actions
	for (int i = 0; i < ControllerActions::ACTIONS_END; ++i) {
		keys->registerAction(i, ControllerActions::actionNames[i]);
	}
}

ControlsReader::~ControlsReader(void) {

}

void ControlsReader::setDefaultControls() {
	KeyManager * keys = mInputManager->getKeyManager();
	
	// ACCELERATE
	keys->setKey(ControllerActions::ACCELERATE, OIS::KC_UP);
	keys->setKey(ControllerActions::ACCELERATE, OIS::KC_NUMPAD8);

	// BRAKE
	keys->setKey(ControllerActions::BRAKE, OIS::KC_DOWN);
	keys->setKey(ControllerActions::BRAKE, OIS::KC_NUMPAD2);

	// TURN LEFT
	keys->setKey(ControllerActions::TURNLEFT, OIS::KC_LEFT);
	keys->setKey(ControllerActions::TURNLEFT, OIS::KC_NUMPAD4);

	// TURN RIGHT
	keys->setKey(ControllerActions::TURNRIGHT, OIS::KC_RIGHT);
	keys->setKey(ControllerActions::TURNRIGHT, OIS::KC_NUMPAD6);

	// CAMERA
	keys->setCameraKey(CameraActions::CHANGECAMERA, OIS::KC_C);
	keys->setCameraKey(CameraActions::CHANGECAMERA, OIS::KC_V);

	keys->setCameraKey(CameraActions::THIRD_PERSON_CAMERA, OIS::KC_1);
	keys->setCameraKey(CameraActions::FIRST_PERSON_CAMERA, OIS::KC_2);
	keys->setCameraKey(CameraActions::REAR_VIEW_CAMERA, OIS::KC_3);
	keys->setCameraKey(CameraActions::FREE_CAMERA, OIS::KC_4);

	keys->setCameraKey(CameraActions::FREE_CAMERA_FWD, OIS::KC_W);
	keys->setCameraKey(CameraActions::FREE_CAMERA_BACK, OIS::KC_S);
	keys->setCameraKey(CameraActions::FREE_CAMERA_LEFT, OIS::KC_A);
	keys->setCameraKey(CameraActions::FREE_CAMERA_RIGHT, OIS::KC_D);
	keys->setCameraKey(CameraActions::FREE_CAMERA_UP, OIS::KC_E);
	keys->setCameraKey(CameraActions::FREE_CAMERA_DOWN, OIS::KC_Q);
}

void ControlsReader::readControls() {
	//TODO: read ini file
}

}
