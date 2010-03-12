#ifndef STARTPOSITION_H
#define STARTPOSITION_H

#include "ParseException.h"
#include <tinyxml/tinyxml.h>
#include <OgrePlatform.h>
#include "Entity.h"

namespace HovUni {

/**
 * @author PJ
 */ 
class StartPosition : public Entity
{
private:

	/**
	 * The number of the player
	 */
	Ogre::int32 mPlayerNumber;

public:

	/**
	 * Constructor
	 */
	StartPosition(const Ogre::String& name, const Ogre::String& category, const Ogre::Vector3& position, const Ogre::Quaternion& orientation, float processInterval);


	/**
	 * Constructor
	 * @param data, xml element that descripes the start position
	 * @throws ParseException
	 */
	void load ( TiXmlElement * data ) throw (ParseException);

	/**
	 * Destructor
	 */
	~StartPosition(void);

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

	/**
	 * Callback to process this entity. This allows to do entity specific processing
	 * (e.g. intermediate actions).
	 *
	 * @param timeSince the time since the last processing of the entity
	 */
	virtual void process(float timeSince){
	}

	/**
	 * Callback to process a controller event at the server that got processed by the 
	 * controller.  Must be overriden since this class in itself has no clue which 
	 * controller properties there are.
	 *
	 * @param event a controller event
	 */
	virtual void processEventsServer(ControllerEvent* event){
	}

	/**
	 * Callback to process a controller event at the owner that got processed by the 
	 * controller.  Must be overriden since this class in itself has no clue which 
	 * controller properties there are.
	 *
	 * @param event a controller event
	 */
	virtual void processEventsOwner(ControllerEvent* event){
	}

	/**
	 * Callback to process a controller event at other clients that got processed by the controller.  Must
	 * be overriden since this class in itself has no clue which controller properties 
	 * there are.
	 *
	 * @param event a controller event
	 */
	virtual void processEventsOther(ControllerEvent* event){
	}
};

}

#endif
