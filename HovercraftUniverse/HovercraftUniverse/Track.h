#ifndef TRACK_H
#define TRACK_H

#include "ParseException.h"
#include <tinyxml/tinyxml.h>
#include <OgreString.h>
#include <OgrePlatform.h>
#include "Entity.h"

namespace HovUni {

class Track : public Entity{
private:

	/**
	 * Name of the track
	 */
	Ogre::String mName;

	/**
	 * Physics filename
	 */
	Ogre::String mPhysicsFileName;

	/**
	 * Minimum players
	 */
	Ogre::int32 mMinimumPlayers;

	/**
	 * Minimum players
	 */
	Ogre::int32 mMaximumPlayers;

public:

	static const Ogre::String CATEGORY;
	
	Track(const Ogre::String& name, const Ogre::Vector3& position, const Ogre::Quaternion& orientation, float processInterval);

	/**
	 * Constructor
	 * @param data
	 * @throws ParseException
	 */
	void load(TiXmlElement * data) throw(ParseException);

	/**
	 * Destructor
	 */
	virtual ~Track(void);

	/**
	 * Get physics filename
	 * @return the physics filename
	 */
	inline Ogre::String getPhysicsFileName() const {
		return mPhysicsFileName;
	}

	/**
	 * Set physics filename
	 * @param physics filename
	 */
	inline void setPhysicsFileName(const Ogre::String& physicsFileName){
		mPhysicsFileName = physicsFileName;
	}

	/**
	 * Get minimum players
	 * @return the minimum players
	 */
	inline Ogre::int32 getMinimumPlayers() const {
		return mMinimumPlayers;
	}

	/**
	 * Set minimum players
	 * @param minplayers
	 */
	inline void setMinimumPlayers(Ogre::int32 minplayers){
		mMinimumPlayers = minplayers;
	}


	/**
	 * Get maximum players
	 * @return the maximum players
	 */
	inline Ogre::int32 getMaximumPlayers() const {
		return mMaximumPlayers;
	}

	/**
	 * Set maximum players
	 * @param maximum
	 */
	inline void setMaximumPlayers(Ogre::int32 maximum){
		mMaximumPlayers = maximum;
	}

	/**
	 * Get name
	 * @return the name
	 */
	inline Ogre::String getName() const {
		return mName;
	}

	/**
	 * Set name
	 * @param name
	 */
	inline void setName(const Ogre::String& name){
		mName = name;
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