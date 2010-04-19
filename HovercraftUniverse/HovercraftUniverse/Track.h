#ifndef TRACK_H
#define TRACK_H

#include "NetworkEntity.h"

#include "Exception.h"
#include <tinyxml/tinyxml.h>

namespace HovUni {

class Track : public NetworkEntity {
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
	 * Constructor.
	 *
	 * @param name The name of the track
	 * @param processInterval The process interval
	 */
	Track(const Ogre::String& name);

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

	virtual void setAnnouncementData(ZCom_BitStream* stream){
	}

	virtual void parseEvents(eZCom_Event type, eZCom_NodeRole remote_role, ZCom_ConnID conn_id,	ZCom_BitStream* stream, float timeSince){
	}

};

}

#endif