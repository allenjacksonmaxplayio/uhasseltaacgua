#ifndef STARTPHANTOM_H
#define STARTPHANTOM_H

#include <Physics/Dynamics/Phantom/hkpAabbPhantom.h>

namespace HovUni {

class StartPhantom : public hkpAabbPhantom
{
private:

public:
	StartPhantom(const hkAabb& aabb);

	~StartPhantom(void);

	virtual void addOverlappingCollidable( hkpCollidable* handle );

	virtual void removeOverlappingCollidable( hkpCollidable* handle );
};

}

#endif