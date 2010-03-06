#ifndef STARTPHANTOM_H
#define STARTPHANTOM_H

#include <Physics/Dynamics/Phantom/hkpAabbPhantom.h>

namespace HovUni {

/**
 * A phantom to check if a player has passed the start line
 * @author Pieter-Jan Pintens
 */
class StartPhantom : public hkpAabbPhantom
{
private:

public:
	/**
	 * Constructor
	 * @param aabb, the bounding box
	 */
	StartPhantom(const hkAabb& aabb);

	~StartPhantom(void);

	virtual void addOverlappingCollidable( hkpCollidable* handle );

	virtual void removeOverlappingCollidable( hkpCollidable* handle );
};

}

#endif