#ifndef SPEED_BOOST_H
#define SPEED_BOOST_H

#include "Exception.h"
#include "Entity.h"
#include <tinyxml/tinyxml.h>
#include <OgreString.h>
#include <OgrePlatform.h>

namespace HovUni {

/**
 * Boost
 * A Boost should speed up an entity that passes over it in the direction it is currently heading. 
 * @author PJ
 */
class Boost : public Entity{
private:

	/**
	 * The BoostData
	 */
	Ogre::Real mBoost;

public:

	/**
	 * The category used for checkpoints
	 */
	static const Ogre::String CATEGORY;

	/**
	 * Constructor
	 */
	Boost(const Ogre::String& name, const Ogre::Vector3& position, const Ogre::Quaternion& orientation, float processInterval);

	/**
	 * Load
	 * @param data
	 * @throws ParseException
	 */
	void load(TiXmlElement * data) throw(ParseException);

	/**
	 * Destructor
	 */
	~Boost(void);

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
	void setBoost(Ogre::Real boost) {
		mBoost = boost;
	}

	/**
	 * Callback to process this entity. This allows to do entity specific processing
	 *(e.g. intermediate actions).
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