#include "StdAfx.h"
#include "Player.h"

ZCom_ClassID Player::mClassID = ZCom_Invalid_ID;

Player::Player(ZCom_Control* control) {
	mNode->registerNodeDynamic(mClassID, control);
}

Player::~Player(void) {

}

void Player::processEntityEvents(const string& event) {
	if (mNode->getRole() == eZCom_RoleAuthority) {
		cout << "Player event occurred: " << event << endl;
		cout << "  Responding..." << endl;
		ZCom_BitStream* event = new ZCom_BitStream();
		event->addString("moved up");
		mNode->sendEvent(eZCom_Unreliable, ZCOM_REPRULE_AUTH_2_ALL, event);
	} else if (mNode->getRole() == eZCom_RoleOwner) {
		cout << "Player event occurred: YOU " << event << endl;
	} else {
		cout << "Player event occurred: OTHER " << event << endl;
	}
}

void Player::registerClass(ZCom_Control* control) {
	mClassID = control->ZCom_registerClass("Player");
}

ZCom_ClassID Player::getClassID() {
	return mClassID;
}