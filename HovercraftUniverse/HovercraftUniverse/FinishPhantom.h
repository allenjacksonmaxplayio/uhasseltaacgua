#ifndef FINISHPHANTOM_H
#define FINISHPHANTOM_H

#include <Physics/Dynamics/Phantom/hkpAabbPhantom.h>

namespace HovUni {

class FinishPhantom : public hkpAabbPhantom
{
private:

public:
	FinishPhantom(const hkAabb& aabb);

	~FinishPhantom(void);

	virtual void addOverlappingCollidable( hkpCollidable* handle );

	virtual void removeOverlappingCollidable( hkpCollidable* handle );
};

}

#endif