#include "StdAfx.h"
#include "NetworkEvent.h"
#include "Player.h"
#include "SampleEventParser.h"

ZCom_ClassID Player::mClassID = ZCom_Invalid_ID;

Player::Player(ZCom_Control* control) {
	mNode->registerNodeDynamic(mClassID, control);
}

Player::~Player(void) {

}

void Player::parseEntityEvents(ZCom_BitStream* stream) {
	// Parse
	HovUni::SampleEventParser p;
	HovUni::NetworkEvent<SampleEventType> event = p.parse(stream);

	// Process

	// Server
	if (mNode->getRole() == eZCom_RoleAuthority) {
		switch (event.getType()) {
			case HovUni::MoveForward:
				{
					cout << "Player is trying to move forward" << endl;
					// Let's allow the movement
					ZCom_BitStream* stream = new ZCom_BitStream();
					event.serialize(stream);
					mNode->sendEvent(eZCom_Unreliable, ZCOM_REPRULE_AUTH_2_ALL, stream);
				}
				break;
			case HovUni::MoveBackward:
				{
					cout << "Player is trying to move backward" << endl;
					// Let's allow the movement
					ZCom_BitStream* stream = new ZCom_BitStream();
					event.serialize(stream);
					mNode->sendEvent(eZCom_Unreliable, ZCOM_REPRULE_AUTH_2_ALL, stream);
				}
				break;
			case HovUni::MoveLeft:
				{
					cout << "Player is trying to move left" << endl;
					// Let's allow the movement
					ZCom_BitStream* stream = new ZCom_BitStream();
					event.serialize(stream);
					mNode->sendEvent(eZCom_Unreliable, ZCOM_REPRULE_AUTH_2_ALL, stream);
				}
				break;
			case HovUni::MoveRight:
				{
					cout << "Player is trying to move right but crashed" << endl;
					// Cannot allow movement so shock reaction to left
					ZCom_BitStream* stream = new ZCom_BitStream();
					HovUni::SampleEventMoveLeft seml(0.5);
					seml.serialize(stream);
					mNode->sendEvent(eZCom_Unreliable, ZCOM_REPRULE_AUTH_2_ALL, stream);
				}
				break;

			default:
				break;
		}

	// Owner
	} else if (mNode->getRole() == eZCom_RoleOwner) {
		switch (event.getType()) {
			case HovUni::MoveForward:
				cout << "You moved forward" << endl;
				break;
			case HovUni::MoveBackward:
				cout << "You moved backward" << endl;
				break;
			case HovUni::MoveLeft:
				cout << "You moved left" << endl;
				break;
			case HovUni::MoveRight:
				cout << "You moved right" << endl;
				break;

			default:
				break;
		}

	// Others
	} else {
		switch (event.getType()) {
			case HovUni::MoveForward:
				cout << "Someone moved forward" << endl;
				break;
			case HovUni::MoveBackward:
				cout << "Someone moved backward" << endl;
				break;
			case HovUni::MoveLeft:
				cout << "Someone moved left" << endl;
				break;
			case HovUni::MoveRight:
				cout << "Someone moved right" << endl;
				break;

			default:
				break;
		}
	}

}

void Player::registerClass(ZCom_Control* control) {
	mClassID = control->ZCom_registerClass("Player");
}

ZCom_ClassID Player::getClassID() {
	return mClassID;
}