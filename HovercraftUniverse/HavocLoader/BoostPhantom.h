#ifndef BOOSTPHANTOM_H
#define BOOSTPHANTOM_H

#include <Physics/Dynamics/Phantom/hkpAabbPhantom.h>

namespace HovUni {

class BoostPhantom : public hkpAabbPhantom
{
private:

public:
	BoostPhantom(const hkAabb& aabb);

	~BoostPhantom(void);

	virtual void addOverlappingCollidable( hkpCollidable* handle );

	virtual void removeOverlappingCollidable( hkpCollidable* handle );
};

}

#endif