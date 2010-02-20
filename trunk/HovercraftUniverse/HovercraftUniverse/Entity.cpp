#include "Entity.h"
#include <cassert>

namespace HovUni {

Entity::Entity(Ogre::String name, Ogre::String category, Ogre::Vector3 position, Ogre::Vector3 orientation, 
			   Controller * controller) : mName(name), mCategory(category), mController(controller) {
	changePosition(position);
	changeOrientation(orientation);
}

Entity::~Entity() {
	// Empty
}

void Entity::changePosition(Ogre::Vector3 newPosition) {
	// TODO Check whether valid

	// Set new position
	mPosition = newPosition;
}

void Entity::changeOrientation(Ogre::Vector3 newOrientation) {
	// TODO Check whether valid

	// Set new orientation
	mOrientation = newOrientation;
}

void Entity::setController(Controller * controller) {
	// TODO Check whether valid

	// Set controller
	mController = controller;
}

void Entity::update(Ogre::Real timeSinceLastFrame) {
	// Process controller
	processController(timeSinceLastFrame);

	// TODO Synchronize network
	// TODO ...
}

}