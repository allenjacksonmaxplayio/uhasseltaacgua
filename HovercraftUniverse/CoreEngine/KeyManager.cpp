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
	*/
	mCameraMapping[OIS::KC_C] = CameraActions::CHANGECAMERA;
	mCameraMapping[OIS::KC_1] = CameraActions::THIRD_PERSON_CAMERA;
	mCameraMapping[OIS::KC_2] = CameraActions::FIRST_PERSON_CAMERA;
	mCameraMapping[OIS::KC_3] = CameraActions::REAR_VIEW_CAMERA;
	mCameraMapping[OIS::KC_4] = CameraActions::FREE_CAMERA;
	mCameraMapping[OIS::KC_W] = CameraActions::FREE_CAMERA_FWD;
	mCameraMapping[OIS::KC_S] = CameraActions::FREE_CAMERA_BACK;
	mCameraMapping[OIS::KC_A] = CameraActions::FREE_CAMERA_LEFT;
	mCameraMapping[OIS::KC_D] = CameraActions::FREE_CAMERA_RIGHT;
	mCameraMapping[OIS::KC_E] = CameraActions::FREE_CAMERA_UP;
	mCameraMapping[OIS::KC_Q] = CameraActions::FREE_CAMERA_DOWN;
	
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
	mCameraMapping[key] = CameraActions::INVALID;
}

const int KeyManager::getAction(const OIS::KeyCode key) {
	return mKeyMapping[key];
}

const char* KeyManager::getName(const int action) {
	return mActionMapping[action];
}

const std::list<OIS::KeyCode> KeyManager::getCameraKeys(const CameraActions::CameraControllerActionType action) {
	std::list<OIS::KeyCode> keys;

    std::map<OIS::KeyCode, CameraActions::CameraControllerActionType>::const_iterator iter;
    for (iter = mCameraMapping.begin(); iter != mCameraMapping.end(); ++iter) {
        if (iter->second == action) {
            keys.push_back(iter->first);
        }
    }

    return keys;
}

void KeyManager::setCameraKey(const CameraActions::CameraControllerActionType action, const OIS::KeyCode key) {
	mKeyMapping[key] = 0;
	mCameraMapping[key] = action;
}

const CameraActions::CameraControllerActionType KeyManager::getCameraAction(const OIS::KeyCode key) {
	return mCameraMapping[key];
}

const char* KeyManager::getCameraName(const CameraActions::CameraControllerActionType action) {
	return CameraActions::cameraActionNames[action];
}

}