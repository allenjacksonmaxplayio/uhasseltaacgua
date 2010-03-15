#include "Entity.h"
#include "EntityManager.h"
#include "ControllerEventParser.h"
#include <cassert>
#include <OgreLogManager.h>

namespace HovUni {

class EntityManager;

Entity::Entity(Ogre::String name, Ogre::String category, bool track, Ogre::Vector3 position, Ogre::Vector3 orientation, Ogre::Vector3 upvector, Ogre::String ogreentity, float processInterval, unsigned short replicators) : 
		NetworkEntity(replicators + 2), mName(name), mCategory(category), mOgreEntity(ogreentity), mController(0), mProcessInterval(processInterval), 
		mProcessElapsed(processInterval) {
	if (track) {
		// Track this entity
		EntityManager::getClientSingletonPtr()->trackEntity(mName);
	}

	// Update data
	changePosition(position);
	changeOrientation(orientation.getRotationTo(Ogre::Vector3::UNIT_Z));
	changeOrientation(upvector.getRotationTo(Ogre::Vector3::UNIT_Y));
}

Entity::Entity(Ogre::String name, Ogre::String category, bool track, Ogre::Vector3 position, Ogre::Quaternion orientation, Ogre::String ogreentity, float processInterval, unsigned short replicators) : 
		NetworkEntity(replicators + 2), mName(name), mCategory(category), mOgreEntity(ogreentity), mController(0), mProcessInterval(processInterval), 
		mProcessElapsed(processInterval) {
	if (track) {
		// Track this entity
		EntityManager::getClientSingletonPtr()->trackEntity(mName);
	}

	// Update data
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

void Entity::changeOrientation(Ogre::Quaternion newOrientation) {
	// TODO Check whether valid

	// Set new orientation
	mOrientation = newOrientation * mOrientation;
}

void Entity::setController(Controller * controller) {
	// TODO Check whether valid

	// Set controller
	mController = controller;
	mController->setEntity(this);
}

void Entity::update(float timeSince) {

	// Process the network entity
	NetworkEntity::processEvents(timeSince);

	// Process controller
	processController(timeSince);

	if (mProcessInterval != -1) {
		mProcessElapsed -= timeSince;
		// Fire callback to process entity specific
		float since = mProcessInterval - mProcessElapsed;
		while (mProcessElapsed <= 0.0f) {
			process(since);
			mProcessElapsed += mProcessInterval;
			since = 0.0f;
		}
	}
}

Ogre::String Entity::getName() const { 
	return mName;
}

Ogre::String Entity::getCategory() const { 
	return mCategory;
}

Ogre::Vector3 Entity::getPosition() const { 
	return mPosition; 
}

Ogre::Vector3 Entity::getUpVector() const { 
	return mOrientation * Ogre::Vector3::UNIT_Y; 
}

Ogre::Vector3 Entity::getOrientation() const {
	return mOrientation * Ogre::Vector3::UNIT_Z;
}

Ogre::String Entity::getOgreEntity() const {
	return mOgreEntity;
}

Ogre::Quaternion Entity::getQuaternion() const {
	return mOrientation;
}

void Entity::parseEvents(ZCom_BitStream* stream, float timeSince) {
	ControllerEventParser p;
	ControllerEvent* event = p.parse(stream);
	processControllerEvents(event);
	delete event;
}

void Entity::processController(float timeSince) {
	if (mController) {
		// Get events from controller
		std::vector<ControllerEvent*> events = mController->getEvents();
	
		// Send the events
		for (std::vector<ControllerEvent*>::iterator it = events.begin(); it != events.end(); ++it) {
			ControllerEvent* event = *it;
			if (isRegistered()) {
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
			processEventsServer(event);
			Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "Processed for server";
			break;
		case eZCom_RoleOwner:
			Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "Event for owner";
			processEventsOwner(event);
			break;
		case eZCom_RoleProxy:
			processEventsOther(event);
			break;
		default:
			break;
	}
}

void Entity::setupReplication() {
	//TODO: min and max delay should be defined, not magic number...
	replicateOgreVector3(&mPosition);
	replicateOgreQuaternion(&mOrientation);
}

}