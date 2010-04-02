#include "PlayerSettings.h"
#include "Lobby.h"
#include "GameEvent.h"
#include "GameEventParser.h"
#include "InitEvent.h"

namespace HovUni {

PlayerSettings::PlayerSettings( Lobby * lobby, unsigned int userID) : 
	NetworkEntity(3), mUserID(userID), mCharacter(""), mHovercraft(""), mPlayerName(""), mLobby(lobby) {
	
	// Empty
	mNode->setOwner(userID, true);

	// Add as network entity
	networkRegister(NetworkIDManager::getServerSingletonPtr(),getClassName(), true);
	mNode->setEventNotification(true, false);
}

PlayerSettings::PlayerSettings(Lobby * lobby, ZCom_BitStream* announcementdata, ZCom_ClassID id, ZCom_Control* control):
	NetworkEntity(3), mLobby(lobby), mUserID(announcementdata->getInt(32)), mCharacter(""), mHovercraft(""), mPlayerName("")
{
	//Read the other settings out of the announcement data
	int length = announcementdata->getInt(sizeof(int) * 8);
	if (length != 0){
		mCharacter = Ogre::String(announcementdata->getString());
	}

	length = announcementdata->getInt(sizeof(int) * 8);
	if (length != 0){
		mHovercraft = Ogre::String(announcementdata->getString());
	}

	length = announcementdata->getInt(sizeof(int) * 8);
	if (length != 0){
		mPlayerName = Ogre::String(announcementdata->getString());
	}

	networkRegister(id, control);
	mNode->setEventNotification(true, false);
}

PlayerSettings::~PlayerSettings() {
}

std::string PlayerSettings::getClassName() {
	return "PlayerSettings";
}

void PlayerSettings::setAnnouncementData(ZCom_BitStream* stream) {
	stream->addInt(mUserID, 32);
	
	stream->addInt(mCharacter.length(),sizeof(int) * 8);
	if ( mCharacter.length() != 0 ){
		stream->addString(mCharacter.c_str());
	}

	stream->addInt(mHovercraft.length(),sizeof(int) * 8);
	if ( mHovercraft.length() != 0 ){
		stream->addString(mHovercraft.c_str());
	}

	stream->addInt(mPlayerName.length(),sizeof(int) * 8);
	if ( mPlayerName.length() != 0 ){
		stream->addString(mPlayerName.c_str());
	}
}

void PlayerSettings::parseEvents(eZCom_Event type, eZCom_NodeRole remote_role, ZCom_ConnID conn_id, ZCom_BitStream* stream, float timeSince) {
	// User events
	/*
	if (type == eZCom_EventUser && mNode->getRole() != eZCom_RoleAuthority) {
		GameEventParser p;
		GameEvent* event = p.parse(stream);
		InitEvent* init = dynamic_cast<InitEvent*>(event);
		if (init) {
			ZCom_BitStream* state = init->getStream();
			mPlayerName = state->getString();
			mHovercraft = state->getString();
			mCharacter = state->getString();
		}
	}
	*/
	// Request to delete this object
	if (type == eZCom_EventRemoved && remote_role == eZCom_RoleAuthority) {
		//remove it from the lobby
		mLobby->removePlayer(this);
	}

	// A new client received this object so send current state
	/*
	if (type == eZCom_EventInit && mNode->getRole() == eZCom_RoleAuthority) {
		ZCom_BitStream* state = new ZCom_BitStream();
		state->addString(mPlayerName.c_str());
		state->addString(mHovercraft.c_str());
		state->addString(mCharacter.c_str());
		sendEventDirect(InitEvent(state), conn_id);
	}
	*/
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