#ifndef ENITITYDESCRIPTION_H
#define ENITITYDESCRIPTION_H

#include <OgreString.h>
#include <OgreVector3.h>
#include <OgrePlatform.h>

namespace HovUni {

/**
 * A struct that describes an Entity
 * Contains its name, position and orientation.
 */
class EntityDescription
{
private:

	Ogre::String mName;

	Ogre::Vector3 mPosition;

	Ogre::Quaternion mOrientation;

public:

	/**
	 * Constructor
	 * @param name
	 * @param position
	 * @param orientation
	 */
	EntityDescription(const Ogre::String& name, const Ogre::Vector3& position, const Ogre::Quaternion& orientation);

	/**
	 * Get name
	 * @return name
	 */
	inline Ogre::String& getName(){
		return mName;
	}

	/**
	 * Get name
	 * @return name
	 */
	inline const Ogre::String& getName() const {
		return mName;
	}
	
	/**
	 * Get position
	 * @return position
	 */
	inline Ogre::Vector3& getPosition(){
		return mPosition;
	}

	/**
	 * Get position
	 * @return position
	 */
	inline const Ogre::Vector3& getPosition() const {
		return mPosition;
	}

	/**
	 * Get orientation
	 * @return orientation
	 */
	inline Ogre::Quaternion& getOrientation(){
		return mOrientation;
	}

	/**
	 * Get orientation
	 * @return orientation
	 */
	inline const Ogre::Quaternion& getOrientation() const {
		return mOrientation;
	}
};

}

#endif