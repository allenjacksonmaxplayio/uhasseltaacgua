#include "PlayerSettings.h"
#include "Lobby.h"
#include "GameEvent.h"
#include "GameEventParser.h"
#include "InitEvent.h"

#include <OgreLogManager.h>

namespace HovUni {

PlayerSettings::PlayerSettings(Lobby * lobby, unsigned int userID, bool serverOwner) :
	NetworkEntity(3), mUserID(userID), mCharacter(0), mHovercraft(0), mPlayerName(""),
			mLobby(lobby) {

	// Add as network entity
	networkRegister(NetworkIDManager::getServerSingletonPtr(), getClassName(), true);
	mNode->setEventNotification(true, false);

	if (!serverOwner) {
		// Set owner
		mNode->setOwner(userID, true);
	}

	// No default values, they can be set in the ini file
}

PlayerSettings::PlayerSettings(Lobby * lobby, ZCom_BitStream* announcementdata, ZCom_ClassID id,
		ZCom_Control* control) :
	NetworkEntity(3), mLobby(lobby), mUserID(announcementdata->getInt(32)), mCharacter(0),
			mHovercraft(0), mPlayerName("") {
	networkRegister(id, control);
	mNode->setEventNotification(true, false);
}

PlayerSettings::~PlayerSettings() {
}

std::string PlayerSettings::getClassName() {
	return "PlayerSettings";
}

void PlayerSettings::setPlayerName(const Ogre::String& name) {
	mPlayerName.assign(name);
}

const Ogre::String& PlayerSettings::getPlayerName() const {
	return mPlayerName;
}

void PlayerSettings::setCharacter(unsigned int character) {
	mCharacter = character;
}

const Ogre::String PlayerSettings::getCharacter() const {
	// TODO Mapping?
	if (mCharacter == 0) {
		return "NoMappingYet";
	} else {
		return "";
	}
}

void PlayerSettings::setHovercraft(unsigned int hov) {
	mHovercraft = hov;
}

const Ogre::String PlayerSettings::getHovercraft() const {
	// TODO Mapping? Must be performed in an INI to which the main INI refers. At the moment it is rather lame ..
	if (mHovercraft == 0) {
		return "hover1";
	} else if (mHovercraft == 1) {
		return "HippyCraft";
	} else {
		return "";
	}
}

const unsigned int PlayerSettings::getID() const {
	return mUserID;
}

void PlayerSettings::setAnnouncementData(ZCom_BitStream* stream) {
	stream->addInt(mUserID, 32);
}

void PlayerSettings::parseEvents(eZCom_Event type, eZCom_NodeRole remote_role, ZCom_ConnID conn_id,
		ZCom_BitStream* stream, float timeSince) {

}

void PlayerSettings::setupReplication() {
	//replicate name
	replicateString(&mPlayerName, ZCOM_REPRULE_OWNER_2_AUTH | ZCOM_REPRULE_AUTH_2_PROXY);

	//replicate hovercraft
	replicateUnsignedInt((int*) &mHovercraft,
			ZCOM_REPRULE_OWNER_2_AUTH | ZCOM_REPRULE_AUTH_2_PROXY, 4);

	//replicate character
	replicateUnsignedInt((int*) &mCharacter, ZCOM_REPRULE_OWNER_2_AUTH | ZCOM_REPRULE_AUTH_2_PROXY,
			4);
}

}
