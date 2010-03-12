#ifndef PLAYER_H
#define PLAYER_H

#include <zoidcom/zoidcom.h>
#include <OgreString.h>

namespace HovUni {

class Player {
private:

	//connection id
	const ZCom_ConnID mConnectionID;

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
	Player(ZCom_ConnID mConnectionID);

	~Player(void);

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


};

}

#endif