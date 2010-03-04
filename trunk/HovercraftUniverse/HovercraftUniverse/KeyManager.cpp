#include "KeyManager.h"
#include <utility>
#include <algorithm>

namespace HovUni {

KeyManager::KeyManager(void) {
	// TODO: for now hardcoded keys...
	mMapping[OIS::KC_UP] = ACCELERATE;
	mMapping[OIS::KC_DOWN] = BRAKE;
	mMapping[OIS::KC_LEFT] = TURNLEFT;
	mMapping[OIS::KC_RIGHT] = TURNRIGHT;

	mMapping[OIS::KC_NUMPAD8] = ACCELERATE;
	mMapping[OIS::KC_NUMPAD2] = BRAKE;
	mMapping[OIS::KC_NUMPAD4] = TURNLEFT;
	mMapping[OIS::KC_NUMPAD6] = TURNRIGHT;

	mMapping[OIS::KC_C] = CHANGECAMERA;
	mMapping[OIS::KC_1] = THIRD_PERSON_CAMERA;
	mMapping[OIS::KC_2] = FIRST_PERSON_CAMERA;
	mMapping[OIS::KC_3] = REAR_VIEW_CAMERA;
	mMapping[OIS::KC_4] = FREE_CAMERA;
	mMapping[OIS::KC_W] = FREE_CAMERA_FWD;
	mMapping[OIS::KC_S] = FREE_CAMERA_BACK;
	mMapping[OIS::KC_A] = FREE_CAMERA_LEFT;
	mMapping[OIS::KC_D] = FREE_CAMERA_RIGHT;
	mMapping[OIS::KC_E] = FREE_CAMERA_UP;
	mMapping[OIS::KC_Q] = FREE_CAMERA_DOWN;
	
}

KeyManager::~KeyManager(void) {
}

const std::list<OIS::KeyCode> KeyManager::getKeys(const ControllerActionType action) {
	std::list<OIS::KeyCode> keys;

    std::map<OIS::KeyCode, ControllerActionType>::const_iterator iter;
    for (iter = mMapping.begin(); iter != mMapping.end(); ++iter) {
        if (iter->second == action) {
            keys.push_back(iter->first);
        }
    }

    return keys;
}

void KeyManager::setKey(const ControllerActionType action, const OIS::KeyCode key) {
	mMapping[key] = action;
}

const ControllerActionType KeyManager::getAction(const OIS::KeyCode key) {
	return mMapping[key];
}

const char* KeyManager::getName(const ControllerActionType action) {
	return actionNames[action];
}

}