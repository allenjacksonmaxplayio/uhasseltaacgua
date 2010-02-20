#include "StdAfx.h"
#include "SampleEventMoveLeft.h"

namespace HovUni {

SampleEventMoveLeft::SampleEventMoveLeft(float distance) : Event(MoveLeft), mDistance(distance) {

}

SampleEventMoveLeft::SampleEventMoveLeft() : Event(MoveForward), mDistance(0.0) {

}

SampleEventMoveLeft::~SampleEventMoveLeft() {

}

void SampleEventMoveLeft::write(ZCom_BitStream* stream) {
	stream->addFloat(mDistance, 23);
}

void SampleEventMoveLeft::read(ZCom_BitStream* stream) {
	mDistance = stream->getFloat(23);
}

SampleEventMoveLeft SampleEventMoveLeft::parse(ZCom_BitStream* stream) {
	SampleEventMoveLeft e;
	e.deserialize(stream);
	return e;
}

}
