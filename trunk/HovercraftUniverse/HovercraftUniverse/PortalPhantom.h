#ifndef PORTALPHANTOM_H
#define PORTALPHANTOM_H

#include <Physics/Dynamics/Phantom/hkpAabbPhantom.h>

namespace HovUni {

/**
 * A phantom to check if a player entered a teleport portal
 * @author Pieter-Jan Pintens
 */
class PortalPhantom : public hkpAabbPhantom
{
private:

	//TODO

public:
	PortalPhantom(const hkAabb& aabb);

	~PortalPhantom(void);

	virtual void addOverlappingCollidable( hkpCollidable* handle );

	virtual void removeOverlappingCollidable( hkpCollidable* handle );
};

}

#endif