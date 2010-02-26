#include "ControllerEvent.h"

namespace HovUni {

ControllerEvent::ControllerEvent(ControllerEventType type) : NetworkEvent<ControllerEventType>(type), mTime(0.0f) {

}

ControllerEvent::~ControllerEvent() {

}

void ControllerEvent::setTimeSinceLastFrame(Ogre::Real time) {
	mTime = time;
}

Ogre::Real ControllerEvent::getTimeSinceLastFrame() const {
	return mTime;
}

void ControllerEvent::write(ZCom_BitStream* stream) const {
	stream->addFloat(mTime, 23);
}

void ControllerEvent::read(ZCom_BitStream* stream) {
	mTime = stream->getFloat(23);
}

}
