#include "StdAfx.h"
#include "Event.h"
#include "SampleEventMoveForward.h"
#include "SampleEventMoveBackward.h"
#include "SampleEventMoveLeft.h"
#include "SampleEventMoveRight.h"

namespace HovUni {

Event::Event(EventType type) : mType(type) {

}

Event::~Event() {

}

EventType Event::getType() const {
	return mType;
}

void Event::serialize(ZCom_BitStream* stream) const {
	// Write the type of the event
	stream->addInt((int) mType, 4);

	// Write the data of the event
	write(stream);
}

void Event::deserialize(ZCom_BitStream* stream) {
	// Read the type of the event
	mType = (EventType) (int) stream->getInt(4);

	// Read the data of the event
	read(stream);
}

EventType Event::readType(ZCom_BitStream* stream) {
	ZCom_BitStream::BitPos pos;
	stream->saveReadState(pos);
	EventType t = (EventType) (int) stream->getInt(4);
	stream->restoreReadState(pos);
	return t;
}

Event Event::parse(ZCom_BitStream* stream) {
	cout << "Parsing... ";
	if (readType(stream) == MoveForward) {
		cout << "SampleEventMoveForward" << endl;
		return SampleEventMoveForward::parse(stream);
	} else if (readType(stream) == MoveBackward) {
		cout << "SampleEventMoveBackward" << endl;
		return SampleEventMoveBackward::parse(stream);
	} else if (readType(stream) == MoveLeft) {
		cout << "SampleEventMoveLeft" << endl;
		return SampleEventMoveLeft::parse(stream);
	} else if (readType(stream) == MoveRight) {
		cout << "SampleEventMoveRight" << endl;
		return SampleEventMoveRight::parse(stream);
	}

	return Event(MoveLeft);
}

}
