#include "PlayerSettings.h"

namespace HovUni {

PlayerSettings::PlayerSettings(ZCom_ConnID connectionID) : 
	NetworkEntity(3), mConnectionID(connectionID), mCharacter(""), mHovercraft(""), mPlayerName("") {
	
	// Empty
	mNode->setOwner(connectionID,true);

	// Add as network entity
	networkRegister(NetworkIDManager::getServerSingletonPtr(),getClassName(),true);

	//some default values
	mHovercraft = "hover1";
}

PlayerSettings::PlayerSettings(ZCom_BitStream* announcedata):
	NetworkEntity(3)
{
	mConnectionID = announcedata->getInt(sizeof(ZCom_ConnID) * 8);
}

PlayerSettings::~PlayerSettings(void){
}

std::string PlayerSettings::getClassName(){
	return "Player";
}

void PlayerSettings::setAnnouncementData(ZCom_BitStream* stream){
	stream->addInt(mConnectionID,sizeof(ZCom_ConnID) * 8);
}

void PlayerSettings::setupReplication(){
	//replicate name
	replicateString(&mPlayerName);

	//replicate hovercraft
	replicateString(&mHovercraft);

	//replicate character
	replicateString(&mCharacter);
}

}