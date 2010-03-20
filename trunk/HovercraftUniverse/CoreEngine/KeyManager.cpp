#include "KeyManager.h"
#include <utility>
#include <algorithm>

namespace HovUni {

KeyManager::KeyManager(void) {
	// TODO: for now hardcoded keys...
	/*
	mKeyMapping[OIS::KC_UP] = ACCELERATE;
	mKeyMapping[OIS::KC_DOWN] = BRAKE;
	mKeyMapping[OIS::KC_LEFT] = TURNLEFT;
	mKeyMapping[OIS::KC_RIGHT] = TURNRIGHT;

	mKeyMapping[OIS::KC_NUMPAD8] = ACCELERATE;
	mKeyMapping[OIS::KC_NUMPAD2] = BRAKE;
	mKeyMapping[OIS::KC_NUMPAD4] = TURNLEFT;
	mKeyMapping[OIS::KC_NUMPAD6] = TURNRIGHT;

	mKeyMapping[OIS::KC_C] = CHANGECAMERA;
	mKeyMapping[OIS::KC_1] = THIRD_PERSON_CAMERA;
	mKeyMapping[OIS::KC_2] = FIRST_PERSON_CAMERA;
	mKeyMapping[OIS::KC_3] = REAR_VIEW_CAMERA;
	mKeyMapping[OIS::KC_4] = FREE_CAMERA;
	mKeyMapping[OIS::KC_W] = FREE_CAMERA_FWD;
	mKeyMapping[OIS::KC_S] = FREE_CAMERA_BACK;
	mKeyMapping[OIS::KC_A] = FREE_CAMERA_LEFT;
	mKeyMapping[OIS::KC_D] = FREE_CAMERA_RIGHT;
	mKeyMapping[OIS::KC_E] = FREE_CAMERA_UP;
	mKeyMapping[OIS::KC_Q] = FREE_CAMERA_DOWN;
	*/
}

KeyManager::~KeyManager(void) {
}

void KeyManager::registerAction(const int action, const char * name) {
	mActionMapping[action] = name;
}

const std::list<OIS::KeyCode> KeyManager::getKeys(const int action) {
	std::list<OIS::KeyCode> keys;

    std::map<OIS::KeyCode, int>::const_iterator iter;
    for (iter = mKeyMapping.begin(); iter != mKeyMapping.end(); ++iter) {
        if (iter->second == action) {
            keys.push_back(iter->first);
        }
    }

    return keys;
}

void KeyManager::setKey(const int action, const OIS::KeyCode key) {
	mKeyMapping[key] = action;
}

const int KeyManager::getAction(const OIS::KeyCode key) {
	return mKeyMapping[key];
}

const char* KeyManager::getName(const int action) {
	return mActionMapping[action];
}

}