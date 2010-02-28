#include "KeyMapper.h"
#include <utility>
#include <algorithm>

namespace HovUni {

KeyMapper::KeyMapper(void) {
	// TODO: for now hardcoded keys...
	std::list<OIS::KeyCode> accelKeys;
	accelKeys.push_back(OIS::KC_UP);
	accelKeys.push_back(OIS::KC_Z);

	std::list<OIS::KeyCode> brakeKeys;
	brakeKeys.push_back(OIS::KC_DOWN);
	brakeKeys.push_back(OIS::KC_S);

	std::list<OIS::KeyCode> leftKeys;
	leftKeys.push_back(OIS::KC_LEFT);
	leftKeys.push_back(OIS::KC_Q);

	std::list<OIS::KeyCode> rightKeys;
	rightKeys.push_back(OIS::KC_UP);
	rightKeys.push_back(OIS::KC_D);

	std::list<OIS::KeyCode> camKeys;
	camKeys.push_back(OIS::KC_V);

	mMapping[ACCELERATE] = accelKeys;
	mMapping[BRAKE] = brakeKeys;
	mMapping[TURNLEFT] = leftKeys;
	mMapping[TURNRIGHT] = rightKeys;
	mMapping[CHANGECAMERA] = camKeys;
}

KeyMapper::~KeyMapper(void) {
}

const std::list<OIS::KeyCode>& KeyMapper::getKey(const ControllerActionType action) {
	std::list<OIS::KeyCode> &keys = mMapping[action];
	return keys;
}

void KeyMapper::setKey(const ControllerActionType action, const OIS::KeyCode key) {
	// first check if this key is used somewhere else and remove it there
	std::map<ControllerActionType, std::list<OIS::KeyCode> >::const_iterator iter;
    for (iter = mMapping.begin(); iter != mMapping.end(); ++iter) {
		std::list<OIS::KeyCode> keys = iter->second;
		keys.remove(key);
    }

	// now add the new key
	mMapping[action].push_back(key);


}

const ControllerActionType KeyMapper::getAction(const OIS::KeyCode key) {
	std::map<ControllerActionType, std::list<OIS::KeyCode> >::const_iterator iter;
    for (iter = mMapping.begin(); iter != mMapping.end(); ++iter) {
		std::list<OIS::KeyCode> keys = iter->second;
		if (std::find(keys.begin(), keys.end(), key) != keys.end()) {
			// the key is in this list
			return iter->first;
		}
    }

	// no action was found
	return INVALID;
}

const char* KeyMapper::getName(const ControllerActionType action) {
	return actionNames[action];
}

}