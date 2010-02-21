#include "StdAfx.h"
#include "NetworkEvent.h"
#include "Player.h"
#include "SampleEventMoveForward.h"
#include "SampleEventParser.h"

ZCom_ClassID Player::mClassID = ZCom_Invalid_ID;

Player::Player(ZCom_Control* control): mX(0), mY(0), mZ(0) {
	setupReplication();
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
					HovUni::SampleEventMoveForward e = (HovUni::SampleEventMoveForward) event;
					mX += e.getDistance();
					sendEvent(event);
				}
				break;
			case HovUni::MoveBackward:
				{
					cout << "Player is trying to move backward" << endl;
					// Let's allow the movement
					sendEvent(event);
				}
				break;
			case HovUni::MoveLeft:
				{
					cout << "Player is trying to move left" << endl;
					// Let's allow the movement
					sendEvent(event);
				}
				break;
			case HovUni::MoveRight:
				{
					cout << "Player is trying to move right but crashed" << endl;
					// Cannot allow movement so shock reaction to left
					HovUni::SampleEventMoveLeft seml(0.5);
					sendEvent(seml);
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

	cout << "Position: (" << mX << ", " << mY << ", " << mZ << ")" << endl;
}

void Player::setupReplication() {
	mNode->beginReplicationSetup(3);

	mNode->addReplicationFloat(&mX, 23, ZCOM_REPFLAG_MOSTRECENT, ZCOM_REPRULE_AUTH_2_ALL);
	mNode->addReplicationFloat(&mY, 23, ZCOM_REPFLAG_MOSTRECENT, ZCOM_REPRULE_AUTH_2_ALL);
	mNode->addReplicationFloat(&mZ, 23, ZCOM_REPFLAG_MOSTRECENT, ZCOM_REPRULE_AUTH_2_ALL);

	mNode->endReplicationSetup();
}

void Player::registerClass(ZCom_Control* control) {
	mClassID = control->ZCom_registerClass("Player");
}

ZCom_ClassID Player::getClassID() {
	return mClassID;
}