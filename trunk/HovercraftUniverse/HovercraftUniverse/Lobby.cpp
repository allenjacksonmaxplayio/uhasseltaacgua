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
#include "DedicatedServer.h"

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
NetworkEntity(5), mLoader(loader), mHasAdmin(false), mAdmin(-1), mTrack(0), mMaximumPlayers(DedicatedServer::getConfig()->getValue<int>("Server", "MaximumPlayers", 12)),
			mCurrentPlayers(0), mRaceState(0), mBots(DedicatedServer::getConfig()->getValue<bool>("Server", "FillWithBots", false)) {

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
		unsigned int id = it->first;
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
		if (mRaceState->isDone()) {
			Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "[Lobby]: deleting race state";
			deleteRaceState();
		}
	}
}

void Lobby::removePlayer(unsigned int id) {
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

unsigned int Lobby::getPlayerIDfromConnectionID(ZCom_ConnID connID) const {
	for (playermap::const_iterator it = mPlayers.begin(); it != mPlayers.end(); ++it) {
		if (it->second->getConnID() == connID) {
			return it->first;
		}
	}
	return 0;
}


void Lobby::start() {
	StartTrackEvent startEvent;
	sendEvent(startEvent);
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
	return (mCurrentPlayers < mMaximumPlayers) && !getRaceState();
}

void Lobby::onConnect(ZCom_ConnID id) {
	PlayerSettings* newPlayer = new PlayerSettings(this, id);

	// Request extra info
	if (!mHasAdmin) {
		mAdmin = newPlayer->getID();
		getNetworkNode()->setOwner(id, true);
		mHasAdmin = true;
	}

	// Add player to map
	addPlayer(newPlayer);
	mCurrentPlayers++;

	Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "[Lobby]: New player joined with id " << newPlayer->getID();
}

void Lobby::onDisconnect(ZCom_ConnID id, const std::string& reason) {
	unsigned int playerID = getPlayerIDfromConnectionID(id);

	// Remove from map
	removePlayer(playerID);

	// Check if new admin is needed
	if (mAdmin == playerID) {

		// Check if players remain
		if (mPlayers.getPlayers().empty()) {
			// Set admin to false if no player remain
			mHasAdmin = false;

			// There are no players so we can remove the race state if there is one
			if (mRaceState) {
				deleteRaceState();
			}
		} else {
			// Set new admin
			PlayerSettings* newAdmin = mPlayers.begin()->second;
			mAdmin = newAdmin->getID();
			getNetworkNode()->setOwner(newAdmin->getConnID(), true);
		}
	}
}

void Lobby::onStartServer() {
	if (!getRaceState()) {

		//TODO GET FROM TRACK ID
		Ogre::String trackfile = "SimpleTrack2.scene";

		RaceState* racestate = new RaceState(this, mLoader, trackfile);
		setRaceState(racestate);

		// Tell the clients to start
		StartTrackEvent startEvent;
		sendEvent(startEvent);
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

void Lobby::deleteRaceState() {
	delete mRaceState;
	mRaceState = 0;
	Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "[Lobby]: Closed race and ready to allow new players";
}

void Lobby::parseEvents(eZCom_Event type, eZCom_NodeRole remote_role, ZCom_ConnID conn_id, ZCom_BitStream* stream,
		float timeSince) {
	if (type == eZCom_EventUser) {
		GameEventParser p;
		GameEvent* gEvent = p.parse(stream);

		// Check for an init event if this object is just created
		InitEvent* init = dynamic_cast<InitEvent*> (gEvent);
		if (init) {
			Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "[Lobby]: Received initial lobby information";
			ZCom_BitStream* state = init->getStream();
			mAdmin = state->getInt(sizeof(unsigned int) * 8);
			mMaximumPlayers = state->getInt(8);
			mCurrentPlayers = state->getInt(8);
			mTrack = state->getInt(8);
			mBots = state->getBool();
		}

		// Process the events
		eZCom_NodeRole role = mNode->getRole();
		switch (role) {
		case eZCom_RoleAuthority:
			processEventsServer(gEvent);
			break;
		case eZCom_RoleOwner:
			processEventsOwner(gEvent);
			break;
		case eZCom_RoleProxy:
			processEventsOther(gEvent);
			break;
		default:
			break;
		}

		delete gEvent;
	}

	// A new client received this object so send current state
	if (type == eZCom_EventInit && mNode->getRole() == eZCom_RoleAuthority) {
		Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "[Lobby]: New client requested Lobby";
		ZCom_BitStream* state = new ZCom_BitStream();
		state->addInt(mAdmin, sizeof(unsigned int) * 8);
		state->addInt(mMaximumPlayers, 8);
		state->addInt(mCurrentPlayers, 8);
		state->addInt(mTrack,8);
		state->addBool(mBots);
		sendEventDirect(InitEvent(state), conn_id);
	}

}

void Lobby::processEventsServer(GameEvent* gEvent) {
	// Save the new event in the moving status
	StartTrackEvent* start = dynamic_cast<StartTrackEvent*> (gEvent);
	if (start) {
		onStartServer();
	}
}

void Lobby::processEventsOwner(GameEvent* gEvent) {
	// Save the new event in the moving status
	StartTrackEvent* start = dynamic_cast<StartTrackEvent*> (gEvent);
	if (start) {
		onStartClient();
	}
}

void Lobby::processEventsOther(GameEvent* gEvent) {
	// Save the new event in the moving status
	StartTrackEvent* start = dynamic_cast<StartTrackEvent*> (gEvent);
	if (start) {
		onStartClient();
	}
}

void Lobby::setupReplication() {

	//mCurrentPlayers
	mNode->addReplicationInt((int*) &mTrack, // pointer to the variable
			8, // amount of bits(up to 255 maps)
			false, // unsigned
			ZCOM_REPFLAG_MOSTRECENT, // always send the most recent value only
			ZCOM_REPRULE_OWNER_2_AUTH | ZCOM_REPRULE_AUTH_2_ALL // server sends to all clients, but owner can send to server
	);

	//mAdmin
	mNode->addReplicationInt((zS32*) &mAdmin, // pointer to the variable
			sizeof(unsigned int) * 8, // amount of bits(full)
			false, // unsigned
			ZCOM_REPFLAG_MOSTRECENT, // always send the most recent value only
			ZCOM_REPRULE_AUTH_2_ALL // server sends to all clients
	);

	//mCurrentPlayers
	mNode->addReplicationInt((int*) &mCurrentPlayers, // pointer to the variable
			8, // amount of bits(up to 255 players)
			false, // unsigned
			ZCOM_REPFLAG_MOSTRECENT, // always send the most recent value only
			ZCOM_REPRULE_AUTH_2_ALL // server sends to all clients
	);

	//mMaximumPlayers
	mNode->addReplicationInt((int*) &mMaximumPlayers, // pointer to the variable
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
		(*i)->onTrackChange(this->getTrackId());
	}
}

}
