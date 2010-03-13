#ifndef SpeedBoostPhantom_H
#define SpeedBoostPhantom_H

#include <OgreSharedPtr.h>
#include "SpeedBoost.h"
#include <Physics/Dynamics/Phantom/hkpAabbPhantom.h>

namespace HovUni {

/**
 * This is a boost phantom
 * When a player passes trough it should receive a boost or a slowdown.
 * @author Pieter-Jan Pintens
 */
class SpeedBoostPhantom : public hkpAabbPhantom
{
private:

	Ogre::SharedPtr<SpeedBoost> mBoost;

public:

	/**
	 * Constructor 
	 * @param aabb, the bounding box
	 * @param boost, use a negative value for a slowdown.
	 */
	SpeedBoostPhantom(const hkAabb& aabb, Ogre::SharedPtr<SpeedBoost> boost);

	~SpeedBoostPhantom(void);

	virtual void addOverlappingCollidable( hkpCollidable* handle );

	virtual void removeOverlappingCollidable( hkpCollidable* handle );
};

}

#endif