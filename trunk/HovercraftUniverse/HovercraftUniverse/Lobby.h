#ifndef LOBBY_H
#define LOBBY_H

#include "NetworkEntity.h"
#include "PlayerSettings.h"
#include "GameEvent.h"
#include <map>
#include <string>
#include <list>

namespace HovUni {

class LobbyListener;
class Loader;

/**
 * The Lobby which holds the connected players, assigns an 
 * administrator and holds the map info. It also contains a custom loader that is used to load the initial world.
 *
 * @author Pieter-Jan Pintens & Olivier Berghmans
 */
class Lobby : public NetworkEntity{

public:
	
	typedef std::map<ZCom_ConnID,PlayerSettings*> playermap;

private:

	//TODO MUTEX PROTECT PLAYERS
	std::list<LobbyListener*> mListeners;

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

	/** Map with all players */
	playermap mPlayers;

	// TODO Remove
	bool mStarted;

protected:

	/**
	 * Remove player connection id
	 */
	void removePlayer( ZCom_ConnID id );	

public:

	/**
	 * Constructor
	 * @param the loader for the loby, will be deleted by the lobby on destruction
	 */
	Lobby( Loader * loader );

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
	 * Add a player to the lobby
	 */
	void addPlayer(PlayerSettings * settings);

	/**
	 * Remove a player from the lobby
	 */
	void removePlayer( PlayerSettings * settings );

	/**
	 * Add a loby listener
	 * @param listener
	 */
	void addListener( LobbyListener* listener );

	/**
	 * Remove a lobby listener
	 * @param listener
	 */
	void removeListener( LobbyListener* listener );

	/**
	 * Start the track. Called by owner
	 */
	void start();

	/**
	 * Check if the client is the administrator
	 */
	bool isAdmin() const;

	/**
	 * Get a map with all players mapped on their connection id
	 * @return player mapped on their connection id
	 */
	const playermap& getPlayers() const {
		return mPlayers;
	}

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
	 */
	virtual void onDisconnect(ZCom_ConnID id);

	// Event callbacks on authority, issued by owner

	/**
	 * Called when admin sends start
	 */
	virtual void onStart();

	/**
	 * Called when admin changes the map

	 * @param filename the new filename of the map
	 */
	virtual void onTrackChange(const Ogre::String& filename);

	/**
	 * Called when player changes character
	 * 
	 * @param id the ID of the player
	 * @param character the character of the player
	 */
	virtual void onPlayerCharacterChange(ZCom_ConnID id, const Ogre::String& character);

	/**
	 * Called when player changes hovercraft
	 *
	 * @param id the ID of the player
	 * @param hovercraft the hovercraft of the player
	 */
	virtual void onPlayerHovercraftChange(ZCom_ConnID id, const Ogre::String& hovercraft);

	//OVERWRITEN FROM NetworkEntity

	virtual void parseEvents(eZCom_Event type, eZCom_NodeRole remote_role, ZCom_ConnID conn_id, ZCom_BitStream* stream, float timeSince);

	virtual void setupReplication();

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

	/**
	 * Get the class name for this class. This is used for registering
	 * the class with the network
	 *
	 * @return the class name
	 */
	static std::string getClassName();

	// Getters
	Ogre::String getTrackFilename() { return mTrackFilename; }

};

}

#endif
