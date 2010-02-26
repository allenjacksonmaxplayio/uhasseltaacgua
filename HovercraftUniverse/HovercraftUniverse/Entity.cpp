#include "Entity.h"
#include "ControllerEventParser.h"
#include <cassert>
#include <OgreLogManager.h>

namespace HovUni {

Entity::Entity(Ogre::String name, Ogre::String category, Ogre::Vector3 position, Ogre::Vector3 orientation) : 
		mName(name), mCategory(category), mController(0), mRegistered(false) {
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
}

void Entity::networkRegister(ZCom_ClassID id, ZCom_Control* control) {
	mNode->registerNodeDynamic(id, control);
	mRegistered = true;
}

void Entity::parseEvents(ZCom_BitStream* stream) {
	ControllerEventParser p;
	ControllerEvent* event = p.parse(stream);
	processControllerEvents(event);
}

void Entity::processController(Ogre::Real timeSinceLastFrame) {
	if (mController) {
		// Get events from controller
		std::vector<ControllerEvent*> events = mController->getEvents();
	
		// Send the events
		for (std::vector<ControllerEvent*>::iterator it = events.begin(); it != events.end(); ++it) {
			ControllerEvent* event = *it;
			event->setTimeSinceLastFrame(timeSinceLastFrame);
			if (mRegistered) {
				sendEvent(*event);
			} else {
				processControllerEvents(event);
			}
		}
	}
}

void Entity::processControllerEvents(ControllerEvent* event) {
	eZCom_NodeRole role = mNode->getRole();
	switch (role) {
		case eZCom_RoleAuthority:
			Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "Event for server";
			processControllerEventsInServer(event);
			Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "Processed for server";
			break;
		case eZCom_RoleOwner:
			Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "Event for owner";
			processControllerEventsInOwner(event);
			break;
		case eZCom_RoleProxy:
			processControllerEventsInOther(event);
			break;
		default:
			break;
	}
}

}