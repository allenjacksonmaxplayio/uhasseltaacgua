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
#include "InitEvent.h"
#include "NetworkClient.h"
#include "Timing.h"
#include "Track.h"
#include "Entity.h"
#include "EntityManager.h"
#include "DedicatedServer.h"
#include "TrackInfoLoader.h"
#include "Finish.h"
#include "Start.h"
#include "Hovercraft.h"
#include "CheckPoint.h"
#include <math.h>

#include <OgreLogManager.h>

namespace HovUni {

RaceState::RaceState(Lobby* lobby, Loader* loader, Ogre::String track) :
	NetworkEntity(0), mNumberPlayers(0), mState(0), mServer(true), mLobby(lobby), mLoader(loader), mTrackFilename(track),
			mCountdown(-1), mCountdownInterval(5000), mCountdownIntervalLog2(13), mFinishID(-1) {
	mState = new SystemState(this);

	if (mLoader) {
		mLoader->setRaceState(this);
	}

	// Add as network entity
	networkRegister(NetworkIDManager::getServerSingletonPtr(), getClassName(), true);

	// Load track info and check players
	TrackInfoLoader trackInfoLoader(lobby->getTrackFilename());
	Track * trackEntity = trackInfoLoader.getTrack();
	if (trackEntity) {
		Ogre::LogManager::getSingletonPtr()->getDefaultLog()->stream() << "Track " << trackEntity->getDisplayName()
				<< " must have at least " << trackEntity->getMinimumPlayers() << " players and at most "
				<< trackEntity->getMaximumPlayers() << "!";

		unsigned int maxPlayers = trackEntity->getMaximumPlayers();
		unsigned int minPlayers = trackEntity->getMinimumPlayers();

		// Create race players
		const Lobby::playermap::list_type& playersettings = lobby->getPlayers();

		for (Lobby::playermap::const_iterator it = playersettings.begin(); it != playersettings.end()
				|| mPlayers.getPlayers().size() > maxPlayers; ++it) {
			RacePlayer* rplayer = new RacePlayer(this, it->second);
			rplayer->getNetworkNode()->setOwner(it->first, true);
			addPlayer(rplayer);
		}

		// Bots
		int bots = 0;
		if (mLobby->hasBots()) {
			bots = (mLobby->getMaxPlayers() < maxPlayers ? mLobby->getMaxPlayers() : maxPlayers) - mPlayers.getPlayers().size();
		} else if (minPlayers > mPlayers.getPlayers().size()) {
			// The minimum amount of players is not reached so add bots anyway
			bots = minPlayers - mPlayers.getPlayers().size();
		}

		for (int i = 0; i < bots; ++i) {
			PlayerSettings* settings = new PlayerSettings(mLobby, "Bot");
			RacePlayer* rplayer = new RacePlayer(this, settings);
			addPlayer(rplayer);
		}

	}
}

RaceState::RaceState(Lobby* lobby, ClientPreparationLoader* loader, ZCom_BitStream* announcementdata, ZCom_ClassID id,
		ZCom_Control* control) :
	NetworkEntity(0), mNumberPlayers(0), mState(0), mServer(false), mLobby(lobby), mLoader(loader), mTrackFilename(
			announcementdata->getString()), mCountdown(-1), mCountdownInterval(5000), mCountdownIntervalLog2(13), mFinishID(-1) {

	mState = new SystemState(this);

	if (mLoader) {
		mLoader->setRaceState(this);
	}

	// Add as network entity
	networkRegister(id, control);
}

RaceState::~RaceState() {
	// Delete the system state
	delete mState;

	// Delete all the players
	for (playermap::iterator it = mPlayers.begin(); it != mPlayers.end();) {
		if (it->second->isBot()) {
			PlayerSettings* settings = it->second->getSettings();
			it = removePlayer(it);
			delete settings;
		} else {
			it = removePlayer(it);
		}
	}
}

void RaceState::onFinish(Finish * finish, unsigned int playerid) {
	
	if (mFinishID == -1) {
		// finish checkpoint
		std::vector<Entity*> checkpoints = EntityManager::getServerSingletonPtr()->getEntities(CheckPoint::CATEGORY);
		for (unsigned int i = 0; i < checkpoints.size(); ++i) {
			CheckPoint * checkpoint = dynamic_cast<CheckPoint *>(checkpoints[i]);
			if (checkpoint->getNumber() >= mFinishID) {
				mFinishID = checkpoint->getNumber() + 1;
			}
		}
		std::cout << "finish ID is " << mFinishID << std::endl;
	}
	
	
	if (mCheckpointMapping[playerid] == mFinishID) {
		// finished!
		std::cout << playerid << " finished!" << std::endl;
		// increase next checkpoint
		mCheckpointMapping[playerid]++;
		// change state to finishing
		if (mState->getState() == RACING) {
			mState->newState(FINISHING);
		}
		// disable controls for this player
		// TODO (or maybe not?)
	} else if (mCheckpointMapping[playerid] < mFinishID) {
		// not yet finished!
		std::cout << playerid << " reaches incorrect finish, skipped checkpoint " << mCheckpointMapping[playerid] << std::endl;
	} else {
		// already finished
		std::cout << playerid << " already finished" << std::endl;
	}

}

void RaceState::onCheckPoint(CheckPoint * checkpoint, unsigned int playerid) {
	if (mCheckpointMapping[playerid] == checkpoint->getNumber()) {
		// correct checkpoint
		std::cout << playerid << " reaches correct checkpoint " << checkpoint->getNumber() << std::endl;
		// increase next checkpoint
		mCheckpointMapping[playerid]++;
	} else {
		// incorrect checkpoint
		std::cout << playerid << " reaches wrong checkpoint " << checkpoint->getNumber() << " (should be " <<  mCheckpointMapping[playerid] << ")" << std::endl;
	}
}

void RaceState::onStart(Start * start, unsigned int playerid) {
	if (mCheckpointMapping[playerid] == -1) {
		// correct start
		std::cout << playerid << " reaches start" << std::endl;
		mCheckpointMapping[playerid] = 0;
	} else {
		// already passed start!
		std::cout << playerid << " reaches invalid start" << std::endl;
	}
}

std::string RaceState::getClassName() {
	return "RaceState";
}

void RaceState::process() {
	processEvents(0.0f);

	mState->update();

	for (playermap::iterator it = mPlayers.begin(); it != mPlayers.end();) {
		unsigned int id = it->first;
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

	// Decrease the number of players
	--mNumberPlayers;

	return mPlayers.removePlayerByIterator(i);
}

void RaceState::addPlayer(RacePlayer* player, bool ownPlayer) {
	mPlayers.addPlayer(player->getSettings()->getID(), player, ownPlayer);
	mCheckpointMapping[player->getSettings()->getID()] = -1;
	Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "[RaceState]: Inserting new RacePlayer";
	if (ownPlayer) {
		Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "[RaceState]: Received own player object";
	}

	if ((mState->getState() == INITIALIZING)) {
		if (mServer) {
			++mNumberPlayers;
		} else {
			onInitialized();
		}
	}
}

void RaceState::removePlayer(unsigned int id) {
	removePlayer(mPlayers.find(id));
}

Listenable<RaceStateListener>::list_type& RaceState::getListeners() {
	return mListeners;
}

RaceState::States RaceState::getState() const {
	return mState->getState();
}

void RaceState::onInitialized() {
	if ((mState->getState() == INITIALIZING) && (mPlayers.getPlayers().size() == mNumberPlayers)) {
		mState->sendEvent(INITIALIZED);
	}
}

void RaceState::onLoaded() {
	if (mState->getState() == LOADING) {
		// Send event to server indicating that the loading finished
		mState->sendEvent(LOADED);
	}
}

void RaceState::setAnnouncementData(ZCom_BitStream* stream) {
	stream->addString(mTrackFilename.c_str());
}

void RaceState::parseEvents(eZCom_Event type, eZCom_NodeRole remote_role, ZCom_ConnID conn_id, ZCom_BitStream* stream,
		float timeSince) {
	if (type == eZCom_EventUser) {
		GameEventParser p;
		GameEvent* gEvent = p.parse(stream);
		eZCom_NodeRole role = mNode->getRole();

		// Check for an init event if this object is just created
		InitEvent* init = dynamic_cast<InitEvent*> (gEvent);
		if (init) {
			ZCom_BitStream* state = init->getStream();
			mNumberPlayers = state->getInt(8);
		}

		if (role == eZCom_RoleOwner || role == eZCom_RoleProxy) {
			StateEvent* newState = dynamic_cast<StateEvent*> (gEvent);
			if (newState) {
				mState->newState((States) newState->getState());
			}
		} else {
			StateEvent* newState = dynamic_cast<StateEvent*> (gEvent);
			if (newState) {
				mState->newEvent((Events) newState->getState(), mLobby->getPlayerIDfromConnectionID(conn_id));
			}
		}
		delete gEvent;
	}

	// A new client received this object so send current state
	if (type == eZCom_EventInit && mNode->getRole() == eZCom_RoleAuthority) {
		ZCom_BitStream* state = new ZCom_BitStream();
		state->addInt(mNumberPlayers, 8);
		sendEventDirect(InitEvent(state), conn_id);
	}
}

void RaceState::setupReplication() {
	mNode->addReplicationInt(&mNumberPlayers, 8, false, ZCOM_REPFLAG_MOSTRECENT, ZCOM_REPRULE_AUTH_2_ALL);
	mNode->addReplicationInt(&mCountdown, mCountdownIntervalLog2, false, ZCOM_REPFLAG_MOSTRECENT, ZCOM_REPRULE_AUTH_2_ALL, 250,
			1000);
}

RaceState::SystemState::SystemState(RaceState* racestate) :
	mRaceState(racestate), mCurrentState(INITIALIZING), mStartOfState(false), mTimer(0) {
	if (mRaceState->mServer) {
		setWaitingList();
	}
}

void RaceState::SystemState::update() {
	if (mRaceState->mServer) {
		switch (mCurrentState) {
		case INTRO:
			if (mTimer->elapsed() >= DedicatedServer::getConfig()->getValue<int> ("Server", "IntroTime", 1000)) {
				newState(COUNTDOWN);
			}
		case COUNTDOWN:
			if (mTimer->elapsed() >= mRaceState->mCountdownInterval) {
				newState(RACING);
				Entity::setControlsActive();
			} else {
				mRaceState->mCountdown = mRaceState->mCountdownInterval - mTimer->elapsed();
			}
			break;
		case RACING:
			if (mTimer->elapsed() >= DedicatedServer::getConfig()->getValue<int> ("Server", "PlayTime", 15000)) {
				newState(FINISHING);
			}
			break;
		case FINISHING:
			if (mTimer->elapsed() >= DedicatedServer::getConfig()->getValue<int> ("Server", "FinishTime", 30000)) {
				newState(CLEANUP);
				Entity::setControlsInactive();
			}
			break;
		default:
			break;
		}
	}
}

RaceState::States RaceState::SystemState::getState() const {
	return mCurrentState;
}

void RaceState::SystemState::newState(States state) {
	Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "[RaceState]: New state is " << state;
	mCurrentState = state;

	if (mRaceState->mServer) {
		// Send the event to the clients
		StateEvent newState((unsigned int) state);
		mRaceState->sendEvent(newState);

		// Do the appropriate action for this state
		switch (state) {
		case LOADING:
			mStartOfState = true;
			break;
		case INTRO:
			mTimer = new Timing();
			break;
		case COUNTDOWN:
			mTimer->restart();
			break;
		case RACING:
			mTimer->restart();
			break;
		case FINISHING:
			mTimer->restart();
			break;
		default:
			break;
		}
	}
	// Client
	else {
		// Do the appropriate action for this state
		switch (state) {
		case LOADING:
			onLoading();
			break;
		default:
			break;
		}

		// Notify the listeners
		for (listener_iterator i = mRaceState->listenersBegin(); i != mRaceState->listenersEnd(); ++i) {
			(*i)->onStateChange(mCurrentState);
		}
	}
}

void RaceState::SystemState::newEvent(Events events, unsigned int id) {
	Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "[RaceState]: New event " << events << " from " << id;
	// Check if the event is correct for the current state
	bool correct = false;

	if (((mCurrentState == INITIALIZING) && (events == INITIALIZED)) || ((mCurrentState == LOADING) && (events == STATECHANGED))
			|| ((mCurrentState == LOADING) && (events == LOADED))) {
		correct = true;
	}

	if (correct) {
		eraseFromList(id);
	}

}

void RaceState::SystemState::sendEvent(Events events) {
	StateEvent newState((unsigned int) events);
	ZCom_BitStream* stream = new ZCom_BitStream();
	newState.serialize(stream);
	ZCom_ConnID id = ((NetworkClient*) mRaceState->mNode->getControl())->getConnectionID();
	mRaceState->mNode->sendEventDirect(eZCom_ReliableOrdered, stream, id);
	Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "[RaceState]: sent " << events << " event";
}

void RaceState::SystemState::onLoading() {
	if (mRaceState->mServer) {
		// Load the track on the server
		mRaceState->mLoader->load(mRaceState->mTrackFilename);
	} else {
		sendEvent(STATECHANGED);
		// Start waiting for loading the entities
		((ClientPreparationLoader*) mRaceState->mLoader)->registerLoader(mRaceState->mTrackFilename);
	}
}

void RaceState::SystemState::setWaitingList() {
	if (mRaceState->mServer) {
		mWaitingList.clear();
		for (playermap::const_iterator it = mRaceState->mPlayers.begin(); it != mRaceState->mPlayers.end(); ++it) {
			if (!it->second->isBot()) {
				mWaitingList.insert(it->first);
			}
		}
	}
}

void RaceState::SystemState::eraseFromList(unsigned int id) {
	mWaitingList.erase(id);

	if (mWaitingList.empty()) {
		switch (mCurrentState) {
		case INITIALIZING:
			setWaitingList();
			newState(LOADING);
			break;
		case LOADING:
			if (mStartOfState) {
				mStartOfState = false;
				setWaitingList();
				onLoading();
			} else {
				newState(INTRO);
			}
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
	case RaceState::INTRO:
		os << "INTRO";
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

std::ostream& operator<<(std::ostream& os, const RaceState::Events& events) {
	switch (events) {
	case RaceState::INITIALIZED:
		os << "INITIALIZED";
		break;
	case RaceState::LOADED:
		os << "LOADED";
		break;
	case RaceState::STATECHANGED:
		os << "STATECHANGED";
		break;
	default:
		os << events;
		break;
	}
	return os;
}

}
