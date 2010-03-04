#ifndef PORTALPHANTOM_H
#define PORTALPHANTOM_H

#include <Physics/Dynamics/Phantom/hkpAabbPhantom.h>

namespace HovUni {

class PortalPhantom : public hkpAabbPhantom
{
private:

public:
	PortalPhantom(const hkAabb& aabb);

	~PortalPhantom(void);

	virtual void addOverlappingCollidable( hkpCollidable* handle );

	virtual void removeOverlappingCollidable( hkpCollidable* handle );
};

}

#endif