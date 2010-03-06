#include "Entity.h"
#include "EntityManager.h"
#include "ControllerEventParser.h"
#include <cassert>
#include <OgreLogManager.h>

namespace HovUni {

class EntityManager;

Entity::Entity(Ogre::String name, Ogre::String category, bool track, Ogre::Vector3 position, Ogre::Vector3 orientation, float processInterval) : 
		NetworkEntity(1), mName(name), mCategory(category), mController(0), mProcessInterval(processInterval), 
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
	mPosition[0] = newPosition.x;
	mPosition[1] = newPosition.y;
	mPosition[2] = newPosition.z;
}

void Entity::changeOrientation(Ogre::Vector3 newOrientation) {
	// TODO Check whether valid

	// Set new orientation
	mOrientation[0] = newOrientation.x;
	mOrientation[1] = newOrientation.y;
	mOrientation[2] = newOrientation.z;
}

void Entity::setController(Controller * controller) {
	// TODO Check whether valid

	// Set controller
	mController = controller;
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

void Entity::networkRegister(ZCom_ClassID id, ZCom_Control* control) {
	// Register to network
	NetworkEntity::networkRegister(id, control);
}

void Entity::parseEvents(ZCom_BitStream* stream, float timeSince) {
	ControllerEventParser p;
	ControllerEvent* event = p.parse(stream);
	processControllerEvents(event);
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
	// Create the position replicator
	ZCom_Replicate_Numeric<zFloat*, 3> *repnum = new ZCom_Replicate_Numeric<zFloat*, 3>(mPosition, 23, ZCOM_REPFLAG_MOSTRECENT, ZCOM_REPRULE_AUTH_2_ALL);
	mNode->addReplicator(repnum, true);
}

}