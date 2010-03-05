#include <Common/Base/hkBase.h>
#include <Common/Base/System/hkBaseSystem.h>

#include "HavocEntityType.h"
#include "FinishPhantom.h"

namespace HovUni {

FinishPhantom::FinishPhantom(const hkAabb& aabb ):
	hkpAabbPhantom( aabb, 0)
{
}

FinishPhantom::~FinishPhantom(void)
{
}

void FinishPhantom::addOverlappingCollidable( hkpCollidable* handle )
{
	hkpAabbPhantom::addOverlappingCollidable( handle );
}

void FinishPhantom::removeOverlappingCollidable( hkpCollidable* handle )
{
	hkpAabbPhantom::removeOverlappingCollidable( handle );
}

}