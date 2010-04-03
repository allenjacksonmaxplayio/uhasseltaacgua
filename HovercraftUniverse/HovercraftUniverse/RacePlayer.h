#ifndef RACEPLAYER_H
#define RACEPLAYER_H

#include "NetworkEntity.h"

namespace HovUni {

class Lobby;
class RaceState;
class PlayerSettings;

/**
 * Class that represents a player in the race. It will hold his current
 * position, etc.
 *
 * @author Olivier Berghmans
 */
class RacePlayer: public NetworkEntity {
private:
	/** The race state */
	RaceState* const mRaceState;

	/** The general player settings and data */
	PlayerSettings* const mPlayerSettings;

	/** The current position of this player in the race */
	short mPlayerPosition;

public:
	/**
	 * Constructor
	 *
	 * @param state the race state
	 * @param playerSettings The general settings for this player
	 */
	RacePlayer(RaceState* state, PlayerSettings* playerSettings);

	/**
	 * Constructor
	 *
	 * @param lobby the lobby to retrieve the race state and player settings from
	 * @param announcementdata the announce data
	 * @param ID the class ID
	 * @param control the network control
	 */
	RacePlayer(Lobby* lobby, ZCom_BitStream* announcementdata, ZCom_ClassID id,
			ZCom_Control* control);

	/**
	 * Destructor
	 */
	~RacePlayer();

	/**
	 * Get the race state for this player
	 *
	 * @return the race state
	 */
	RaceState* getRaceState();

	/**
	 * Get the player settings for this player
	 *
	 * @return the settings
	 */
	PlayerSettings* getSettings();

	/**
	 * Set the current position of the player
	 *
	 * @param position the new position
	 */
	void setPosition(short position);

	/**
	 * Get the current position of the player
	 *
	 * @return the current position
	 */
	short getPosition() const;

	void onCheckpoint();

	void onFinish();

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

#endif //_RACEPLAYER_H
