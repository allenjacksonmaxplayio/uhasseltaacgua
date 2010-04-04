#ifndef PLAYERSETTINGS_H
#define PLAYERSETTINGS_H

#include "NetworkEntity.h"
#include <zoidcom/zoidcom.h>
#include <OgreString.h>
#include "GameEvent.h"

namespace HovUni {

class Lobby;

/**
 * The settings of a player. This is distributed over all players so that
 * they now what the settings are of each player
 *
 * @author Olivier Berghmans & Pieter-Jan Pintens & Nick De Frangh
 */
class PlayerSettings: public NetworkEntity {
private:
	/** The lobby */
	Lobby* mLobby;

	/** The ID of the user */
	const unsigned int mUserID;

	/** The name of the user */
	Ogre::String mPlayerName;

	/** The hovercraft type (only 4 bits are used = 16 possibilities) */
	unsigned short mHovercraft;

	/* The character type (only 4 bits are used = 16 possibilities) */
	unsigned short mCharacter;

public:

	/**
	 * Constructor
	 *
	 * @param lobby the lobby
	 * @param userID the ID of the user
	 */
	PlayerSettings(Lobby * lobby, unsigned int userID);

	/**
	 * Constructor
	 *
	 * @param lobby the lobby
	 * @param announcementdata the announce data
	 * @param ID the class ID
	 * @param control the network control
	 */
	PlayerSettings(Lobby * lobby, ZCom_BitStream* announcementdata, ZCom_ClassID id,
			ZCom_Control* control);

	/**
	 * Destructor
	 */
	~PlayerSettings();

	/**
	 * Get the class name for this class. This is used for registering
	 * the class with the network
	 *
	 * @return the class name
	 */
	static std::string getClassName();

	/**
	 * Set player name
	 *
	 * @param name the name of the player
	 */
	void setPlayerName(const Ogre::String& name);

	/**
	 * Get player name
	 *
	 * @return name the name of the player
	 */
	const Ogre::String& getPlayerName() const;

	/**
	 * Set character
	 *
	 * @param character the character
	 */
	void setCharacter(unsigned short character);

	/**
	 * Get character
	 *
	 * @return character the character
	 */
	const Ogre::String getCharacter() const;

	/**
	 * Set hovercraft
	 *
	 * @param hovercraft the hovercraft
	 */
	void setHovercraft(unsigned short hov);

	/**
	 * Get hovercraft
	 *
	 * @return hovercraft the hovercraft
	 */
	const Ogre::String getHovercraft() const;

	/**
	 * Get the ID of the user
	 *
	 * @return the ID of the user
	 */
	const unsigned int getID() const;

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

#endif
