#include "Config.h"
#include "EntityManager.h"
#include "PlayerSettings.h"
#include "Lobby.h"
#include "GameEvent.h"
#include "GameEventParser.h"
#include "InitEvent.h"

#include <OgreLogManager.h>

namespace HovUni {

PlayerSettings::PlayerSettings(Lobby * lobby, unsigned int userID) :
	NetworkEntity(3), mUserID(userID), mCharacter(0), mHovercraft(0), mPlayerName(""), mLobby(lobby) {

	// Add as network entity
	networkRegister(NetworkIDManager::getServerSingletonPtr(), getClassName(), true);
	mNode->setEventNotification(true, false);

	// Set owner
	mNode->setOwner(userID, true);
}

PlayerSettings::PlayerSettings(Lobby* lobby, const Ogre::String& name) :
	NetworkEntity(3), mUserID(0), mCharacter(0), mHovercraft(0), mPlayerName(name), mLobby(lobby) {

	// Add as network entity
	networkRegister(NetworkIDManager::getServerSingletonPtr(), getClassName(), true);
	mNode->setEventNotification(true, false);
}

PlayerSettings::PlayerSettings(Lobby * lobby, ZCom_BitStream* announcementdata, ZCom_ClassID id, ZCom_Control* control) :
	NetworkEntity(3), mLobby(lobby), mUserID(announcementdata->getInt(32)), mCharacter(0), mHovercraft(0), mPlayerName("") {

	// Add as network entity
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
	// Read ini as specified in the entity manager
	Config * config = new Config();
	config->loadFile(EntityManager::getEntityMappingFile());

	// Return the associated value
	std::stringstream ss;
	ss << mCharacter;
	return config->getValue("Character", ss.str(), "");
}

void PlayerSettings::setHovercraft(unsigned int hov) {
	mHovercraft = hov;
}

const Ogre::String PlayerSettings::getHovercraft() const {
	// Read ini as specified in the entity manager
	Config * config = new Config();
	config->loadFile(EntityManager::getEntityMappingFile());

	// Return the associated value
	std::stringstream ss;
	ss << mHovercraft;
	return config->getValue("Hovercraft", ss.str(), "");
}

const unsigned int PlayerSettings::getID() const {
	return mUserID;
}

void PlayerSettings::setAnnouncementData(ZCom_BitStream* stream) {
	stream->addInt(mUserID, 32);
}

void PlayerSettings::parseEvents(eZCom_Event type, eZCom_NodeRole remote_role, ZCom_ConnID conn_id, ZCom_BitStream* stream,
		float timeSince) {
	if (type == eZCom_EventUser) {
		GameEventParser p;
		GameEvent* event = p.parse(stream);

		// Check for an init event if this object is just created
		InitEvent* init = dynamic_cast<InitEvent*> (event);
		if (init) {
			ZCom_BitStream* state = init->getStream();
			mPlayerName = state->getString();
			mHovercraft = state->getInt(4);
			mCharacter = state->getInt(4);
		}

		delete event;
	}

	// A new client received this object so send current state
	if (type == eZCom_EventInit && mNode->getRole() == eZCom_RoleAuthority) {
		ZCom_BitStream* state = new ZCom_BitStream();
		state->addString(mPlayerName.c_str());
		state->addInt(mHovercraft, 4);
		state->addInt(mCharacter, 4);
		sendEventDirect(InitEvent(state), conn_id);
	}
}

void PlayerSettings::setupReplication() {
	//replicate name
	replicateString(&mPlayerName, ZCOM_REPRULE_OWNER_2_AUTH | ZCOM_REPRULE_AUTH_2_PROXY);

	//replicate hovercraft
	replicateUnsignedInt((int*) &mHovercraft, ZCOM_REPRULE_OWNER_2_AUTH | ZCOM_REPRULE_AUTH_2_PROXY, 4);

	//replicate character
	replicateUnsignedInt((int*) &mCharacter, ZCOM_REPRULE_OWNER_2_AUTH | ZCOM_REPRULE_AUTH_2_PROXY, 4);
}

}
