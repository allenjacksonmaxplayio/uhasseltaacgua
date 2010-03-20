#include "ObjectTrackCameraController.h"
#include "EntityManager.h"
#include <OgreLogManager.h>

class EntityManager;

namespace HovUni {

ObjectTrackCameraController::ObjectTrackCameraController() : mEntity(0) {
	// All initialized
}

ObjectTrackCameraController::~ObjectTrackCameraController() {
	// Empty
}

std::vector<ControllerEvent*> ObjectTrackCameraController::getEvents() {
	// These events are really not interesting for network transfer and thus, this method should not be called
	assert (false);

	// Return empty vector
	return std::vector<ControllerEvent*>();
}

Ogre::Vector3 ObjectTrackCameraController::getPosition() {
	initialize();
	if (mEntity) {
		return mEntity->getPosition();
	} else {
		// Return default value
		return Ogre::Vector3::ZERO;
	}
}

Ogre::Vector3 ObjectTrackCameraController::getDirection() {
	initialize();
	if (mEntity) {
		return mEntity->getOrientation();
	} else {
		// Return default value
		return Ogre::Vector3::NEGATIVE_UNIT_Z;
	}
}

Ogre::Quaternion ObjectTrackCameraController::getOrientation() {
	initialize();
	if (mEntity) {
		return mEntity->getQuaternion();
	} else {
		// Return default value
		return Ogre::Quaternion::IDENTITY;
	}
}

Ogre::Vector3 ObjectTrackCameraController::getUpVector() {
	initialize();
	// TODO Make sure the up vector can change
	if (mEntity) {
		return mEntity->getUpVector();
	} else {
		// Return default value
		return Ogre::Vector3::UNIT_Y;
	}
}

void ObjectTrackCameraController::initialize() {
	if (!mEntity) {
		// Get tracked entity
		mEntity = EntityManager::getClientSingletonPtr()->getTrackedEntity();
	}
}

}