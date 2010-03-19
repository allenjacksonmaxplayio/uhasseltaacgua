#include "Player.h"

namespace HovUni {

Player::Player(ZCom_ConnID connectionID) : NetworkEntity(0), mConnectionID(connectionID) {
	// Empty
}

Player::~Player(void){
}

}