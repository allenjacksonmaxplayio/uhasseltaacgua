#ifndef ASTROID_H
#define ASTROID_H

#include <tinyxml/tinyxml.h>
#include <OgreString.h>
#include <OgrePlatform.h>

namespace HovUni {

/**
 * @author PJ
 */
class Astroid
{
public:

	enum AstroidType {
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
	AstroidType mAstroidType;


public:
	
	/**
	 * Constructor
	 * @param data, xml element that descripes the start position
	 */
	Astroid( TiXmlElement * data );

	/**
	 * Destructor
	 */
	~Astroid(void);

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
	 * Get the astroid type
	 * @return astroid type
	 */
	inline AstroidType getAstroidType() const {
		return mAstroidType;
	}

	/**
	 * Set the astroid type
	 * @param astroid type
	 */
	inline void setAstroidType( AstroidType type ) {
		mAstroidType = type;
	}
};

}

#endif