#ifndef ASTEROID_H
#define ASTEROID_H

#include <tinyxml/tinyxml.h>
#include <OgreString.h>
#include <OgrePlatform.h>

namespace HovUni {

/**
 * @author PJ
 */
class Asteroid
{
public:

	enum AsteroidType {
		UNKNOWN = -1,
		ICE,
		FIRE,
		JUNGLE,
		STONE,
		DESERT
	};

private:

	/**
	 * Name
	 */
	Ogre::String mName;

	/**
	 * Gravity
	 */
	Ogre::Real mGravity;

	/**
	 * Type
	 */
	AsteroidType mAsteroidType;


public:
	
	/**
	 * Constructor
	 * @param data, xml element that descripes the start position
	 */
	Asteroid( TiXmlElement * data );

	/**
	 * Destructor
	 */
	~Asteroid(void);

	/**
	 * Get the name
	 * @return name
	 */
	inline Ogre::String getName() const {
		return mName;
	}

	/**
	 * Set the name
	 * @param name
	 */
	inline void setName( const Ogre::String& name ) {
		mName = name;
	}

	/**
	 * Get the gravity
	 * @return gravity
	 */
	inline Ogre::Real getGravity() const {
		return mGravity;
	}

	/**
	 * Set the gravity
	 * @param gravity
	 */
	inline void setGravity( const Ogre::Real& gravity ) {
		mGravity = gravity;
	}

	/**
	 * Get the Asteroid type
	 * @return Asteroid type
	 */
	inline AsteroidType getAsteroidType() const {
		return mAsteroidType;
	}

	/**
	 * Set the Asteroid type
	 * @param Asteroid type
	 */
	inline void setAsteroidType( AsteroidType type ) {
		mAsteroidType = type;
	}
};

}

#endif