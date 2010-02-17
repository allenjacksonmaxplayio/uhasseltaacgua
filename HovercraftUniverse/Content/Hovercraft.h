#ifndef HOVERCRAFT_H
#define HOVERCRAFT_H

#include "UserData.h"
#include <OgreString.h>
#include <tinyxml/tinyxml.h>

namespace HovUni {

/**
 * @author PJ
 */ 
class Hovercraft : public UserData
{
private:

	/**
	 * The name
	 */
	Ogre::String mName;

	/**
	 * The name
	 */
	Ogre::String mDescription;

	/**
	 * The speed
	 */
	Ogre::Real mSpeed;

	/**
	 * The mass
	 */
	Ogre::Real mMass;

	/**
	 * The base acceleration without powerups
	 */
	Ogre::Real mAcceleration;

public:

	/**
	 * Constructor
	 * @param data, xml element that descripes the hovercraft
	 */
	Hovercraft( TiXmlElement * data );

	/**
	 * Destructor
	 */
	~Hovercraft(void);

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
	 * Get the description
	 * @return description
	 */
	inline Ogre::String getDescription() const {
		return mDescription;
	}

	/**
	 * Set the description
	 * @param description
	 */
	inline void setDescription( const Ogre::String& description ) {
		mDescription = description;
	}

	/**
	 * Get the speed
	 * @return speed
	 */
	inline Ogre::Real getSpeed() const {
		return mSpeed;
	}

	/**
	 * Set the speed
	 * @param speed
	 */
	inline void setSpeed( Ogre::Real speed ) {
		mSpeed = speed;
	}

	/**
	 * Get the mass
	 * @return mass
	 */
	inline Ogre::Real getMass() const {
		return mMass;
	}

	/**
	 * Set the mass
	 * @param mass
	 */
	inline void setMass( Ogre::Real mass ) {
		mMass = mass;
	}

	/**
	 * Get the acceleration
	 * @return acceleration
	 */
	inline Ogre::Real getAcceleration() const {
		return mAcceleration;
	}

	/**
	 * Set the acceleration
	 * @param acceleration
	 */
	inline void setAcceleration( Ogre::Real acceleration ) {
		mAcceleration = acceleration;
	}
};

}

#endif
