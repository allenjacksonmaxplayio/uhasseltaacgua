#ifndef TRACK_H
#define TRACK_H

#include "Entity.h"

#include "Exception.h"
#include <tinyxml/tinyxml.h>

namespace HovUni {

class Track : public Entity{
private:

	/**
	 * Name of the track
	 */
	Ogre::String mDisplayName;

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

	/**
	 * The category used for tracks
	 */
	static const Ogre::String CATEGORY;
	
	/**
	 * Constructor.
	 *
	 * @param name The name of the track
	 * @param position
	 * @param quaternion
	 * @param processInterval The process interval
	 */
	Track(const Ogre::String& name, const Ogre::Vector3& position, const Ogre::Quaternion& orientation, float processInterval);

	/**
	 * Constructor.
	 * 
	 * @param announcedata
	 */
	Track( ZCom_BitStream* announcedata );

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
	inline Ogre::String getDisplayName() const {
		return mDisplayName;
	}

	/**
	 * Set name
	 * @param name
	 */
	inline void setDisplayName(const Ogre::String& name){
		mDisplayName = name;
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