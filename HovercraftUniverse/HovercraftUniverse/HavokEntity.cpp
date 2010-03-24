#include "HavokEntity.h"
#include "HavokEntityType.h"
#include "Havok.h"

#include "Entity.h"

#include <Common/Base/Types/Color/hkColor.h>
#include <Common/Visualize/hkDebugDisplay.h>

#include <Physics/Dynamics/Entity/hkpRigidBody.h>
#include <Physics/Utilities/CharacterControl/CharacterRigidBody/hkpCharacterRigidBodyListener.h>
#include <Physics/Collide/Shape/Convex/Capsule/hkpCapsuleShape.h>

namespace HovUni {

HavokEntity::HavokEntity( hkpWorld * world, Entity * entity ): 
	mPhysicsWorld(world), mCharacterRigidBody(HK_NULL), mCharacterContext(HK_NULL), mEntity(entity)
{
	mForward.set( 1.0f, 0.0f, 0.0f );
	mUp.set(0.0f,1.0f,0.0f);

	mPhysicsWorld->addReference();
}

void HavokEntity::load( const hkVector4& position ){
	assert(mCharacterContext == HK_NULL && mCharacterRigidBody == HK_NULL);

	loadCharacter(position);

	assert(mCharacterContext != HK_NULL && mCharacterRigidBody != HK_NULL);
}

HavokEntity::~HavokEntity() {	
	//remove the references
	mCharacterContext->removeReference();
	mCharacterContext = HK_NULL;
	
	mPhysicsWorld->removeEntity(mCharacterRigidBody->getRigidBody());
	mCharacterRigidBody->removeReference();
	mCharacterRigidBody = HK_NULL;

	mPhysicsWorld->removeReference();
	mPhysicsWorld = HK_NULL;
}

const hkVector4& HavokEntity::getPosition() const {
	return mCharacterRigidBody->getPosition();
}

const hkQuaternion& HavokEntity::getOrientation() const {
	return mCharacterRigidBody->getRigidBody()->getRotation();
}

Entity * HavokEntity::getEntity()  {
	return mEntity;
}

const hkVector4& HavokEntity::getForward() const {
	return mForward;
}

hkVector4& HavokEntity::getForward() {
	return mForward;
}

void HavokEntity::updateUp( const hkVector4& newUp ) {
	// Only change gravity if the change isn't negligible
	if( mUp.dot3(newUp) < 1e-6f)
	{
		hkRotation rbRotation; rbRotation.set(mCharacterRigidBody->getRigidBody()->getRotation());
		hkVector4& oldForward = rbRotation.getColumn(0);
		hkVector4 newRot;
		newRot.setCross(oldForward, newUp);
		mForward.setCross(newUp, newRot);
		mForward.normalize3();
	}

	mUp = newUp;
}
	
}