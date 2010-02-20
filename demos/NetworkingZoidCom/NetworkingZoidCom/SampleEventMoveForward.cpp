#include "StdAfx.h"
#include "SampleEventMoveForward.h"

namespace HovUni {

SampleEventMoveForward::SampleEventMoveForward(float distance) : Event(MoveForward), mDistance(distance) {

}

SampleEventMoveForward::SampleEventMoveForward() : Event(MoveForward), mDistance(0.0) {

}

SampleEventMoveForward::~SampleEventMoveForward() {

}

void SampleEventMoveForward::write(ZCom_BitStream* stream) {
	stream->addFloat(mDistance, 23);
}

void SampleEventMoveForward::read(ZCom_BitStream* stream) {
	mDistance = stream->getFloat(23);
}

SampleEventMoveForward SampleEventMoveForward::parse(ZCom_BitStream* stream) {
	SampleEventMoveForward e;
	e.deserialize(stream);
	return e;
}

}
