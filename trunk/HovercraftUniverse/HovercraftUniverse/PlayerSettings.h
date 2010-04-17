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
	/*
	 * Not replicated fields
	 */
private:
	/** The lobby */
	Lobby* mLobby;

	/*
	 * Replicated fields
	 */
private:
	// Adding a replicated field: set up replication (in setupReplication) + init event (in parseEvents)
	// Const fields should be in announce data and not as replicator

	/** The ID of the user */
	const unsigned int mUserID;

	/** The name of the user */
	Ogre::String mPlayerName;

	/** The hovercraft type (only 4 bits are used = 16 possibilities) */
	unsigned int mHovercraft;

	/* The character type (only 4 bits are used = 16 possibilities) */
	unsigned int mCharacter;

public:

	/**
	 * Constructor for settings for a certain player
	 *
	 * @param lobby the lobby
	 * @param userID the ID of the player
	 */
	PlayerSettings(Lobby * lobby, unsigned int userID);

	/**
	 * Constructor for settings of an AI or something
	 *
	 * @param lobby the lobby
	 * @param name the name this AI will use
	 */
	PlayerSettings(Lobby* lobby, const Ogre::String& name);

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
	void setCharacter(unsigned int character);

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
	void setHovercraft(unsigned int hov);

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

	/**
	 * Check whether this is a bot
	 *
	 * @return true if it is a bot, false otherwise
	 */
	inline bool isBot() const {
		return mUserID == ZCom_Invalid_ID;
	}

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
