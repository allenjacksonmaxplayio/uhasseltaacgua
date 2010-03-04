#ifndef POWERUPPHANTOM_H
#define POWERUPPHANTOM_H

#include <Physics/Dynamics/Phantom/hkpAabbPhantom.h>

namespace HovUni {

class PowerupPhantom : public hkpAabbPhantom
{
private:

public:
	PowerupPhantom(const hkAabb& aabb);

	~PowerupPhantom(void);

	virtual void addOverlappingCollidable( hkpCollidable* handle );

	virtual void removeOverlappingCollidable( hkpCollidable* handle );
};

}

#endif