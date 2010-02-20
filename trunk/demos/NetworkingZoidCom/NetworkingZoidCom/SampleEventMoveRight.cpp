#include "StdAfx.h"
#include "SampleEventMoveRight.h"

namespace HovUni {

SampleEventMoveRight::SampleEventMoveRight(float distance) : Event(MoveRight), mDistance(distance) {

}

SampleEventMoveRight::SampleEventMoveRight() : Event(MoveForward), mDistance(0.0) {

}

SampleEventMoveRight::~SampleEventMoveRight() {

}

void SampleEventMoveRight::write(ZCom_BitStream* stream) {
	stream->addFloat(mDistance, 23);
}

void SampleEventMoveRight::read(ZCom_BitStream* stream) {
	mDistance = stream->getFloat(23);
}

SampleEventMoveRight SampleEventMoveRight::parse(ZCom_BitStream* stream) {
	SampleEventMoveRight e;
	e.deserialize(stream);
	return e;
}

}
