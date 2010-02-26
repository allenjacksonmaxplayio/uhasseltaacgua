#include "Character.h"

#include <Physics/Utilities/CharacterControl/CharacterRigidBody/hkpCharacterRigidBodyListener.h>

namespace HovUni {

	Character::Character( hkpWorld * world, hkpCharacterRigidBodyCinfo * info ): 
		mPhysicsWorld(world), mCharacterRigidBody(HK_NULL)
	{
/*		mPhysicsWorld->markForWrite();

		//	Create a character rigid body
		{
			mCharacterRigidBody = new hkpCharacterRigidBody( *info );
			{
				hkpCharacterRigidBodyListener* listener = new hkpCharacterRigidBodyListener();
				mCharacterRigidBody->setListener( listener );
				listener->removeReference();
			}
			mPhysicsWorld->addEntity( mCharacterRigidBody->getRigidBody() );
		}
	
		mPhysicsWorld->unmarkForWrite();*/
	}

	Character::~Character() {
/*		
		if ( mCharacterRigidBody != HK_NULL ){
			//remove old hovercraft
			mPhysicsWorld->removeEntity(mCharacterRigidBody->getRigidBody());
			mCharacterRigidBody->removeReference();
			mCharacterRigidBody = HK_NULL;
		}

		//mCharacterContext->removeReference();
		//mCharacterContext = HK_NULL;

		mPhysicsWorld->removeReference();
		mPhysicsWorld = HK_NULL;*/
	}

	
}