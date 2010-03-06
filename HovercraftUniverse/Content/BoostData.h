#ifndef BOOSTDATA_H
#define BOOSTDATA_H

#include "UserData.h"
#include <tinyxml/tinyxml.h>
#include <OgreString.h>
#include <OgrePlatform.h>

namespace HovUni {

/**
 * BoostData
 * A BoostData should speed up an entity that passes over it in the direction it is currently heading. 
 * @author PJ
 */
class BoostData : public UserData
{
private:

	/**
	 * The BoostData
	 */
	Ogre::Real mBoost;

public:

	/**
	 * Constructor
	 * @param data
	 * @throws ParseException
	 */
	BoostData( TiXmlElement * data ) throw (ParseException);

	/**
	 * Destructor
	 */
	~BoostData(void);

	/**
	 * Get the BoostData
	 * @return BoostData
	 */
	Ogre::Real getBoost() const {
		return mBoost;
	}

	/**
	 * Set the BoostData
	 * @param BoostData
	 */
	void setBoost( Ogre::Real boost) {
		mBoost = boost;
	}
};

}

#endif