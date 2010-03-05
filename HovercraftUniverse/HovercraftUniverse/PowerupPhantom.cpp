#include <Common/Base/hkBase.h>
#include <Common/Base/System/hkBaseSystem.h>

#include "HavocEntityType.h"
#include "PowerupPhantom.h"

namespace HovUni {

PowerupPhantom::PowerupPhantom(const hkAabb& aabb ):
	hkpAabbPhantom( aabb, 0)
{
}

PowerupPhantom::~PowerupPhantom(void)
{
}

void PowerupPhantom::addOverlappingCollidable( hkpCollidable* handle )
{
	hkpAabbPhantom::addOverlappingCollidable( handle );
}

void PowerupPhantom::removeOverlappingCollidable( hkpCollidable* handle )
{
	hkpAabbPhantom::removeOverlappingCollidable( handle );
}

}