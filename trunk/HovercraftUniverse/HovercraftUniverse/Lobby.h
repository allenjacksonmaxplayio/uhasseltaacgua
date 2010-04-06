#ifndef LOBBY_H
#define LOBBY_H

#include "NetworkEntity.h"
#include "GameEvent.h"
#include <map>
#include <string>
#include <vector>

namespace HovUni {

class LobbyListener;
class Loader;
class PlayerSettings;
class RaceState;

/**
 * The Lobby which holds the settings of the connected players, assigns an
 * administrator and holds the map info. It also contains a custom loader that is used to load the initial world.
 *
 * @author Olivier Berghmans & Pieter-Jan Pintens
 */
class Lobby: public NetworkEntity, public ZCom_NodeReplicationInterceptor {
public:
	typedef std::map<ZCom_ConnID, PlayerSettings*> playermap;

private:
	//TODO MUTEX PROTECT PLAYERS

	/** The listeners */
	std::vector<LobbyListener*> mListeners;

	/** Specific loader, will be different on client and server **/
	Loader * mLoader;

	/** Indicator of whether there is an administrator */
	bool mHasAdmin;

	/** The ID of the administrator */
	ZCom_ConnID mAdmin;

	/** The maximum number of players allowed */
	int mMaximumPlayers;

	/** The current number of players */
	int mCurrentPlayers;

	/** The filename of the track */
	Ogre::String mTrackFilename;

	/** Map with all player settings */
	playermap mPlayers;

	/** The own player settings object, or 0 for the server */
	PlayerSettings* mOwnPlayer;

	/** The race state when a race is busy */
	RaceState* mRaceState;

	/** Value to check if we should fill the server with bots */
	bool mFillWithBots;

public:

	/**
	 * Constructor
	 *
	 * @param loader the loader for the loby, will be deleted by the lobby on destruction
	 */
	Lobby(Loader* loader);

	/**
	 * Destructor
	 */
	~Lobby();

	/**
	 * Process the lobby. This will process all events for the lobby and for all the
	 * players in the lobby.
	 */
	void process();

	/**
	 * Start the track. Called by owner
	 */
	void start();

	/**
	 * Check if the client is the administrator of the lobby.
	 */
	bool isAdmin() const;

	/**
	 * Add a player setting to the lobby
	 *
	 * @param settings the player settings
	 * @param ownPlayer indicates whether it is the setting of the own player
	 */
	void addPlayer(PlayerSettings * settings, bool ownPlayer = false);

	/**
	 * Get a player setting from the lobby
	 *
	 * @param id the id of the player
	 * @return the settings
	 */
	PlayerSettings* getPlayer(ZCom_ConnID id);

	/**
	 * Add a lobby listener
	 *
	 * @param listener the listener which will get called back upon events
	 */
	void addListener(LobbyListener* listener);

	/**
	 * Remove a lobby listener
	 *
	 * @param listener the listener
	 */
	void removeListener(LobbyListener* listener);

	/**
	 * Get the class name for this class. This is used for registering
	 * the class with the network
	 *
	 * @return the class name
	 */
	static std::string getClassName();

	/**
	 * Get a map with all players mapped on their connection id
	 *
	 * @return player settings mapped on their connection id
	 */
	inline const playermap& getPlayers() const {
		return mPlayers;
	}

	/**
	 * Get the own player settings
	 *
	 * @return the own player settings
	 */
	inline PlayerSettings* getOwnPlayer() {
		return mOwnPlayer;
	}

	/**
	 * Get the track filename
	 *
	 * @return the filename of the track
	 */
	inline Ogre::String getTrackFilename() {
		return mTrackFilename;
	}

	/**
	 * Set the race state
	 *
	 * @param state the new race state
	 */
	void setRaceState(RaceState* state);

	/**
	 * Get the race state
	 *
	 * @return the race state
	 */
	RaceState* getRaceState();

	// Connect callback on authority

	/**
	 * Called when player is about to connect
	 *
	 * @param id the ID of the new connected player
	 * @return true when there is room for a player, false if Lobby is full
	 */
	bool onConnectAttempt(ZCom_ConnID id);

	/**
	 * Called when player connects
	 *
	 * @param id the ID of the new connected player
	 */
	virtual void onConnect(ZCom_ConnID id);

	/**
	 * Called when player disconnects
	 * 
	 * @param id the ID of the disconnected player
	 * @param reason the reason
	 */
	virtual void onDisconnect(ZCom_ConnID id, const std::string& reason);

	/**
	 * Called when admin sends start
	 */
	virtual void onStartServer();

	/**
	 * Called to notify the listeners of the start
	 */
	virtual void onStartClient();

	/**
	 * Called when admin changes the map

	 * @param filename the new filename of the map
	 */
	virtual void onTrackChange(const Ogre::String& filename);

	/**
	 * Mark the lobby to fill the server with bots or not.
	 * @param val True when you want to fill with bots, false otherwise
	 */
	void setFillWithBots(bool val) { mFillWithBots = val; }

	/**
	 * Check if we want to fill with bots or not
	 *
	 * @return True when we want to fill, false otherwise
	 */
	bool isFillWithBots() { return mFillWithBots; }

protected:

	/**
	 * Remove player connection id
	 *
	 * @param id the ID of the player
	 */
	void removePlayer(ZCom_ConnID id);

	/**
	 * Remove player
	 *
	 * @param i the iterator pointing to the player
	 */
	playermap::iterator removePlayer(playermap::iterator i);

	//OVERWRITEN FROM NetworkEntity

	/*
	 * @see NetworkEntity::parseEvents(eZCom_Event type, eZCom_NodeRole remote_role, ZCom_ConnID conn_id, ZCom_BitStream* stream, float timeSince)
	 */
	virtual void parseEvents(eZCom_Event type, eZCom_NodeRole remote_role, ZCom_ConnID conn_id,
			ZCom_BitStream* stream, float timeSince);

	/*
	 * @see NetworkEntity::setupReplication()
	 */
	virtual void setupReplication();

	/*
	 * @see NetworkEntity::setAnnouncementData(ZCom_BitStream* stream)
	 */
	virtual void setAnnouncementData(ZCom_BitStream* stream);

	/**
	 * Process a game event at the server
	 *
	 * @param event an event
	 */
	void processEventsServer(GameEvent* event);

	/**
	 * Process a game event at the owner
	 *
	 * @param event an event
	 */
	void processEventsOwner(GameEvent* event);

	/**
	 * Process a game event at other clients
	 *
	 * @param event an event
	 */
	void processEventsOther(GameEvent* event);
	
	///////////////////////////
	// INTERCEPTOR FUNCTIONS //
	///////////////////////////
public:
		/**
	 * @inheritDoc
	 */
	bool inPreUpdate(ZCom_Node *_node, ZCom_ConnID _from, eZCom_NodeRole _remote_role) { return true; }

	/**
	 * @inheritDoc
	 */
	bool inPreUpdateItem(ZCom_Node *_node, ZCom_ConnID _from, eZCom_NodeRole _remote_role,
		ZCom_Replicator *_replicator, zU32 _estimated_time_sent) { return true; }

	/**
	 * @inheritDoc
	 */
	void inPostUpdate(ZCom_Node *_node, ZCom_ConnID _from, eZCom_NodeRole _remote_role,
			zU32 _rep_bits, zU32 _event_bits, zU32 _meta_bits);

	/**
	 * @inheritDoc
	 */
	void outPreReplicateNode(ZCom_Node *_node, ZCom_ConnID _to, eZCom_NodeRole _remote_role) {
	}

	/**
	 * @inheritDoc
	 */
	void outPreDereplicateNode(ZCom_Node *_node, ZCom_ConnID _to, eZCom_NodeRole _remote_role) {
	}

	/**
	 * @inheritDoc
	 */
	bool outPreUpdate(ZCom_Node *_node, ZCom_ConnID _to, eZCom_NodeRole _remote_role) {
		return true;
	}

	/*! @copydoc ZCom_NodeReplicationInterceptor::outPreUpdateItem(ZCom_Node*,ZCom_ConnID,eZCom_NodeRole,ZCom_Replicator*) */
	bool outPreUpdateItem(ZCom_Node *_node, ZCom_ConnID _to, eZCom_NodeRole _remote_role,
			ZCom_Replicator *_replicator) {
		return true;
	}

	/*! @copydoc ZCom_NodeReplicationInterceptor::outPostUpdate(ZCom_Node*,ZCom_ConnID,eZCom_NodeRole,zU32,zU32,zU32) */
	void outPostUpdate(ZCom_Node *_node, ZCom_ConnID _to, eZCom_NodeRole _remote_role,
		zU32 _rep_bits, zU32 _event_bits, zU32 _meta_bits) {}

};

}

#endif
