#include "HavokEntity.h"
#include "HavokEntityType.h"
#include "Havok.h"

#include "Entity.h"

#include <Common/Base/Types/Color/hkColor.h>
#include <Common/Visualize/hkDebugDisplay.h>

#include <Physics/Dynamics/Entity/hkpRigidBody.h>
#include <Physics/Utilities/CharacterControl/CharacterRigidBody/hkpCharacterRigidBodyListener.h>

namespace HovUni {

HavokEntity::HavokEntity( hkpWorld * world, Entity * entity, hkpCharacterRigidBodyCinfo * info, hkpCharacterContext * characterContext ): 
	mPhysicsWorld(world), mCharacterRigidBody(HK_NULL), mCharacterContext(characterContext), mEntity(entity)
{
	mForward.set( 0.0f, 0.0f, -1.0f );
	mUp.set(0.0f,1.0f,0.0f);

	//add references here
	mCharacterContext->addReference();
	mPhysicsWorld->addReference();

	mPhysicsWorld->markForWrite();

	//Create a character rigid body
	mCharacterRigidBody = new hkpCharacterRigidBody( *info );
	hkpCharacterRigidBodyListener* listener = new hkpCharacterRigidBodyListener();
	mCharacterRigidBody->setListener( listener );
	listener->removeReference();		
	hkpRigidBody * charbody = mCharacterRigidBody->getRigidBody();

	//set name and type
	charbody->setUserData(reinterpret_cast<hkUlong>(this));
	HavokEntityType::setEntityType(charbody,HavokEntityType::CHARACTER);

	mPhysicsWorld->addEntity( charbody );
	mPhysicsWorld->unmarkForWrite();
}

HavokEntity::~HavokEntity() {	
	mCharacterContext->removeReference();
	mCharacterContext = HK_NULL;

	//remove the reference
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

hkpCharacterRigidBody * HavokEntity::getCharacterRigidBody() {
	return mCharacterRigidBody;
}

void HavokEntity::updateUp( hkVector4& newUp ) {
	// Only change gravity if the change isn't negligible
	if( mUp.dot3(newUp) < 1e-6f)
	{
		// don't reorient character when it has an invalid rotational axis
		//  (this may happen the first few frames)
		if( mCharacterRigidBody->getRigidBody()->getRotation().hasValidAxis()) {
			hkRotation rbRotation; rbRotation.set(mCharacterRigidBody->getRigidBody()->getRotation());
			hkVector4& oldForward = rbRotation.getColumn(0);
			hkVector4 newRot; 
			newRot.setCross(oldForward, newUp);
			mForward.setCross(newUp, newRot);
			mForward.normalize3();
		}
	}

	mUp = newUp;
}
	
}