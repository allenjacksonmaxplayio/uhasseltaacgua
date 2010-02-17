#include "StdAfx.h"
#include "Player.h"

ZCom_ClassID Player::mClassID = ZCom_Invalid_ID;

Player::Player(ZCom_Control* control) {
	mNode->registerNodeDynamic(mClassID, control);
}

Player::~Player(void) {

}

void Player::registerClass(ZCom_Control* control) {
	mClassID = control->ZCom_registerClass("Player");
}

ZCom_ClassID Player::getClassID() {
	return mClassID;
}