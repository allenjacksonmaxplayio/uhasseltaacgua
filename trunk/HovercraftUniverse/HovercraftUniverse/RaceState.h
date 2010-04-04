#ifndef RACESTATE_H
#define RACESTATE_H

#include "NetworkEntity.h"
#include <list>

namespace HovUni {

class Lobby;
class Loader;
class ClientPreparationLoader;
class RacePlayer;
class RaceStateListener;

/**
 * RaceState will be the main controlling component during the game.
 * It will manage the game state, handle game events and take care of all the
 * game logic.
 *
 * @author Olivier Berghmans & Nick De Frangh
 */
class RaceState: public NetworkEntity {
public:
	typedef std::map<ZCom_ConnID, RacePlayer*> playermap;

	/** All the possible stated during the race */
	static const enum States {
		INITIALIZING = 0, /** Pre-race state, show intro */
		COUNTDOWN, /** The race will start, show countdown */
		RACING, /** The race has started */
		FINISHING, /** Someone has finished, wait for everyone to finish */
		ROUNDUP
	/** Everyone has finished, show some stats and return to lobby */
	};

private:
	/** the current state of the race */
	States mCurrentState;

	/** The reference to the lobby */
	Lobby* const mLobby;

	/** The loader */
	Loader* const mLoader;

	/** The track file name for this race */
	const Ogre::String mTrackFilename;

	/** The list of race players */
	playermap mPlayers;

	/** The own player */
	RacePlayer* mOwnPlayer;

	/** The listeners */
	std::list<RaceStateListener*> mListeners;

public:
	/**
	 * Constructor
	 *
	 * @param lobby a reference to the lobby
	 * @param loader the loader for the server
	 * @param track the track filename
	 */
	RaceState(Lobby* lobby, Loader* loader, Ogre::String track);

	/**
	 * Constructor
	 *
	 * @param lobby a reference to the lobby
	 * @param announcementdata the announce data
	 * @param ID the class ID
	 * @param control the network control
	 */
	RaceState(Lobby* lobby, ClientPreparationLoader* loader, ZCom_BitStream* announcementdata,
			ZCom_ClassID id, ZCom_Control* control);

	/**
	 * Destructor
	 */
	virtual ~RaceState();

	/**
	 * Process the race state
	 */
	void process();

	/**
	 * Add a player to the race state
	 *
	 * @param player the player settings
	 * @param ownPlayer indicates whether it is the setting of the own player
	 */
	void addPlayer(RacePlayer* player, bool ownPlayer = false);

	/**
	 * Remove a player from the race state
	 *
	 * @param player the player settings
	 */
	void removePlayer(RacePlayer* player);

	/**
	 * Get a player from the lobby
	 *
	 * @param id the id of the player
	 * @return the settings
	 */
	RacePlayer* getPlayer(ZCom_ConnID id);

	/**
	 * Get the own player
	 *
	 * @return the own player settings
	 */
	inline RacePlayer* getOwnPlayer() {
		return mOwnPlayer;
	}

	/**
	 * Add a race state listener
	 *
	 * @param listener the listener which will get called back upon events
	 */
	void addListener(RaceStateListener* listener);

	/**
	 * Remove a race state listener
	 *
	 * @param listener the listener
	 */
	void removeListener(RaceStateListener* listener);

	/**
	 * Get the class name for this class. This is used for registering
	 * the class with the network
	 *
	 * @return the class name
	 */
	static std::string getClassName();

	/**
	 * Get the list of listeners
	 *
	 * @return the list
	 */
	std::list<RaceStateListener*>& getListeners();

protected:

	/**
	 * Remove player connection id
	 */
	void removePlayer(ZCom_ConnID id);

	/**
	 * Set the new state for the race state
	 *
	 * @param state the new state
	 */
	void setNewState(States state);

	/**
	 * A callback that should be implemented in order to parse and process
	 * incoming events.
	 */
	virtual void parseEvents(eZCom_Event type, eZCom_NodeRole remote_role, ZCom_ConnID conn_id,
			ZCom_BitStream* stream, float timeSince);

	/**
	 * A callback that should be implemented so the replicators for this
	 * entity can be set up. In case the number of replicators given to the
	 * constructor is zero, this callback can be implemented as empty.
	 */
	virtual void setupReplication();

	/**
	 * A callback that should be implemented so the announcement data for this
	 * entity can be set.
	 *
	 * @param stream the bitstream where the data can be set
	 */
	virtual void setAnnouncementData(ZCom_BitStream* stream);

};
}

#endif //_RACESTATE_H
