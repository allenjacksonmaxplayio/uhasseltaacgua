#include "Lobby.h"
#include "EntityManager.h"
#include "NetworkIDManager.h"
#include "String_Replicator.h"
#include "GameEventParser.h"
#include "Loader.h"

#include "LobbyListener.h"
#include "PlayerSettings.h"
#include "RaceState.h"
#include "RacePlayer.h"

//Events
#include "OnJoinEvent.h"
#include "OnLeaveEvent.h"

#include <OgreLogManager.h>

namespace HovUni {

std::string Lobby::getClassName() {
	return "Lobby";
}

Lobby::Lobby(Loader * loader) :
	NetworkEntity(4), mLoader(loader), mHasAdmin(false), mAdmin(-1), mTrackFilename("SimpleTrack.scene"),
			mMaximumPlayers(12), mCurrentPlayers(0), mOwnPlayer(0), mRaceState(0) {

	if (loader) {
		loader->setLobby(this);
	}
}

Lobby::~Lobby() {
	if (mLoader)
		delete mLoader;
}

void Lobby::process() {
	processEvents(0.0f);
	for (playermap::iterator it = mPlayers.begin(); it != mPlayers.end();) {
		PlayerSettings* settings = it->second;

		// Check if this settings wasn't deleted in the mean time
		if (settings->isDeleted()) {
			//Notify our listeners
			for (std::list<LobbyListener*>::iterator i = mListeners.begin(); i != mListeners.end(); ++i) {
				(*i)->onLeave(settings->getID());
			}
			it = mPlayers.erase(it);
		} else {
			settings->processEvents(0.0f);
			++it;
		}
	}
	if (mRaceState) {
		mRaceState->processEvents(0.0f);
	}
}

void Lobby::removePlayer(ZCom_ConnID id) {
	playermap::iterator i = mPlayers.find(id);
	delete i->second;
	mPlayers.erase(i);
	mCurrentPlayers--;
}

void Lobby::addPlayer(PlayerSettings * settings, bool ownPlayer) {
	playermap::iterator i = mPlayers.find(settings->getID());

	if (i != mPlayers.end()) {
		removePlayer(settings->getID());
	}
	mPlayers.insert(std::pair<ZCom_ConnID, PlayerSettings*>(settings->getID(), settings));

	// Set own player
	if (ownPlayer) {
		mOwnPlayer = settings;
		Ogre::LogManager::getSingleton().getDefaultLog()->stream()
				<< "[Lobby]: Received own player object";
	} else {
		Ogre::LogManager::getSingleton().getDefaultLog()->stream()
				<< "[Lobby]: Inserting PlayerSettings of other player";
	}

	//Notify our listeners
	for (std::list<LobbyListener*>::iterator i = mListeners.begin(); i != mListeners.end(); ++i) {
		(*i)->onJoin(settings);
	}
}

PlayerSettings* Lobby::getPlayer(ZCom_ConnID id) {
	playermap::iterator i = mPlayers.find(id);
	return (i != mPlayers.end()) ? i->second : 0;
}

void Lobby::addListener(LobbyListener* listener) {
	mListeners.push_back(listener);
}

void Lobby::removeListener(LobbyListener* listener) {
	mListeners.remove(listener);
}

void Lobby::start() {
	StartTrackEvent event;
	sendEvent(event);
}

bool Lobby::isAdmin() const {
	return (mOwnPlayer && mOwnPlayer->getID() == mAdmin);
}

void Lobby::setRaceState(RaceState* state) {
	if (mRaceState) {
		delete mRaceState;
	}
	mRaceState = state;
}

RaceState* Lobby::getRaceState() {
	return mRaceState;
}

bool Lobby::onConnectAttempt(ZCom_ConnID id) {
	//TODO lock mutex
	return (mCurrentPlayers < mMaximumPlayers) && !getRaceState();
}

void Lobby::onConnect(ZCom_ConnID id) {
	//TODO lock mutex

	// Request extra info
	if (!mHasAdmin) {
		mAdmin = id;
		getNetworkNode()->setOwner(mAdmin, true);
		mHasAdmin = true;
	}

	// Add player to map
	addPlayer(new PlayerSettings(this, id));
	mCurrentPlayers++;
	Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "[Lobby]: New player joined with id " << id;

	//Send Event to players and self
	OnJoinEvent event(id);
	sendEvent(event);
}

void Lobby::onDisconnect(ZCom_ConnID id) {
	//TODO lock mutex

	// Remove from map
	removePlayer(id);

	// Check if new admin is needed
	if (mAdmin == id) {

		// Check if players remain
		if (mPlayers.empty()) {
			// Set admin to false if no player remain
			mHasAdmin = false;
		} else {
			// Set new admin
			mAdmin = mPlayers.begin()->first;
			getNetworkNode()->setOwner(mAdmin, true);
		}
	}

	//Send Event to players and self
	OnLeaveEvent event(id);
	sendEvent(event);
}

void Lobby::onTrackChange(const Ogre::String& filename) {
	mTrackFilename = filename;
}

void Lobby::onStartServer() {
	if (!getRaceState()) {
		RaceState* racestate = new RaceState(this, mLoader, mTrackFilename);
		setRaceState(racestate);

		// Tell the clients to start
		StartTrackEvent event;
		sendEvent(event);
		Ogre::LogManager::getSingleton().getDefaultLog()->stream()
				<< "[Lobby]: Racestate constructing and ready process events";
	}
}

void Lobby::onStartClient() {
	for (std::list<LobbyListener*>::iterator i = mListeners.begin(); i != mListeners.end(); i++) {
		(*i)->onStart();
	}
}

void Lobby::parseEvents(eZCom_Event type, eZCom_NodeRole remote_role, ZCom_ConnID conn_id,
		ZCom_BitStream* stream, float timeSince) {
	if (type == eZCom_EventUser) {
		GameEventParser p;
		GameEvent* event = p.parse(stream);
		eZCom_NodeRole role = mNode->getRole();

		switch (role) {
		case eZCom_RoleAuthority:
			processEventsServer(event);
			break;
		case eZCom_RoleOwner:
			processEventsOwner(event);
			break;
		case eZCom_RoleProxy:
			processEventsOther(event);
			break;
		default:
			break;
		}

		//General events needed for all
		switch (event->getType()) {
		case onLeave: {
			OnLeaveEvent * leaveevent = dynamic_cast<OnLeaveEvent*> (event);
			//propagate to listeners
			for (std::list<LobbyListener*>::iterator i = mListeners.begin(); i != mListeners.end(); i++) {
				(*i)->onLeave(leaveevent->getConnectionId());
			}
			break;
		}
		}

		delete event;
	}
}

void Lobby::processEventsServer(GameEvent* event) {
	// Save the new event in the moving status
	StartTrackEvent* start = dynamic_cast<StartTrackEvent*> (event);
	if (start) {
		onStartServer();
	}
}

void Lobby::processEventsOwner(GameEvent* event) {
	// Save the new event in the moving status
	StartTrackEvent* start = dynamic_cast<StartTrackEvent*> (event);
	if (start) {
		onStartClient();
	}
}

void Lobby::processEventsOther(GameEvent* event) {
	// Save the new event in the moving status
	StartTrackEvent* start = dynamic_cast<StartTrackEvent*> (event);
	if (start) {
		onStartClient();
	}
}

void Lobby::setupReplication() {

	//track filename
	replicateString(&mTrackFilename, ZCOM_REPRULE_OWNER_2_AUTH | ZCOM_REPRULE_AUTH_2_PROXY);

	//mAdmin
	mNode->addReplicationInt((zS32*) &mAdmin, // pointer to the variable
			sizeof(ZCom_ConnID) * 8, // amount of bits(full)
			false, // unsigned
			ZCOM_REPFLAG_MOSTRECENT, // always send the most recent value only
			ZCOM_REPRULE_AUTH_2_ALL // server sends to all clients
	);

	//mCurrentPlayers
	mNode->addReplicationInt(&mCurrentPlayers, // pointer to the variable
			8, // amount of bits(up to 255 players)
			false, // unsigned
			ZCOM_REPFLAG_MOSTRECENT, // always send the most recent value only
			ZCOM_REPRULE_AUTH_2_ALL // server sends to all clients
	);

	//mMaximumPlayers
	mNode->addReplicationInt(&mMaximumPlayers, // pointer to the variable
			8, // amount of bits(up to 255 players)
			false, // unsigned
			ZCOM_REPFLAG_MOSTRECENT, // always send the most recent value only
			ZCOM_REPRULE_AUTH_2_ALL // server sends to all clients
	);
}

void Lobby::setAnnouncementData(ZCom_BitStream* stream) {

}

}
