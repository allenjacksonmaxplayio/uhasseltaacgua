#ifndef USERDATA_H
#define USERDATA_H

#include <OgreMovableObject.h>

namespace HovUni {

class UserData
{
protected:

	/**
	 * Movable to which user data is attached
	 */
	Ogre::MovableObject * mMovableObject;

public:

	/**
	 * Constructor
	 * @param parameters, export data
	 */
	UserData();

	/**
	 * Destructor
	 */
	virtual ~UserData(void);

	/**
	 * Get movable data
	 * @return the movable object
	 */
	inline Ogre::MovableObject * getMovableObject() {
		return mMovableObject;
	}

	/**
	 * Get movable data
	 * @return the movable object
	 */
	inline const Ogre::MovableObject * getMovableObject() const {
		return mMovableObject;
	}

	/**
	 * Set movable data
	 * @param the movable object
	 */
	void setMovableObject( Ogre::MovableObject * movobj );
};

}

#endif