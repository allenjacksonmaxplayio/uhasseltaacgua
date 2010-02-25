/*#include "Character.h"

#include <Physics/Utilities/CharacterControl/CharacterRigidBody/hkpCharacterRigidBodyListener.h>
#include <Physics/Collide/Shape/Convex/Capsule/hkpCapsuleShape.h>

namespace HovUni {

	Character::Character( hkpWorld * world, hkVector4 startpos, hkQuaternion rotation ): 
		mPhysicsWorld(world), mCharacterRigidBody(HK_NULL)
	{
		mPhysicsWorld->markForWrite();

		//	Create a character rigid body
		{
			// Construct a shape
			hkVector4 vertexA(0.4f,0,0);
			hkVector4 vertexB(-0.4f,0,0);		

			// Create a capsule to represent the character standing
			hkpShape* capsule = new hkpCapsuleShape(vertexA, vertexB, 0.6f);
			
			// Construct a character rigid body
			hkpCharacterRigidBodyCinfo info;
			info.m_mass = 100.0f;
			info.m_shape = capsule;
			info.m_maxForce = 1000.0f;
			info.m_up.set(0,1,0);
			info.m_position = startpos;
			info.m_rotation = rotation;
			info.m_maxSlope = HK_REAL_PI/2.0f;	// Only vertical plane is too steep


			mCharacterRigidBody = new hkpCharacterRigidBody( info );
			{
				hkpCharacterRigidBodyListener* listener = new hkpCharacterRigidBodyListener();
				mCharacterRigidBody->setListener( listener );
				listener->removeReference();
			}
			mPhysicsWorld->addEntity( mCharacterRigidBody->getRigidBody() );

			capsule->removeReference();

		}
		
		// Create the character state machine and context
		{
			hkpCharacterState* state;
			hkpCharacterStateManager* manager = new hkpCharacterStateManager();

			state = new hkpCharacterStateOnGround();
			manager->registerState( state,	HK_CHARACTER_ON_GROUND);
			state->removeReference();

			state = new hkpCharacterStateInAir();
			manager->registerState( state,	HK_CHARACTER_IN_AIR);
			state->removeReference();

			state = new hkpCharacterStateJumping();
			manager->registerState( state,	HK_CHARACTER_JUMPING);
			state->removeReference();

			state = new hkpCharacterStateClimbing();
			manager->registerState( state,	HK_CHARACTER_CLIMBING);
			state->removeReference();

			mCharacterContext = new hkpCharacterContext(manager, HK_CHARACTER_IN_AIR);	
			manager->removeReference();			

			// Set new filter parameters for final output velocity filtering
			// Smoother interactions with small dynamic boxes
			mCharacterContext->setCharacterType(hkpCharacterContext::HK_CHARACTER_RIGIDBODY);
			mCharacterContext->setFilterParameters(0.9f,12.0f,200.0f);
		}

		mPhysicsWorld->unmarkForWrite();
	}

	Character::~Character() {
		
		if ( mCharacterRigidBody != HK_NULL ){
			//remove old hovercraft
			mPhysicsWorld->removeEntity(mCharacterRigidBody->getRigidBody());
			mCharacterRigidBody->removeReference();
			mCharacterRigidBody = HK_NULL;
		}

		//mCharacterContext->removeReference();
		//mCharacterContext = HK_NULL;

		mPhysicsWorld->removeReference();
		mPhysicsWorld = HK_NULL;
	}
}*/