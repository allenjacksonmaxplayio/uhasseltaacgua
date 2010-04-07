#include "RacePlayer.h"
#include "RaceState.h"
#include "PlayerSettings.h"
#include "Lobby.h"
#include "RaceStateListener.h"

namespace HovUni {

RacePlayer::RacePlayer(RaceState* state, PlayerSettings* playerSettings, bool serverOwner) :
	NetworkEntity(1), mRaceState(state), mPlayerSettings(playerSettings), mPlayerPosition(-1) {

	// Add as network entity
	networkRegister(NetworkIDManager::getServerSingletonPtr(), getClassName(), true);
	mNode->dependsOn(state->getNetworkNode());

	if (!serverOwner) {
		// Set owner
		mNode->setOwner(mPlayerSettings->getID(), true);
	}
}

RacePlayer::RacePlayer(Lobby* lobby, ZCom_BitStream* announcementdata, ZCom_ClassID id,
		ZCom_Control* control) :
	NetworkEntity(1), mRaceState(lobby->getRaceState()), mPlayerSettings(lobby->getPlayer(
			announcementdata->getInt(32))), mPlayerPosition(-1) {

	// Add as network entity
	networkRegister(id, control);
}

RacePlayer::~RacePlayer() {

}

std::string RacePlayer::getClassName() {
	return "RacePlayer";
}

RaceState* RacePlayer::getRaceState() {
	return mRaceState;
}

PlayerSettings* RacePlayer::getSettings() {
	return mPlayerSettings;
}

void RacePlayer::setPosition(short position) {
	mPlayerPosition = position;
	std::list<RaceStateListener*> listeners = mRaceState->getListeners();
	for (std::list<RaceStateListener*>::iterator i = listeners.begin(); i != listeners.end(); ++i) {
		(*i)->onPositionChange(this);
	}
}

short RacePlayer::getPosition() const {
	return mPlayerPosition;
}

void RacePlayer::setAnnouncementData(ZCom_BitStream* stream) {
	stream->addInt(mPlayerSettings->getID(), 32);
}

void RacePlayer::parseEvents(eZCom_Event type, eZCom_NodeRole remote_role, ZCom_ConnID conn_id,
		ZCom_BitStream* stream, float timeSince) {

}

void RacePlayer::setupReplication() {
	mNode->addReplicationInt((zS32*) &mPlayerPosition, // pointer to the variable
			sizeof(short) * 8, // amount of bits(full)
			false, // unsigned
			ZCOM_REPFLAG_MOSTRECENT, // always send the most recent value only
			ZCOM_REPRULE_AUTH_2_ALL // server sends to all clients
	);
}

}
