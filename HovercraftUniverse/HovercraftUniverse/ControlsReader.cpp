#include "ControlsReader.h"
#include "KeyManager.h"
#include "inifile.h"
#include <boost/algorithm/string.hpp>


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

void ControlsReader::setKeys(ControllerActions::ControllerActionType action, std::string keys, std::string defaultValue) {
	KeyManager * keyManager = mInputManager->getKeyManager();
	
	std::vector<std::string> strs;
	boost::split(strs, keys, boost::is_any_of(","));
	if (strs.size() == 0) {
		keyManager->setKey(action, defaultValue);
	} else {
		for (unsigned int i = 0; i < strs.size(); ++i) {
			keyManager->setKey(action, strs[i]);
		}
	}
}

void ControlsReader::setKeys(CameraActions::CameraControllerActionType action, std::string keys, std::string defaultValue) {
	KeyManager * keyManager = mInputManager->getKeyManager();
	
	std::vector<std::string> strs;
	boost::split(strs, keys, boost::is_any_of(","));
	if (strs.size() == 0) {
		keyManager->setCameraKey(action, defaultValue);
	} else {
		for (unsigned int i = 0; i < strs.size(); ++i) {
			keyManager->setCameraKey(action, strs[i]);
		}
	}
}

void ControlsReader::readControls() {
	KeyManager * keys = mInputManager->getKeyManager();
	std::string controlINI = mInputManager->getControlsFile();

	CIniFile reader;
	bool readerSuccess = reader.Load(controlINI);
	
	setKeys(ControllerActions::ACCELERATE, reader.GetKeyValue("Movement", "Accelerate"), "KC_UP");
	setKeys(ControllerActions::BRAKE, reader.GetKeyValue("Movement", "Brake"), "KC_DOWN");
	setKeys(ControllerActions::TURNLEFT, reader.GetKeyValue("Movement", "Turnleft"), "KC_LEFT");
	setKeys(ControllerActions::TURNRIGHT, reader.GetKeyValue("Movement", "Turnright"), "KC_RIGHT");

	setKeys(CameraActions::CHANGECAMERA, reader.GetKeyValue("Camera", "Changecamera"), "KC_C");
	setKeys(CameraActions::THIRD_PERSON_CAMERA, reader.GetKeyValue("Camera", "Thirdperson"), "KC_1");
	setKeys(CameraActions::FIRST_PERSON_CAMERA, reader.GetKeyValue("Camera", "Firstperson"), "KC_2");
	setKeys(CameraActions::REAR_VIEW_CAMERA, reader.GetKeyValue("Camera", "Rearview"), "KC_3");
	setKeys(CameraActions::FREE_CAMERA, reader.GetKeyValue("Camera", "Freeroam"), "KC_4");

	setKeys(CameraActions::FREE_CAMERA_FWD, reader.GetKeyValue("FreeCamera", "Forward"), "KC_W");
	setKeys(CameraActions::FREE_CAMERA_BACK, reader.GetKeyValue("FreeCamera", "Back"), "KC_S");
	setKeys(CameraActions::FREE_CAMERA_LEFT, reader.GetKeyValue("FreeCamera", "Left"), "KC_A");
	setKeys(CameraActions::FREE_CAMERA_RIGHT, reader.GetKeyValue("FreeCamera", "Right"), "KC_D");
	setKeys(CameraActions::FREE_CAMERA_UP, reader.GetKeyValue("FreeCamera", "Up"), "KC_E");
	setKeys(CameraActions::FREE_CAMERA_DOWN, reader.GetKeyValue("FreeCamera", "Down"), "KC_Q");
}

void ControlsReader::writeControls() {
	KeyManager * keys = mInputManager->getKeyManager();
	std::string controlINI = mInputManager->getControlsFile();

	// TODO: write INI
}

}
