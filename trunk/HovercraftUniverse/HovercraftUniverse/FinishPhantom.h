#ifndef FINISHPHANTOM_H
#define FINISHPHANTOM_H

#include <Physics/Dynamics/Phantom/hkpAabbPhantom.h>

namespace HovUni {

/**
 * A phantom used to check if a player passes the finish
 * @author Pieter-Jan Pintens
 */
class FinishPhantom : public hkpAabbPhantom
{
private:

public:

	/**
	 * Constructor
	 * @param aabb, the bounding box
	 */
	FinishPhantom(const hkAabb& aabb);

	~FinishPhantom(void);

	virtual void addOverlappingCollidable( hkpCollidable* handle );

	virtual void removeOverlappingCollidable( hkpCollidable* handle );
};

}

#endif