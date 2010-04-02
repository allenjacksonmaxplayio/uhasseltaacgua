#include "PlayerSettings.h"
#include "Lobby.h"
#include "GameEvent.h"
#include "GameEventParser.h"
#include "InitEvent.h"

#include <OgreLogManager.h>

namespace HovUni {

PlayerSettings::PlayerSettings( Lobby * lobby, unsigned int userID) : 
	NetworkEntity(4), mUserID(userID), mCharacter(""), mHovercraft(""), mPlayerName(""), mLobby(lobby), mTMP(0) {

	// Add as network entity
	networkRegister(NetworkIDManager::getServerSingletonPtr(),getClassName(), true);
	mNode->setEventNotification(true, false);

	// Set owner
	mNode->setOwner(userID, true);

	//some default values
	// TODO Nickman, you have removed this in your commit, but I needed it or otherwise it would crash. So I put it back for a second (Kristof)
	mHovercraft = "hover1";
	mPlayerName = "Playorlol";
}

PlayerSettings::PlayerSettings(Lobby * lobby, ZCom_BitStream* announcementdata, ZCom_ClassID id, ZCom_Control* control):
	NetworkEntity(4), mLobby(lobby), mUserID(announcementdata->getInt(32)), mCharacter(""), mHovercraft(""), mPlayerName(""), mTMP(0)
{
	networkRegister(id, control);
	mNode->setEventNotification(true, false);
}

PlayerSettings::~PlayerSettings() {
}

std::string PlayerSettings::getClassName() {
	return "PlayerSettings";
}

int PlayerSettings::getTMP() {
	return mTMP;
}

void PlayerSettings::setAnnouncementData(ZCom_BitStream* stream) {
	stream->addInt(mUserID, 32);	
}

void PlayerSettings::parseEvents(eZCom_Event type, eZCom_NodeRole remote_role, ZCom_ConnID conn_id, ZCom_BitStream* stream, float timeSince) {
	// User events
	if (type == eZCom_EventUser && mNode->getRole() != eZCom_RoleAuthority) {
		GameEventParser p;
		GameEvent* event = p.parse(stream);
		InitEvent* init = dynamic_cast<InitEvent*>(event);
		if (init) {
			ZCom_BitStream* state = init->getStream();
			mPlayerName = state->getString();
			mHovercraft = state->getString();
			mCharacter = state->getString();
			Ogre::LogManager::getSingletonPtr()->stream() << "PlayerSettings:: received current state from server";
		}
	}

	// Request to delete this object
	if (type == eZCom_EventRemoved && remote_role == eZCom_RoleAuthority) {
		//remove it from the lobby
		mLobby->removePlayer(this);
	}

	// A new client received this object so send current state
	if (type == eZCom_EventInit && mNode->getRole() == eZCom_RoleAuthority) {
		ZCom_BitStream* state = new ZCom_BitStream();
		state->addString(mPlayerName.c_str());
		state->addString(mHovercraft.c_str());
		state->addString(mCharacter.c_str());
		sendEventDirect(InitEvent(state), conn_id);
		Ogre::LogManager::getSingletonPtr()->getDefaultLog()->stream() << "PlayerSettings:: sent current state to new client";
	}
}

void PlayerSettings::setupReplication(){
	mNode->addReplicationInt(
    &mTMP,  // pointer to the variable
    7,        // amount of bits (7 bits allow values up to 127
              // 100 is max for the health)
    false,    // unsigned
    ZCOM_REPFLAG_MOSTRECENT, // always send the most recent value only
    ZCOM_REPRULE_AUTH_2_ALL|ZCOM_REPRULE_OWNER_2_AUTH  // owner to server + server to clients
    );


	//replicate name
	replicateString(&mPlayerName, ZCOM_REPRULE_OWNER_2_AUTH|ZCOM_REPRULE_AUTH_2_PROXY);

	//replicate hovercraft
	replicateString(&mHovercraft, ZCOM_REPRULE_OWNER_2_AUTH|ZCOM_REPRULE_AUTH_2_PROXY);

	//replicate character
	replicateString(&mCharacter, ZCOM_REPRULE_OWNER_2_AUTH|ZCOM_REPRULE_AUTH_2_PROXY);
}

}