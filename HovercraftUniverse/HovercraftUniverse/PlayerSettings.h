#ifndef PLAYERSETTINGS_H
#define PLAYERSETTINGS_H

#include "NetworkEntity.h"
#include <zoidcom/zoidcom.h>
#include <OgreString.h>
#include "GameEvent.h"

namespace HovUni {

class PlayerSettings : public NetworkEntity {
private:

	//connection id (const)
	ZCom_ConnID mConnectionID;

	//name
	Ogre::String mPlayerName;
	
	//hovercraft type
	Ogre::String mHovercraft;

	//character type
	Ogre::String mCharacter;

public:

	/**
	 * Constructor
	 * @param mconnectionid
	 */
	PlayerSettings(ZCom_ConnID mConnectionID);

	/**
	 * Constructor
	 * @param announcedata
	 */
	PlayerSettings(ZCom_BitStream* announcedata);

	~PlayerSettings(void);

	/**
	 * Get the class name for this class. This is used for registering
	 * the class with the network
	 *
	 * @return the class name
	 */
	static std::string getClassName();

	/**
	 * Set player name
	 * @param name
	 */
	inline void setPlayerName(const Ogre::String& name){
		mPlayerName = name;
	}

	/**
	 * Get player name
	 * @return name
	 */
	inline const Ogre::String& getPlayerName() const { 
		return mPlayerName;
	}

	/**
	 * Set character
	 * @param character
	 */
	inline void setCharacter(const Ogre::String& character){
		mCharacter = character;
	}

	/**
	 * Get character
	 * @return character
	 */
	inline const Ogre::String& getCharacter() const { 
		return mCharacter;
	}

	/**
	 * Set hovercraft
	 * @param hovercraft
	 */
	inline void setHovercraft(const Ogre::String& hov){
		mHovercraft = hov;
	}

	/**
	 * Get hovercraft
	 * @return hovercraft
	 */
	inline const Ogre::String& getHovercraft() const { 
		return mHovercraft;
	}

	/**
	 * Get connection id
	 * @return connection id
	 */
	inline const ZCom_ConnID getConnectionID() const { 
		return mConnectionID;
	}

	virtual void parseEvents(ZCom_BitStream* stream, float timeSince){
	}

protected:

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