#include <Common/Base/hkBase.h>
#include <Common/Base/System/hkBaseSystem.h>

#include "EntityType.h"
#include "BoostPhantom.h"

namespace HovUni {

BoostPhantom::BoostPhantom(const hkAabb& aabb ):
	hkpAabbPhantom( aabb, 0)
{
}

BoostPhantom::~BoostPhantom(void)
{
}

void BoostPhantom::addOverlappingCollidable( hkpCollidable* handle )
{
	hkpAabbPhantom::addOverlappingCollidable( handle );
}

void BoostPhantom::removeOverlappingCollidable( hkpCollidable* handle )
{
	hkpAabbPhantom::removeOverlappingCollidable( handle );
}

}