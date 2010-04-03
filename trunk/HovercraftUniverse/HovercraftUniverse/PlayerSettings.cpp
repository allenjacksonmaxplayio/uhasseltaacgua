#include "PlayerSettings.h"
#include "Lobby.h"
#include "GameEvent.h"
#include "GameEventParser.h"
#include "InitEvent.h"

namespace HovUni {

PlayerSettings::PlayerSettings(Lobby * lobby, unsigned int userID) :
	NetworkEntity(3), mUserID(userID), mCharacter(""), mHovercraft(""), mPlayerName(""), mLobby(
			lobby) {

	// Add as network entity
	networkRegister(NetworkIDManager::getServerSingletonPtr(), getClassName(), true);
	mNode->setEventNotification(true, false);

	// Set owner
	mNode->setOwner(userID, true);

	// No default values, they can be set in the ini file
}

PlayerSettings::PlayerSettings(Lobby * lobby, ZCom_BitStream* announcementdata, ZCom_ClassID id,
		ZCom_Control* control) :
	NetworkEntity(3), mLobby(lobby), mUserID(announcementdata->getInt(32)), mCharacter(""),
			mHovercraft(""), mPlayerName("") {
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
}

void PlayerSettings::parseEvents(eZCom_Event type, eZCom_NodeRole remote_role, ZCom_ConnID conn_id,
		ZCom_BitStream* stream, float timeSince) {
	// Request to delete this object
	if (type == eZCom_EventRemoved && remote_role == eZCom_RoleAuthority) {
		//remove it from the lobby
		mLobby->removePlayer(this);
	}
}

void PlayerSettings::setupReplication() {
	//replicate name
	replicateString(&mPlayerName, ZCOM_REPRULE_OWNER_2_AUTH | ZCOM_REPRULE_AUTH_2_PROXY);

	//replicate hovercraft
	replicateString(&mHovercraft, ZCOM_REPRULE_OWNER_2_AUTH | ZCOM_REPRULE_AUTH_2_PROXY);

	//replicate character
	replicateString(&mCharacter, ZCOM_REPRULE_OWNER_2_AUTH | ZCOM_REPRULE_AUTH_2_PROXY);
}

}
