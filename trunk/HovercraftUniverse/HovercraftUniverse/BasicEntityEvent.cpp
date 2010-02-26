#include "BasicEntityEvent.h"
#include <OgreLogManager.h>

namespace HovUni {

BasicEntityEvent::BasicEntityEvent(Ogre::Vector3 direction, Ogre::Vector3 orientationchange) : 
	ControllerEvent(BasicEntity), mDirection(direction), mOrientation(orientationchange) {

}

BasicEntityEvent::~BasicEntityEvent() {

}

Ogre::Vector3 BasicEntityEvent::getDirection() const {
	return mDirection;
}

Ogre::Vector3 BasicEntityEvent::getOrientationChange() const {
	return mOrientation;
}

void BasicEntityEvent::write(ZCom_BitStream* stream) const {
	// Write information for controller event
	ControllerEvent::write(stream);

	// Write own information
	stream->addFloat(mDirection.x, 23);
	stream->addFloat(mDirection.y, 23);
	stream->addFloat(mDirection.z, 23);
	stream->addFloat(mOrientation.x, 23);
	stream->addFloat(mOrientation.y, 23);
	stream->addFloat(mOrientation.z, 23);
	Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "Write " << mDirection.x << " " << mDirection.y << " " << mDirection.z;
}

void BasicEntityEvent::read(ZCom_BitStream* stream) {
	// Read information for controller event
	ControllerEvent::read(stream);

	// Read own information
	mDirection.x = stream->getFloat(23);
	mDirection.y = stream->getFloat(23);
	mDirection.z = stream->getFloat(23);
	mOrientation.x = stream->getFloat(23);
	mOrientation.y = stream->getFloat(23);
	mOrientation.z = stream->getFloat(23);
	Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "Read " << mDirection.x << " " << mDirection.y << " " << mDirection.z;
}

BasicEntityEvent* BasicEntityEvent::parse(ZCom_BitStream* stream) {
	BasicEntityEvent* e = new BasicEntityEvent(Ogre::Vector3(0.0, 0.0, 0.0), Ogre::Vector3(0.0, 0.0, 0.0));
	e->deserialize(stream);
	return e;
}

}
