#ifndef ASTEROID_H
#define ASTEROID_H

#include "ParseException.h"
#include "Entity.h"
#include <tinyxml/tinyxml.h>
#include <OgreString.h>
#include <OgrePlatform.h>

namespace HovUni {

/**
 * @author PJ
 */
class Asteroid : public Entity
{
public:

	enum AsteroidType {
		UNKNOWN = -1,
		ICE,
		FIRE,
		JUNGLE,
		STONE,
		DESERT
	};

private:

	/**
	 * Name
	 */
	Ogre::String mName;

	/**
	 * Gravity
	 */
	Ogre::Real mGravity;

	/**
	 * Type
	 */
	AsteroidType mAsteroidType;


public:
	
	/**
	 * Constructor
	 */
	Asteroid(const Ogre::String& name, const Ogre::String& category, const Ogre::Vector3& position, const Ogre::Quaternion& orientation, float processInterval);

	/**
	 * Load
	 * @param data, xml element that descripes the asteroid
	 * @throws ParseException
	 */
	void load ( TiXmlElement * data ) throw (ParseException);

	/**
	 * Destructor
	 */
	~Asteroid(void);

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
	 * Get the gravity
	 * @return gravity
	 */
	inline Ogre::Real getGravity() const {
		return mGravity;
	}

	/**
	 * Set the gravity
	 * @param gravity
	 */
	inline void setGravity( const Ogre::Real& gravity ) {
		mGravity = gravity;
	}

	/**
	 * Get the AsteroidData type
	 * @return AsteroidData type
	 */
	inline AsteroidType getAsteroidType() const {
		return mAsteroidType;
	}

	/**
	 * Set the AsteroidData type
	 * @param AsteroidData type
	 */
	inline void setAsteroidType( AsteroidType type ) {
		mAsteroidType = type;
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