#include <Common/Base/hkBase.h>
#include <Common/Base/System/hkBaseSystem.h>

#include "EntityType.h"
#include "CheckpointPhantom.h"

namespace HovUni {

CheckpointPhantom::CheckpointPhantom(const hkAabb& aabb ):
	hkpAabbPhantom( aabb, 0)
{
}

CheckpointPhantom::~CheckpointPhantom(void)
{
}

void CheckpointPhantom::addOverlappingCollidable( hkpCollidable* handle )
{
	hkpAabbPhantom::addOverlappingCollidable( handle );
}

void CheckpointPhantom::removeOverlappingCollidable( hkpCollidable* handle )
{
	hkpAabbPhantom::removeOverlappingCollidable( handle );
}

}