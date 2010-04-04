#include "RaceState.h"
#include "Lobby.h"
#include "Loader.h"
#include "ClientPreparationLoader.h"
#include "RacePlayer.h"
#include "PlayerSettings.h"
#include "RaceStateListener.h"

#include <OgreLogManager.h>

namespace HovUni {

RaceState::RaceState(Lobby* lobby, Loader* loader, Ogre::String track) :
	NetworkEntity(0), mCurrentState(INITIALIZING), mLobby(lobby), mLoader(loader), mTrackFilename(
			track) {

	// Add as network entity
	networkRegister(NetworkIDManager::getServerSingletonPtr(), getClassName(), true);

	// Load the track on the server
	mLoader->load(mTrackFilename);
}

RaceState::RaceState(Lobby* lobby, ClientPreparationLoader* loader,
		ZCom_BitStream* announcementdata, ZCom_ClassID id, ZCom_Control* control) :
	NetworkEntity(0), mCurrentState(INITIALIZING), mLobby(lobby), mLoader(loader), mTrackFilename(
			announcementdata->getString()) {

	// Add as network entity
	networkRegister(id, control);

	// Load the track on the client
	loader->registerLoader(mTrackFilename);
}

RaceState::~RaceState() {

}

std::string RaceState::getClassName() {
	return "RaceState";
}

void RaceState::process() {
	processEvents(0.0f);
	for (playermap::iterator it = mPlayers.begin(); it != mPlayers.end(); ++it) {
		it->second->processEvents(0.0f);
	}
}

void RaceState::removePlayer(ZCom_ConnID id) {
	playermap::iterator i = mPlayers.find(id);
	delete i->second;
	mPlayers.erase(i);
}

void RaceState::addPlayer(RacePlayer* player, bool ownPlayer) {
	playermap::iterator i = mPlayers.find(player->getSettings()->getID());

	if (i != mPlayers.end()) {
		removePlayer(player->getSettings()->getID());
	}
	mPlayers.insert(std::pair<ZCom_ConnID, RacePlayer*>(player->getSettings()->getID(), player));
	Ogre::LogManager::getSingleton().getDefaultLog()->stream()
			<< "[RaceState]: Inserting new RacePlayer";

	// Set own player
	if (ownPlayer) {
		mOwnPlayer = player;
		Ogre::LogManager::getSingleton().getDefaultLog()->stream()
				<< "[RaceState]: Received own player object";
	}
}

void RaceState::removePlayer(RacePlayer* player) {
	removePlayer(player->getSettings()->getID());
}

RacePlayer* RaceState::getPlayer(ZCom_ConnID id) {
	playermap::iterator i = mPlayers.find(id);
	return (i != mPlayers.end()) ? i->second : 0;
}

void RaceState::addListener(RaceStateListener* listener) {
	mListeners.push_back(listener);
}

void RaceState::removeListener(RaceStateListener* listener) {
	mListeners.remove(listener);
}

std::list<RaceStateListener*>& RaceState::getListeners() {
	return mListeners;
}

void RaceState::setNewState(States state) {
	mCurrentState = state;
	for (std::list<RaceStateListener*>::iterator i = mListeners.begin(); i != mListeners.end(); ++i) {
		(*i)->onStateChange(mCurrentState);
	}
}

void RaceState::setAnnouncementData(ZCom_BitStream* stream) {
	stream->addString(mTrackFilename.c_str());
}

void RaceState::parseEvents(eZCom_Event type, eZCom_NodeRole remote_role, ZCom_ConnID conn_id,
		ZCom_BitStream* stream, float timeSince) {

}

void RaceState::setupReplication() {
}

}
