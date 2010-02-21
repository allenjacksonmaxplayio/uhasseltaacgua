#include "StdAfx.h"
#include "SampleEventMoveBackward.h"

namespace HovUni {

SampleEventMoveBackward::SampleEventMoveBackward(float distance) : NetworkEvent(MoveBackward), mDistance(distance) {

}

SampleEventMoveBackward::SampleEventMoveBackward() : NetworkEvent(MoveForward), mDistance(0.0) {

}

SampleEventMoveBackward::~SampleEventMoveBackward() {

}

void SampleEventMoveBackward::write(ZCom_BitStream* stream) {
	stream->addFloat(mDistance, 23);
}

void SampleEventMoveBackward::read(ZCom_BitStream* stream) {
	mDistance = stream->getFloat(23);
}

SampleEventMoveBackward SampleEventMoveBackward::parse(ZCom_BitStream* stream) {
	SampleEventMoveBackward e;
	e.deserialize(stream);
	return e;
}

}
