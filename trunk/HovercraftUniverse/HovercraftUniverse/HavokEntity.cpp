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
	mForward.set( 0.0f, 0.0f, -1.0f );
	mUp.set(0.0f,1.0f,0.0f);

	mPhysicsWorld->addReference();
}

void HavokEntity::loadCharacter( const hkVector4& position ){
	mPhysicsWorld->markForWrite();

	// Create a character rigid body object
	// Construct a shape
	hkVector4 vertexA( 0.0f,  0.4f, 0.0f );
	hkVector4 vertexB( 0.0f, -0.4f, 0.0f );

	// Construct a character rigid body
	hkpCharacterRigidBodyCinfo info;
	info.m_mass = 8.0f;
	info.m_shape = new hkpCapsuleShape( vertexA, vertexB, 0.6f );;

	info.m_maxForce = 8000.0f;
	info.m_position = position;
	info.m_maxSlope = 45.0f * HK_REAL_DEG_TO_RAD;
	info.m_friction = 0.1f;
	

	hkpCharacterState* state;
	hkpCharacterStateManager* manager = new hkpCharacterStateManager();

	state = new hkpCharacterStateOnGround();
	manager->registerState( state,	HK_CHARACTER_ON_GROUND );

	static_cast<hkpCharacterStateOnGround*>( manager->getState( HK_CHARACTER_ON_GROUND ) )->setDisableHorizontalProjection( true );
	state->removeReference();

	state = new hkpCharacterStateInAir();
	manager->registerState( state,	HK_CHARACTER_IN_AIR );
	state->removeReference();

	state = new hkpCharacterStateJumping();
	manager->registerState( state,	HK_CHARACTER_JUMPING );
	state->removeReference();

	mCharacterContext = new hkpCharacterContext( manager, HK_CHARACTER_IN_AIR );

	// Set character type
	mCharacterContext->setCharacterType( hkpCharacterContext::HK_CHARACTER_RIGIDBODY );

	//Create a character rigid body
	mCharacterRigidBody = new hkpCharacterRigidBody( info );
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

void HavokEntity::load( const hkVector4& position ){
	assert(mCharacterContext == HK_NULL && mCharacterRigidBody == HK_NULL);

	loadCharacter(position);

	assert(mCharacterContext != HK_NULL && mCharacterRigidBody != HK_NULL);
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

void HavokEntity::updateUp( const hkVector4& newUp ) {
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