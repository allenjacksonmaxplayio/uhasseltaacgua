#include "RaceState.h"
#include "Lobby.h"
#include "Loader.h"
#include "ClientPreparationLoader.h"
#include "RacePlayer.h"
#include "PlayerSettings.h"
#include "RaceStateListener.h"
#include "GameEvent.h"
#include "GameEventParser.h"
#include "StateEvent.h"
#include "NetworkClient.h"

#include <OgreLogManager.h>

namespace HovUni {

RaceState::RaceState(Lobby* lobby, Loader* loader, Ogre::String track) :
	NetworkEntity(0), mCurrentState(INITIALIZING), mServer(true), mLobby(lobby), mLoader(loader), mTrackFilename(track),
			mInitialized(true) {
	if (mLoader) {
		mLoader->setRaceState(this);
	}

	// Add as network entity
	networkRegister(NetworkIDManager::getServerSingletonPtr(), getClassName(), true);

	// Create race players
	const Lobby::playermap& playersettings = lobby->getPlayers();

	for (Lobby::playermap::const_iterator it = playersettings.begin(); it != playersettings.end(); ++it) {
		RacePlayer* rplayer = new RacePlayer(this, it->second);
		addPlayer(rplayer);
	}

	// Set the waiting list for retrieving the initialized event
	setWaitingList();

	/*
	 //Code to add bots to the game, unfinished!
	 if (lobby->isFillWithBots()) {
	 //This 5 should be replaced by the real maximum number of players
	 int botsNeeded = 5 - lobby->getNumberOfPlayers();

	 //Add bots to the game
	 for (int i = 1; i <= botsNeeded; ++i) {
	 //Create the playersettings
	 PlayerSettings* settings = new PlayerSettings(lobby, (short)-i, true);
	 lobby->addPlayer(settings);
	 settings->setCharacter(0);
	 settings->setHovercraft(0);
	 settings->setPlayerName("BOT");
	 RacePlayer* rplayer = new RacePlayer(this, settings, true);
	 addPlayer(rplayer);
	 }
	 }
	 */
}

RaceState::RaceState(Lobby* lobby, ClientPreparationLoader* loader, ZCom_BitStream* announcementdata, ZCom_ClassID id,
		ZCom_Control* control) :
	NetworkEntity(0), mCurrentState(INITIALIZING), mServer(false), mLobby(lobby), mLoader(loader), mTrackFilename(
			announcementdata->getString()), mInitialized(false) {
	if (mLoader) {
		mLoader->setRaceState(this);
	}

	// Add as network entity
	networkRegister(id, control);
}

RaceState::~RaceState() {

}

std::string RaceState::getClassName() {
	return "RaceState";
}

void RaceState::process() {
	processEvents(0.0f);

	if (!mInitialized && (mCurrentState == INITIALIZING)) {
		// Send the event to indicate that the race state was initialized
		sendRaceStateEvent(INITIALIZED);
		mInitialized = true;
	}

	for (playermap::iterator it = mPlayers.begin(); it != mPlayers.end();) {
		ZCom_ConnID id = it->first;
		RacePlayer* player = it->second;

		// Check if this settings wasn't deleted in the mean time
		if (player->isDeleted()) {
			it = removePlayer(it);
		} else {
			player->processEvents(0.0f);
			++it;
		}
	}
}

void RaceState::removePlayer(ZCom_ConnID id) {
	playermap::iterator i = mPlayers.find(id);
	removePlayer(i);
}

RaceState::playermap::iterator RaceState::removePlayer(playermap::iterator i) {
	delete i->second;
	return mPlayers.erase(i);
}

void RaceState::addPlayer(RacePlayer* player, bool ownPlayer) {
	playermap::iterator i = mPlayers.find(player->getSettings()->getID());

	if (i != mPlayers.end()) {
		removePlayer(player->getSettings()->getID());
	}
	mPlayers.insert(std::pair<ZCom_ConnID, RacePlayer*>(player->getSettings()->getID(), player));
	Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "[RaceState]: Inserting new RacePlayer";

	// Set own player
	if (ownPlayer) {
		mOwnPlayer = player;
		Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "[RaceState]: Received own player object";
	}
}

RacePlayer* RaceState::getPlayer(ZCom_ConnID id) {
	playermap::iterator i = mPlayers.find(id);
	return (i != mPlayers.end()) ? i->second : 0;
}

void RaceState::addListener(RaceStateListener* listener) {
	mListeners.push_back(listener);
}

void RaceState::removeListener(RaceStateListener* listener) {
	std::vector<RaceStateListener*>::const_iterator it = mListeners.begin();

	while (it != mListeners.end()) {
		if ((*it) == listener) {
			mListeners.erase(it);
			return;
		}

		++it;
	}
}

std::vector<RaceStateListener*>& RaceState::getListeners() {
	return mListeners;
}

void RaceState::onLoading() {
	if (mServer) {
		// Load the track on the server
		mLoader->load(mTrackFilename);
	} else {
		// Load the track on the client
		((ClientPreparationLoader*) mLoader)->registerLoader(mTrackFilename);
	}
}

void RaceState::onLoaded() {
	Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "[RaceState]: Sending loaded event";
	// Send event to server indicating that the loading finished
	sendRaceStateEvent(LOADED);
}

void RaceState::setNewState(States state) {
	Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "[RaceState]: New state is " << state;
	mCurrentState = state;

	// Do the appropriate action for this state
	switch (state) {
	case LOADING:
		onLoading();
		break;
	default:
		break;
	}

	if (mNode->getRole() == eZCom_RoleAuthority) {
		// Send the event to the clients
		StateEvent newState((unsigned int) state);
		sendEvent(newState);
	} else {
		// Notify the listeners
		for (std::vector<RaceStateListener*>::iterator i = mListeners.begin(); i != mListeners.end(); ++i) {
			(*i)->onStateChange(mCurrentState);
		}
	}
}

void RaceState::gotNewEvent(Events event, ZCom_ConnID id) {
	Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "[RaceState]: New event " << event << " from " << id;
	// Check if the event is correct for the current state
	bool correct = false;

	if (((mCurrentState == INITIALIZING) && (event == INITIALIZED)) || ((mCurrentState == LOADING) && (event == LOADED))) {
		correct = true;
	}

	if (correct) {
		mWaitingList.erase(id);

		if (mWaitingList.empty()) {
			switch (mCurrentState) {
			case INITIALIZING:
				setNewState(LOADING);
				setWaitingList();
				break;
			case LOADING:
				setNewState(COUNTDOWN);
				break;
			default:
				break;
			}
		}
	}
}

void RaceState::sendRaceStateEvent(Events event) {
	StateEvent newState((unsigned int) event);
	ZCom_BitStream* stream = new ZCom_BitStream();
	newState.serialize(stream);
	mNode->sendEventDirect(eZCom_ReliableOrdered, stream, ((NetworkClient*) mNode->getControl())->getConnectionID());
}

void RaceState::setWaitingList() {
	mWaitingList.clear();
	for (playermap::const_iterator it = mPlayers.begin(); it != mPlayers.end(); ++it) {
		mWaitingList.insert(it->first);
	}
}

void RaceState::setAnnouncementData(ZCom_BitStream* stream) {
	stream->addString(mTrackFilename.c_str());
}

void RaceState::parseEvents(eZCom_Event type, eZCom_NodeRole remote_role, ZCom_ConnID conn_id, ZCom_BitStream* stream,
		float timeSince) {
	if (type == eZCom_EventUser) {
		GameEventParser p;
		GameEvent* event = p.parse(stream);
		eZCom_NodeRole role = mNode->getRole();

		if (role == eZCom_RoleOwner || role == eZCom_RoleProxy) {
			StateEvent* newState = dynamic_cast<StateEvent*> (event);
			if (newState) {
				setNewState((States) newState->getState());
			}
		} else {
			StateEvent* newState = dynamic_cast<StateEvent*> (event);
			if (newState) {
				gotNewEvent((Events) newState->getState(), conn_id);
			}
		}
		delete event;
	}
}

void RaceState::setupReplication() {
}

std::ostream& operator<<(std::ostream& os, const RaceState::States& state) {
	switch (state) {
	case RaceState::INITIALIZING:
		os << "INITIALIZING";
		break;
	case RaceState::LOADING:
		os << "LOADING";
		break;
	case RaceState::COUNTDOWN:
		os << "COUNTDOWN";
		break;
	case RaceState::RACING:
		os << "RACING";
		break;
	case RaceState::FINISHING:
		os << "FINISHING";
		break;
	case RaceState::CLEANUP:
		os << "CLEANUP";
		break;
	default:
		os << state;
		break;
	}
	return os;
}

std::ostream& operator<<(std::ostream& os, const RaceState::Events& event) {
	switch (event) {
	case RaceState::INITIALIZED:
		os << "INITIALIZED";
		break;
	case RaceState::LOADED:
		os << "LOADED";
		break;
	default:
		os << event;
		break;
	}
	return os;
}

}
