#ifndef STARTPOSITIONDATA_H
#define STARTPOSITIONDATA_H

#include <tinyxml/tinyxml.h>
#include <OgrePlatform.h>
#include "UserData.h"

namespace HovUni {

/**
 * @author PJ
 */ 
class StartPositionData : public UserData
{
private:

	/**
	 * The number of the player
	 */
	Ogre::int32 mPlayerNumber;

public:

	/**
	 * Constructor
	 * @param data, xml element that descripes the start position
	 * @throws ParseException
	 */
	StartPositionData( TiXmlElement * data ) throw (ParseException);

	/**
	 * Destructor
	 */
	~StartPositionData(void);

	/**
	 * Get the player number
	 * @return player number
	 */
	inline Ogre::int32 getPlayerNumber() const {
		return mPlayerNumber;
	}

	/**
	 * Set the player number
	 * @param player number
	 */
	inline void setPlayerNumber( Ogre::int32 playernumber ) {
		mPlayerNumber = playernumber;
	}
};

}

#endif
