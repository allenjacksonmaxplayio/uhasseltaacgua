#include "HavokEntity.h"
#include "HavokEntityType.h"
#include "Havok.h"

#include "EntityCollisionPrevention.h"

#include <Common/Base/Types/Color/hkColor.h>
#include <Common/Visualize/hkDebugDisplay.h>

#include <Physics/Dynamics/Entity/hkpRigidBody.h>
#include <Physics/Utilities/CharacterControl/CharacterRigidBody/hkpCharacterRigidBodyListener.h>
#include <Physics/Collide/Shape/Convex/Capsule/hkpCapsuleShape.h>

namespace HovUni {

const hkVector4 HavokEntity::UP(0,1,0);

const hkVector4 HavokEntity::FORWARD(1,0,0);

HavokEntity::HavokEntity( hkpWorld * world ):
	mCollisionPreventionBox(HK_NULL), mWorld(world)
{
	mWorld->addReference();
}

HavokEntity::~HavokEntity() {
	//remove world
	mWorld->removeReference();

	//remove collision prevention if set
	removeCollisionPrevention();
}

void HavokEntity::addCollisionPrevention(const hkAabb& aabb, hkReal offset){
	if ( mCollisionPreventionBox == HK_NULL ){
		mWorld->markForWrite();	
		mCollisionPreventionBox = new  EntityCollisionPhantom(aabb, this);
		mWorld->addPhantom(mCollisionPreventionBox);
		mWorld->addAction(new EntityCollisionBinder(this->getRigidBody(),mCollisionPreventionBox,offset));	
		mWorld->unmarkForWrite();
	}
}

void HavokEntity::removeCollisionPrevention(){
	if ( mCollisionPreventionBox != HK_NULL ){
		mWorld->markForWrite();
		mWorld->removePhantom(mCollisionPreventionBox);
		mCollisionPreventionBox->removeReference();
		mCollisionPreventionBox = HK_NULL;
		mWorld->unmarkForWrite();
	}
}
	
}