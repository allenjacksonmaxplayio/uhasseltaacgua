#ifndef BOOSTPHANTOM_H
#define BOOSTPHANTOM_H

#include <Physics/Dynamics/Phantom/hkpAabbPhantom.h>

namespace HovUni {

/**
 * This is a boost phantom
 * When a player passes trough it should receive a boost or a slowdown.
 * @author Pieter-Jan Pintens
 */
class BoostPhantom : public hkpAabbPhantom
{
private:

	hkReal mBoost;

public:

	/**
	 * Constructor 
	 * @param aabb, the bounding box
	 * @param boost, use a negative value for a slowdown.
	 */
	BoostPhantom(const hkAabb& aabb, hkReal boost);

	~BoostPhantom(void);

	virtual void addOverlappingCollidable( hkpCollidable* handle );

	virtual void removeOverlappingCollidable( hkpCollidable* handle );
};

}

#endif