#include "PlayerSettings.h"
#include "Lobby.h"

namespace HovUni {

PlayerSettings::PlayerSettings( Lobby * lobby, ZCom_ConnID connectionID) : 
	NetworkEntity(3), mConnectionID(connectionID), mCharacter(""), mHovercraft(""), mPlayerName(""), mLobby(lobby) {
	
	// Empty
	mNode->setOwner(connectionID,true);

	// Add as network entity
	networkRegister(NetworkIDManager::getServerSingletonPtr(),getClassName());

	//some default values
	mHovercraft = "hover1";
}

PlayerSettings::PlayerSettings( Lobby * lobby, ZCom_BitStream* announcedata):
	NetworkEntity(3), mLobby(lobby)
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

void PlayerSettings::parseEvents(eZCom_Event type, eZCom_NodeRole remote_role, ZCom_ConnID conn_id, ZCom_BitStream* stream, float timeSince){
	//user data
	if ( type == eZCom_EventUser ){
			
	}
	//Request to delete this object
	if ( type == eZCom_EventRemoved && remote_role == eZCom_RoleAuthority ){
		//remove it from the lobby
		mLobby->removePlayer(this);
	}
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