#include <Common/Base/hkBase.h>
#include <Common/Base/System/hkBaseSystem.h>

#include "HavocEntityType.h"
#include "PortalPhantom.h"

namespace HovUni {

PortalPhantom::PortalPhantom(const hkAabb& aabb ):
	hkpAabbPhantom( aabb, 0)
{
}

PortalPhantom::~PortalPhantom(void)
{
}

void PortalPhantom::addOverlappingCollidable( hkpCollidable* handle )
{
	hkpAabbPhantom::addOverlappingCollidable( handle );
}

void PortalPhantom::removeOverlappingCollidable( hkpCollidable* handle )
{
	hkpAabbPhantom::removeOverlappingCollidable( handle );
}

}