#ifndef ENTITYEXTENSION_H
#define ENTITYEXTENSION_H

#include "OgreMaxScene.hpp"
using namespace OgreMax;

namespace HovUni {

/**
 * @author PJ
 */ 
class EntityExtension
{
protected:

	/**
	 * Reference to the ogre object
	 */
	Ogre::MovableObject * mMovable;

public:

	/**
	 * Constructor
	 * @param movable
	 * @param userdata
	 */
	EntityExtension(Ogre::MovableObject * movable, const Ogre::String& userdata );

	~EntityExtension(void);

	/**
	 * Get the ogre object
	 * @return movable
	 */
	inline Ogre::MovableObject * getMovableObjct() const {
		return mMovable;
	}

	/**
	 * Set the ogre object
	 * @param movable
	 */
	inline void setMovableObjct( Ogre::MovableObject * movable ) {
		mMovable = movable;
	}

};

}

#endif
