#ifndef _RACESTATE_H
#define _RACESTATE_H

#include "NetworkEntity.h"

namespace HovUni {

class Lobby;
class Loader;

/**
 * RaceState will be the main controlling component during the game.
 * It will manage the game state, handle game events and take care of all the
 * game logic.
 *
 * @author Olivier Berghmans & Nick De Frangh
 */
class RaceState: public NetworkEntity {
public:
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
	RaceState(Lobby * lobby, ZCom_BitStream* announcementdata, ZCom_ClassID id,
			ZCom_Control* control);

	/**
	 * Destructor
	 */
	virtual ~RaceState();

	/**
	 * Get the class name for this class. This is used for registering
	 * the class with the network
	 *
	 * @return the class name
	 */
	static std::string getClassName();

protected:

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
