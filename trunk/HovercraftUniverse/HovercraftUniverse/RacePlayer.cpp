#include "RacePlayer.h"
#include "RaceState.h"
#include "PlayerSettings.h"
#include "Lobby.h"
#include "RaceStateListener.h"

#include <OgreLogManager.h>

namespace HovUni {

RacePlayer::RacePlayer(RaceState* state, PlayerSettings* playerSettings) :
	NetworkEntity(1), mRaceState(state), mPlayerSettings(playerSettings), mPlayerPosition(-1), mLastCheckpoint(-1) {

	// Add as network entity
	networkRegister(NetworkIDManager::getServerSingletonPtr(), getClassName(), true);
	mNode->dependsOn(state->getNetworkNode());
}

RacePlayer::RacePlayer(Lobby* lobby, ZCom_BitStream* announcementdata, ZCom_ClassID id,
		ZCom_Control* control) :
	NetworkEntity(1), mRaceState(lobby->getRaceState()), mPlayerSettings(lobby->getPlayer(
			announcementdata->getInt(32))), mPlayerPosition(-1), mLastCheckpoint(-1) {

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

bool RacePlayer::isBot() const {
	return mPlayerSettings->isBot();
}

void RacePlayer::setPosition(short position) {
	mPlayerPosition = position;
	Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "Position of player " << getSettings()->getPlayerName() << " is " << position;
	std::vector<RaceStateListener*> listeners = mRaceState->getListeners();
	for (std::vector<RaceStateListener*>::iterator i = listeners.begin(); i != listeners.end(); ++i) {
		(*i)->onPositionChange(this);
	}
}

short RacePlayer::getPosition() const {
	return mPlayerPosition;
}

void RacePlayer::addCheckpoint(unsigned int checkpoint, long timestamp) {
	if (mLastCheckpoint == checkpoint - 1) {
		mCheckpoints[checkpoint] = timestamp;
		++mLastCheckpoint;
	}
}

long RacePlayer::getCheckpoint(unsigned int checkpoint) {
	return (checkpoint <= mLastCheckpoint ? mCheckpoints[checkpoint] : -1);
}

unsigned int RacePlayer::getLastCheckpoint() {
	return mLastCheckpoint;
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
