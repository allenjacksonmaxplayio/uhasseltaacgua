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

	/** The hovercraft type */
	Ogre::String mHovercraft;

	/* The character type */
	Ogre::String mCharacter;

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
	 * @param announcedata the announce data
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
	inline void setPlayerName(const Ogre::String& name) {
		mPlayerName.assign(name);
	}

	/**
	 * Get player name
	 *
	 * @return name the name of the player
	 */
	inline const Ogre::String& getPlayerName() const {
		return mPlayerName;
	}

	/**
	 * Set character
	 *
	 * @param character the character
	 */
	inline void setCharacter(const Ogre::String& character) {
		mCharacter.assign(character);
	}

	/**
	 * Get character
	 *
	 * @return character the character
	 */
	inline const Ogre::String& getCharacter() const {
		return mCharacter;
	}

	/**
	 * Set hovercraft
	 *
	 * @param hovercraft the hovercraft
	 */
	inline void setHovercraft(const Ogre::String& hov) {
		mHovercraft.assign(hov);
	}

	/**
	 * Get hovercraft
	 *
	 * @return hovercraft the hovercraft
	 */
	inline const Ogre::String& getHovercraft() const {
		return mHovercraft;
	}

	/**
	 * Get the ID of the user
	 *
	 * @return the ID of the user
	 */
	inline const unsigned int getID() const {
		return mUserID;
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
