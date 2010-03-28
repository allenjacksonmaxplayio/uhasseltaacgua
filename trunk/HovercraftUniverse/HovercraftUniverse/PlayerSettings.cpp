#include "PlayerSettings.h"

namespace HovUni {

PlayerSettings::PlayerSettings(ZCom_ConnID connectionID) : 
	NetworkEntity(3), mConnectionID(connectionID), mCharacter(""), mHovercraft(""), mPlayerName("") {
	
	// Empty
	mNode->setOwner(connectionID,true);

	// Add as network entity
	networkRegister(NetworkIDManager::getServerSingletonPtr(),getClassName());

	//some default values
	mHovercraft = "hover1";
}

PlayerSettings::PlayerSettings(ZCom_BitStream* announcedata):
	NetworkEntity(3)
{
}

PlayerSettings::~PlayerSettings(void){
}

std::string PlayerSettings::getClassName(){
	return "PlayerSettings";
}

void PlayerSettings::setAnnouncementData(ZCom_BitStream* stream){
	// No need to send the connection ID since it is already known by the client
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