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
	NetworkEntity(0), mState(0), mServer(true), mLobby(lobby), mLoader(loader), mTrackFilename(track) {
	mState = new SystemState(this);

	if (mLoader) {
		mLoader->setRaceState(this);
	}

	// Add as network entity
	networkRegister(NetworkIDManager::getServerSingletonPtr(), getClassName(), true);

	// Create race players
	const Lobby::playermap::list_type& playersettings = lobby->getPlayers();

	for (Lobby::playermap::const_iterator it = playersettings.begin(); it != playersettings.end(); ++it) {
		RacePlayer* rplayer = new RacePlayer(this, it->second);
		addPlayer(rplayer);
	}

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
	NetworkEntity(0), mState(0), mServer(false), mLobby(lobby), mLoader(loader), mTrackFilename(announcementdata->getString()) {
	mState = new SystemState(this);
	if (mLoader) {
		mLoader->setRaceState(this);
		loader->getInternalLoader()->setRaceState(this);
	}

	// Add as network entity
	networkRegister(id, control);
}

RaceState::~RaceState() {
	// Delete the system state
	delete mState;

	// Delete all the players
	for (playermap::iterator it = mPlayers.begin(); it != mPlayers.end();) {
		it = removePlayer(it);
	}
}

std::string RaceState::getClassName() {
	return "RaceState";
}

void RaceState::process() {
	processEvents(0.0f);

	mState->update();

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

RaceState::playermap::iterator RaceState::removePlayer(playermap::iterator i) {
	// Remove the ID from the waiting list
	mState->eraseFromList(i->first);

	return mPlayers.removePlayerByIterator(i);
}

void RaceState::addPlayer(RacePlayer* player, bool ownPlayer) {
	mPlayers.addPlayer(player->getSettings()->getID(), player, ownPlayer);
	Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "[RaceState]: Inserting new RacePlayer";
	if (ownPlayer) {
		Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "[RaceState]: Received own player object";
	}
}

void RaceState::removePlayer(ZCom_ConnID id) {
	removePlayer(mPlayers.find(id));
}

Listenable<RaceStateListener>::list_type& RaceState::getListeners() {
	return mListeners;
}

void RaceState::onLoaded() {
	Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "[RaceState]: Sending loaded event";
	// Send event to server indicating that the loading finished
	mState->sendEvent(LOADED);
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
				mState->newState((States) newState->getState());
			}
		} else {
			StateEvent* newState = dynamic_cast<StateEvent*> (event);
			if (newState) {
				mState->newEvent((Events) newState->getState(), conn_id);
			}
		}
		delete event;
	}
}

void RaceState::setupReplication() {

}

RaceState::SystemState::SystemState(RaceState* racestate) :
	mRaceState(racestate), mCurrentState(INITIALIZING), mInitialized(false) {
		if (mRaceState->mServer) {
			setWaitingList();
		}
}

void RaceState::SystemState::update() {
	if (!mRaceState->mServer && !mInitialized && (mCurrentState == INITIALIZING)) {
		// Send the event to indicate that the race state was initialized
		sendEvent(INITIALIZED);
		mInitialized = true;

		// Start waiting for loading the entities
		((ClientPreparationLoader*) mRaceState->mLoader)->registerLoader(mRaceState->mTrackFilename);
	}
}

RaceState::States RaceState::SystemState::getState() const {
	return mCurrentState;
}

void RaceState::SystemState::newState(States state) {
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

	if (mRaceState->mServer) {
		// Send the event to the clients
		StateEvent newState((unsigned int) state);
		mRaceState->sendEvent(newState);
	} else {
		// Notify the listeners
		for (listener_iterator i = mRaceState->listenersBegin(); i != mRaceState->listenersEnd(); ++i) {
			(*i)->onStateChange(mCurrentState);
		}
	}
}

void RaceState::SystemState::newEvent(Events event, ZCom_ConnID id) {
	Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "[RaceState]: New event " << event << " from " << id;
	// Check if the event is correct for the current state
	bool correct = false;

	if (((mCurrentState == INITIALIZING) && (event == INITIALIZED)) || ((mCurrentState == LOADING) && (event == LOADED))) {
		correct = true;
	}

	if (correct) {
		eraseFromList(id);
	}

}

void RaceState::SystemState::sendEvent(Events event) {
	StateEvent newState((unsigned int) event);
	ZCom_BitStream* stream = new ZCom_BitStream();
	newState.serialize(stream);
	ZCom_ConnID id = ((NetworkClient*) mRaceState->mNode->getControl())->getConnectionID();
	mRaceState->mNode->sendEventDirect(eZCom_ReliableOrdered, stream, id);
}

void RaceState::SystemState::onLoading() {
	if (mRaceState->mServer) {
		// Load the track on the server
		mRaceState->mLoader->load(mRaceState->mTrackFilename);
	} else {
		// The client track is already waiting for loading
	}
}

void RaceState::SystemState::setWaitingList() {
	if (mRaceState->mServer) {
		mWaitingList.clear();
		for (playermap::const_iterator it = mRaceState->mPlayers.begin(); it != mRaceState->mPlayers.end(); ++it) {
			mWaitingList.insert(it->first);
		}
	}
}

void RaceState::SystemState::eraseFromList(ZCom_ConnID id) {
	mWaitingList.erase(id);

	if (mWaitingList.empty()) {
		switch (mCurrentState) {
		case INITIALIZING:
			newState(LOADING);
			setWaitingList();
			break;
		case LOADING:
			newState(COUNTDOWN);
			break;
		default:
			break;
		}
	}

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