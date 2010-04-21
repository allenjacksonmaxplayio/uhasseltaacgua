#ifndef HOVERCRAFTUNIVERSEENTITY_H
#define HOVERCRAFTUNIVERSEENTITY_H

#include "Entity.h"

namespace HovUni {

class RaceState;

/**
 * Base class for all Hovercraft Universe Entities
 */
class HovercraftUniverseEntity : public Entity
{
protected:

	/** The racestate */
	RaceState * mRacestate;

public:

	HovercraftUniverseEntity(const Ogre::String& name, const Ogre::String& category, const Ogre::Vector3& position, const Ogre::Vector3& orientation, const Ogre::Vector3& upvector, const Ogre::String& mOgreEntity, float processInterval, unsigned short replicators);

	HovercraftUniverseEntity(const Ogre::String& name, const Ogre::String& category, const Ogre::Vector3& position, const Ogre::Quaternion& orientation, const Ogre::String& mOgreEntity, float processInterval, unsigned short replicators);

	HovercraftUniverseEntity ( ZCom_BitStream* announcementdata, const Ogre::String& category, unsigned short replicators );

	virtual ~HovercraftUniverseEntity(void);

	void setRaceState ( RaceState * racestate );

	RaceState * getRaceState();
};

}

#endif