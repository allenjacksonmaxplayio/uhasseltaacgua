#include "KeyMapper.h"
#include <utility>

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

std::list<OIS::KeyCode> KeyMapper::getKey(const ControllerActionType action) {
	return mMapping[action];
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

const char* KeyMapper::getAction(const ControllerActionType action) {
	return actionNames[action];
}

}