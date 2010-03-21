#include "Player.h"

namespace HovUni {

Player::Player(ZCom_ConnID connectionID) : 
	NetworkEntity(3), mConnectionID(connectionID), mCharacter(""), mHovercraft(""), mPlayerName("") {
	
	// Empty
	mNode->setOwner(connectionID,true);

	// Add as network entity
	networkRegister(NetworkIDManager::getServerSingletonPtr(),getClassName(),true);

	//some default values
	mHovercraft = "hover1";
}

Player::Player(ZCom_BitStream* announcedata):
	NetworkEntity(3)
{
	mConnectionID = announcedata->getInt(sizeof(ZCom_ConnID) * 8);
}

Player::~Player(void){
}

std::string Player::getClassName(){
	return "Player";
}

void Player::setAnnouncementData(ZCom_BitStream* stream){
	stream->addInt(mConnectionID,sizeof(ZCom_ConnID) * 8);
}

void Player::setupReplication(){
	//replicate name
	replicateString(&mPlayerName);

	//replicate hovercraft
	replicateString(&mHovercraft);

	//replicate character
	replicateString(&mCharacter);
}

}