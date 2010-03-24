#include "Entity.h"
#include "EntityManager.h"
#include "ControllerEventParser.h"
#include <cassert>
#include <OgreLogManager.h>

namespace HovUni {

class EntityManager;

Entity::Entity(const Ogre::String& name, const Ogre::String& category, const Ogre::Vector3& position, const Ogre::Vector3& orientation, const Ogre::Vector3& upvector, const Ogre::String& ogreentity, float processInterval, unsigned short replicators) : 
		NetworkEntity(replicators + 3), mName(name), mCategory(category), mOgreEntity(ogreentity), mController(0), mProcessInterval(processInterval), 
			mProcessElapsed(processInterval), mVelocity(Ogre::Vector3::ZERO), mOrientation(Ogre::Quaternion::IDENTITY) {
	// Update data
	changePosition(position);
	changeOrientation(Ogre::Vector3::UNIT_Y.getRotationTo(upvector));
	changeOrientation(Ogre::Vector3::NEGATIVE_UNIT_Z.getRotationTo(orientation));
}

Entity::Entity(const Ogre::String& name, const Ogre::String& category, const Ogre::Vector3& position, const Ogre::Quaternion& orientation, const Ogre::String& ogreentity, float processInterval, unsigned short replicators) : 
		NetworkEntity(replicators + 3), mName(name), mCategory(category), mOgreEntity(ogreentity), mController(0), mProcessInterval(processInterval), 
		mProcessElapsed(processInterval), mVelocity(Ogre::Vector3::ZERO), mOrientation(Ogre::Quaternion::IDENTITY) {
	// Update data
	changePosition(position);
	changeOrientation(orientation);
}

Entity::Entity ( ZCom_BitStream* announcementdata, const Ogre::String& category, unsigned short replicators ): 
	NetworkEntity(replicators + 3), mController(0), mCategory(category), mVelocity(Ogre::Vector3::ZERO)
{
	//name and entity
	mName = Ogre::String(announcementdata->getString());
	mOgreEntity = Ogre::String(announcementdata->getString());

	//process info
	mProcessInterval = announcementdata->getFloat(10);
	mProcessElapsed = mProcessInterval;

	//position
	mPosition[0] = announcementdata->getFloat(10);
	mPosition[1] = announcementdata->getFloat(10);
	mPosition[2] = announcementdata->getFloat(10);
	
	//orientation
	mOrientation[0] = announcementdata->getFloat(10);
	mOrientation[1] = announcementdata->getFloat(10);
	mOrientation[2] = announcementdata->getFloat(10);
	mOrientation[3] = announcementdata->getFloat(10);
}


Entity::~Entity() {
	// Empty
}

void Entity::changePosition(const Ogre::Vector3& newPosition) {
	// TODO Check whether valid

	// Set new position
	mPosition = newPosition;
}

void Entity::changeVelocity(const Ogre::Vector3& newVelocity) {
	mVelocity = newVelocity;
}

void Entity::changeOrientation(const Ogre::Quaternion& newOrientation) {
	// TODO Check whether valid

	// Set new orientation
	mOrientation = newOrientation;
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

Ogre::Vector3 Entity::getVelocity() const { 
	return mVelocity; 
}

Ogre::Vector3 Entity::getUpVector() const { 
	return mOrientation * Ogre::Vector3::UNIT_Y; 
}

Ogre::Vector3 Entity::getOrientation() const {
	return mOrientation * Ogre::Vector3::NEGATIVE_UNIT_Z;
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
	replicateOgreVector3(&mVelocity);
}

void Entity::setAnnouncementData(ZCom_BitStream* stream) {
	stream->addString(mName.c_str());
	stream->addString(mOgreEntity.c_str());
	stream->addFloat(mProcessInterval,10);
	
	stream->addFloat(mPosition[0],10);
	stream->addFloat(mPosition[1],10);
	stream->addFloat(mPosition[2],10);

	stream->addFloat(mOrientation[0],10);
	stream->addFloat(mOrientation[1],10);
	stream->addFloat(mOrientation[2],10);
	stream->addFloat(mOrientation[3],10);
}

}