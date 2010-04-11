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
#include "InitEvent.h"
#include "OnJoinEvent.h"
#include "OnLeaveEvent.h"

#include <OgreLogManager.h>

namespace HovUni {

std::string Lobby::getClassName() {
	return "Lobby";
}

Lobby::Lobby(Loader * loader) :
	NetworkEntity(5), mLoader(loader), mHasAdmin(false), mAdmin(-1), mTrackFilename("SimpleTrack.scene"), mMaximumPlayers(12),
			mCurrentPlayers(0), mRaceState(0), mBots(false) {

	this->setReplicationInterceptor(this);
}

Lobby::~Lobby() {
	// Delete the loader
	delete mLoader;

	// Delete the race state
	delete mRaceState;

	// Delete all the players
	for (playermap::iterator it = mPlayers.begin(); it != mPlayers.end();) {
		it = removePlayer(it);
	}
}

void Lobby::process() {
	processEvents(0.0f);
	for (playermap::iterator it = mPlayers.begin(); it != mPlayers.end();) {
		ZCom_ConnID id = it->first;
		PlayerSettings* settings = it->second;

		// Check if this settings wasn't deleted in the mean time
		if (settings->isDeleted()) {
			//Notify our listeners
			for (listener_iterator i = listenersBegin(); i != listenersEnd(); ++i) {
				(*i)->onLeave(settings->getID());
			}
			it = removePlayer(it);
		} else {
			settings->processEvents(0.0f);
			++it;
		}
	}

	if (mRaceState) {
		mRaceState->process();
	}
}

void Lobby::removePlayer(ZCom_ConnID id) {
	removePlayer(mPlayers.find(id));
}

Lobby::playermap::iterator Lobby::removePlayer(playermap::iterator i) {
	--mCurrentPlayers;

	// If there is a race state, also delete the race player
	if (mRaceState) {
		mRaceState->removePlayer(i->first);
	}

	return mPlayers.removePlayerByIterator(i);
}

void Lobby::addPlayer(PlayerSettings * settings, bool ownPlayer) {
	mPlayers.addPlayer(settings->getID(), settings, ownPlayer);

	//Notify our listeners
	for (listener_iterator i = listenersBegin(); i != listenersEnd(); ++i) {
		(*i)->onJoin(settings);
	}

	if (ownPlayer) {
		Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "[Lobby]: Received own player object";
	} else {
		Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "[Lobby]: Inserting PlayerSettings of other player";
	}
}

void Lobby::start() {
	StartTrackEvent event;
	sendEvent(event);
}

bool Lobby::isAdmin() const {
	return (mPlayers.getOwnPlayer() && mPlayers.getOwnPlayer()->getID() == mAdmin);
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
}

void Lobby::onDisconnect(ZCom_ConnID id, const std::string& reason) {
	//TODO lock mutex

	// Remove from map
	removePlayer(id);

	// Check if new admin is needed
	if (mAdmin == id) {

		// Check if players remain
		if (mPlayers.getPlayers().empty()) {
			// Set admin to false if no player remain
			mHasAdmin = false;

			// There are no players so we can remove the race state if there is one
			if (mRaceState) {
				delete mRaceState;
				mRaceState = 0;
				Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "[Lobby]: Closed race and ready to allow new players";
			}
		} else {
			// Set new admin
			mAdmin = mPlayers.begin()->first;
			getNetworkNode()->setOwner(mAdmin, true);
		}
	}
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
		Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "[Lobby]: Racestate constructing and ready process events";
	}
}

void Lobby::onStartClient() {

	// TODO Is this allowable Nick?
	int currSize = mListeners.size();

	for (int i = 0; i < currSize; ++i) {
		mListeners[i]->onStart();

		//Listeners might have been removed
		if (currSize != mListeners.size()) {
			currSize = mListeners.size();
			--i;
		}
	}
}

void Lobby::parseEvents(eZCom_Event type, eZCom_NodeRole remote_role, ZCom_ConnID conn_id, ZCom_BitStream* stream,
		float timeSince) {
	if (type == eZCom_EventUser) {
		GameEventParser p;
		GameEvent* event = p.parse(stream);

		// Check for an init event if this object is just created
		InitEvent* init = dynamic_cast<InitEvent*> (event);
		if (init) {
			Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "[Lobby]: Received initial lobby information";
			ZCom_BitStream* state = init->getStream();
			mAdmin = state->getInt(sizeof(ZCom_ConnID) * 8);
			mMaximumPlayers = state->getInt(8);
			mCurrentPlayers = state->getInt(8);
			mTrackFilename = state->getString();
			mBots = state->getBool();
		}

		// Process the events
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

		delete event;
	}

	// A new client received this object so send current state
	if (type == eZCom_EventInit && mNode->getRole() == eZCom_RoleAuthority) {
		Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "[Lobby]: New client requested Lobby";
		ZCom_BitStream* state = new ZCom_BitStream();
		state->addInt(mAdmin, sizeof(ZCom_ConnID) * 8);
		state->addInt(mMaximumPlayers, 8);
		state->addInt(mCurrentPlayers, 8);
		state->addString(mTrackFilename.c_str());
		state->addBool(mBots);
		sendEventDirect(InitEvent(state), conn_id);
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
			ZCOM_REPRULE_OWNER_2_AUTH | ZCOM_REPRULE_AUTH_2_ALL // server sends to all clients, but owner can send to server
	);

	//Replicate the setting for filling with bots
	mNode->addReplicationBool(&mBots, ZCOM_REPFLAG_MOSTRECENT, ZCOM_REPRULE_OWNER_2_AUTH | ZCOM_REPRULE_AUTH_2_ALL);
}

void Lobby::setAnnouncementData(ZCom_BitStream* stream) {

}

void Lobby::inPostUpdate(ZCom_Node *_node, ZCom_ConnID _from, eZCom_NodeRole _remote_role, zU32 _rep_bits, zU32 _event_bits,
		zU32 _meta_bits) {
	Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "[Lobby]: Lobby update";
	if (this->isAdmin()) {
		Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "[Lobby]: Lobby ADMIN";
	}
	//Something has changed in the lobby, inform our listeners
	for (listener_iterator i = listenersBegin(); i != listenersEnd(); i++) {
		(*i)->onAdminChange(this->isAdmin());
		(*i)->onBotsChange(this->hasBots());
		(*i)->onMaxPlayersChange(this->getMaxPlayers());
	}
}

}
