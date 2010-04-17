#include "BasicEntityEvent.h"
#include <OgreLogManager.h>

namespace HovUni {

BasicEntityEvent::BasicEntityEvent(bool forward, bool backward, bool left, bool right) : 
	ControllerEvent(BasicEntity), mForward(forward), mBackward(backward), mLeft(left), mRight(right) {

}

BasicEntityEvent::BasicEntityEvent() : ControllerEvent(BasicEntity), mForward(false), mBackward(false), mLeft(false), mRight(false) {

}

BasicEntityEvent::~BasicEntityEvent() {

}

bool BasicEntityEvent::operator==(const BasicEntityEvent& event) {
	if ((mForward == event.mForward) && 
		(mBackward == event.mBackward) && 
		(mLeft == event.mLeft) && 
		(mRight == event.mRight)) {
			return true;
	} else {
		return false;
	}
}

bool BasicEntityEvent::moveForward() const {
	return mForward;
}

bool BasicEntityEvent::moveBackward() const {
	return mBackward;
}

bool BasicEntityEvent::moveLeft() const {
	return mLeft;
}

bool BasicEntityEvent::moveRight() const {
	return mRight;
}

void BasicEntityEvent::clear() {
	mForward = false;
	mBackward = false;
	mLeft = false;
	mRight = false;
}

void BasicEntityEvent::write(ZCom_BitStream* stream) const {
	// Write information for controller event
	ControllerEvent::write(stream);

	// Write own information
	stream->addBool(mForward);
	stream->addBool(mBackward);
	stream->addBool(mLeft);
	stream->addBool(mRight);
}

void BasicEntityEvent::read(ZCom_BitStream* stream) {
	// Read information for controller event
	ControllerEvent::read(stream);

	// Read own information
	mForward = stream->getBool();
	mBackward = stream->getBool();
	mLeft = stream->getBool();
	mRight = stream->getBool();
}

BasicEntityEvent* BasicEntityEvent::parse(ZCom_BitStream* stream) {
	BasicEntityEvent* e = new BasicEntityEvent();
	e->deserialize(stream);
	return e;
}

}
