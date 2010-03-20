#include "KeyManager.h"
#include <utility>
#include <algorithm>

namespace HovUni {

KeyManager::KeyManager(void) {
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

const std::list<int> KeyManager::getRegisteredActions() {
	std::list<int> actions;

    std::map<int, const char *>::const_iterator iter;
    for (iter = mActionMapping.begin(); iter != mActionMapping.end(); ++iter) {
        actions.push_back(iter->first);
    }

    return actions;
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