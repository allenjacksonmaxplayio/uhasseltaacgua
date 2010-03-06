#include "NetworkMovementInput.h"

namespace HovUni {

NetworkMovementInput::NetworkMovementInput(bool forward, bool backward, bool left, bool right) : 
		mForward(forward), mBackward(backward), mLeft(left), mRight(right) {

}

NetworkMovementInput::~NetworkMovementInput(void) {

}

void NetworkMovementInput::pack(ZCom_BitStream& stream) const {
	stream.addBool(mForward);
	stream.addBool(mBackward);
	stream.addBool(mLeft);
	stream.addBool(mRight);
}

void NetworkMovementInput::unpack(ZCom_BitStream& stream) {
	mForward = stream.getBool();
	mBackward = stream.getBool();
	mLeft = stream.getBool();
	mRight = stream.getBool();
}

bool NetworkMovementInput::operator==(const NetworkMovementInput& input) {
	return ((mForward == input.mForward) && (mBackward == input.mBackward) && 
		(mLeft == input.mLeft) && (mRight == input.mRight));
}

NetworkMovementInput& NetworkMovementInput::operator=(const NetworkMovementInput& rhs) {
	if (&rhs != this) {
		mForward = rhs.mForward;
		mBackward = rhs.mBackward;
		mLeft = rhs.mLeft;
		mRight = rhs.mRight;
	}
	return *this;
}

}