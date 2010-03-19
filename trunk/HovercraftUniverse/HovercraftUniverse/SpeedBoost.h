#ifndef SPEED_BOOST_H
#define SPEED_BOOST_H

#include "Entity.h"

#include "Exception.h"
#include <tinyxml/tinyxml.h>

namespace HovUni {

class Hovercraft;

/**
 * Boost
 * A Boost should speed up an entity that passes over it in the direction it is currently heading. 
 * @author PJ
 */
class SpeedBoost : public Entity{
private:

	/**
	 * The BoostData
	 */
	Ogre::Real mBoost;

public:

	/**
	 * The category used for boosts
	 */
	static const Ogre::String CATEGORY;

	/**
	 * Constructor.
	 *
	 * @param name The name of the boost
	 * @param position
	 * @param quaternion
	 * @param processInterval The process interval
	 */
	SpeedBoost(const Ogre::String& name, const Ogre::Vector3& position, const Ogre::Quaternion& orientation, const Ogre::String& ogreentity, float processInterval);

	/**
	 * Load
	 * @param data
	 * @throws ParseException
	 */
	void load(TiXmlElement * data) throw(ParseException);

	/**
	 * Destructor
	 */
	~SpeedBoost(void);

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
	 * Called when given hovercraft enters the portal bounding box
	 * @param hovercraft
	 */
	void onEnter ( Hovercraft * hovercraft );

	/**
	 * Called when given hovercraft leaves the portal bounding box
	 * @param hovercraft
	 */
	void onLeave( Hovercraft * hovercraft );


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

	/**
	 * @see NetworkEntity::setReplication()
	 */
	void setupReplication();

	/**
	 * Get the class name for this class. This is used for registering
	 * the class with the network
	 *
	 * @return the class name
	 */
	static std::string getClassName();
};

}

#endif