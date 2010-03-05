#ifndef TRACK_H
#define TRACK_H

#include <tinyxml/tinyxml.h>
#include <OgreString.h>
#include <OgrePlatform.h>
#include "UserData.h"

namespace HovUni {

class Track : public UserData
{
private:

	/**
	 * Name of the track
	 */
	Ogre::String mName;

	/**
	 * Physics filename
	 */
	Ogre::String mPhysicsFileName;

	/**
	 * Minimum players
	 */
	Ogre::int32 mMinimumPlayers;

	/**
	 * Minimum players
	 */
	Ogre::int32 mMaximumPlayers;

public:
	
	/**
	 * Constructor
	 * @param data
	 * @throws ParseException
	 */
	Track( TiXmlElement * data ) throw (ParseException);

	/**
	 * Destructor
	 */
	virtual ~Track(void);

	/**
	 * Get physics filename
	 * @return the physics filename
	 */
	inline Ogre::String getPhysicsFileName() const {
		return mPhysicsFileName;
	}

	/**
	 * Set physics filename
	 * @param physics filename
	 */
	inline void setPhysicsFileName( const Ogre::String& physicsFileName ){
		mPhysicsFileName = physicsFileName;
	}

	/**
	 * Get minimum players
	 * @return the minimum players
	 */
	inline Ogre::int32 getMinimumPlayers() const {
		return mMinimumPlayers;
	}

	/**
	 * Set minimum players
	 * @param minplayers
	 */
	inline void setMinimumPlayers( Ogre::int32 minplayers ){
		mMinimumPlayers = minplayers;
	}


	/**
	 * Get maximum players
	 * @return the maximum players
	 */
	inline Ogre::int32 getMaximumPlayers() const {
		return mMaximumPlayers;
	}

	/**
	 * Set maximum players
	 * @param maximum
	 */
	inline void setMaximumPlayers( Ogre::int32 maximum ){
		mMaximumPlayers = maximum;
	}

	/**
	 * Get name
	 * @return the name
	 */
	inline Ogre::String getName() const {
		return mName;
	}

	/**
	 * Set name
	 * @param name
	 */
	inline void setName( const Ogre::String& name ){
		mName = name;
	}

};

}

#endif