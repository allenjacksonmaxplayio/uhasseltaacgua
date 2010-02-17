#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include "UserData.h"
#include <OgreString.h>
#include <OgrePlatform.h>
#include <tinyxml/tinyxml.h>

namespace HovUni {

/**
 * @author PJ
 */ 
class CheckPoint : public UserData 
{
private:

	/**
	 * The name
	 */
	Ogre::String mName;

	/**
	 * The number
	 */
	Ogre::int32 mNumber;

public:

	/**
	 * Constructor
	 * @param data, xml element that descripes the checkpoint
	 * @throws ParseException
	 */
	CheckPoint( TiXmlElement * data ) throw (ParseException);

	/**
	 * Destructor
	 */
	~CheckPoint(void);

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
	 * Get the number
	 * @return number
	 */
	inline Ogre::int32 getNumber() const {
		return mNumber;
	}

	/**
	 * Set the number
	 * @param number
	 */
	inline void setNumber( Ogre::int32 number ) {
		mNumber = number;
	}


};

}

#endif
