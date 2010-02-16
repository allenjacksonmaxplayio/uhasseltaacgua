#include "Entity.h"

namespace HovUni {

Entity::Entity(Ogre::Vector3 position, Ogre::Vector3 orientation, Controller * controller) : mController(controller) {
	changePosition(position);
	changeOrientation(orientation);
}

Entity::~Entity() {

}

void Entity::changePosition(Ogre::Vector3 newPosition) {
	// TODO Check whether valid
	// TODO Set new position
}

void Entity::changeOrientation(Ogre::Vector3 newOrientation) {
	// TODO Check whether valid
	// TODO Set new orientation
}

void Entity::setController(Controller * controller) {
	// TODO Check whether valid
	// TODO Set controller
}

void Entity::update() {
	// TODO Process controller
}

void Entity::processController() {
	// TODO Check status controller
	// TODO Perform operations on entity according to status controller
}

}