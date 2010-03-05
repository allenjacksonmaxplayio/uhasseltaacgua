#ifndef CHECKPOINTPHANTOM_H
#define CHECKPOINTPHANTOM_H

#include <Physics/Dynamics/Phantom/hkpAabbPhantom.h>

namespace HovUni {

class CheckpointPhantom : public hkpAabbPhantom
{
private:

public:
	CheckpointPhantom(const hkAabb& aabb);

	~CheckpointPhantom(void);

	virtual void addOverlappingCollidable( hkpCollidable* handle );

	virtual void removeOverlappingCollidable( hkpCollidable* handle );
};

}

#endif