#ifndef BOOST_H
#define BOOST_H

#include "UserData.h"
#include <tinyxml/tinyxml.h>
#include <OgreString.h>
#include <OgrePlatform.h>

namespace HovUni {

/**
 * Boost
 * A boost should speed up an entity that passes over it in the direction it is currently heading. 
 * @author PJ
 */
class Boost : public UserData
{
private:

	/**
	 * The boost
	 */
	Ogre::Real mBoost;

public:

	/**
	 * Constructor
	 * @param data
	 */
	Boost( TiXmlElement * data );

	/**
	 * Destructor
	 */
	~Boost(void);

	/**
	 * Get the boost
	 * @return boost
	 */
	Ogre::Real getBoost() const {
		return mBoost;
	}

	/**
	 * Set the boost
	 * @param boost
	 */
	void setBoost( Ogre::Real boost) {
		mBoost = boost;
	}
};

}

#endif