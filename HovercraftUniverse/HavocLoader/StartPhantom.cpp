#include <Common/Base/hkBase.h>
#include <Common/Base/System/hkBaseSystem.h>

#include "EntityType.h"
#include "StartPhantom.h"

namespace HovUni {

StartPhantom::StartPhantom(const hkAabb& aabb ):
	hkpAabbPhantom( aabb, 0)
{
}

StartPhantom::~StartPhantom(void)
{
}

void StartPhantom::addOverlappingCollidable( hkpCollidable* handle )
{
	hkpAabbPhantom::addOverlappingCollidable( handle );
}

void StartPhantom::removeOverlappingCollidable( hkpCollidable* handle )
{
	hkpAabbPhantom::removeOverlappingCollidable( handle );
}

}