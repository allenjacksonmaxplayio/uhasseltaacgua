#ifndef PORTALDATA_H
#define PORTALDATA_H

#include <tinyxml/tinyxml.h>
#include <OgreString.h>
#include <OgreVector3.h>
#include <OgrePlatform.h>
#include "UserData.h"

namespace HovUni {

/**
 * Portal 
 * A portal is a teleportation mechanism that ports objects from begin to end
 * @author PJ	
 */
class PortalData
{
private:

	/**
	 * Name of the portal
	 */
	Ogre::String mName;

	/**
	 * Start of the portal
	 */
	Ogre::Vector3 mStart;

	/**
	 * End of the portal
	 */
	Ogre::Vector3 mEnd;

public:

	/**
	 * Constructor
	 * @param data
	 * @throws ParseException
	 */
	PortalData(TiXmlElement * data) throw (ParseException);

	/**
	 * Destructor
	 */
	~PortalData(void);

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
	 * Get start point of the portal
	 * @return start
	 */
	inline const Ogre::Vector3& getStart() const {
		return mStart;
	}

	/**
	 * Get start point of the portal
	 * @return start
	 */
	inline Ogre::Vector3& getStart() {
		return mStart;
	}

	/**
	 * Set the start point of the portal
	 * @param start
	 */
	void setStart( const Ogre::Vector3& start ){
		mStart = start;
	}

	/**
	 * Get end point of the portal
	 * @return end
	 */
	inline const Ogre::Vector3& getEnd() const {
		return mEnd;
	}

	/**
	 * Get end point of the portal
	 * @return end
	 */
	inline Ogre::Vector3& getEnd() {
		return mEnd;
	}

	/**
	 * Set the end point of the portal
	 * @param end
	 */
	void setEnd( const Ogre::Vector3& end ){
		mEnd = end;
	}
};

}

#endif