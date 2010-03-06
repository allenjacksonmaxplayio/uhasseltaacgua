#include "Character.h"
#include "HavocEntityType.h"

#include <Common/Base/Types/Color/hkColor.h>
#include <Common/Visualize/hkDebugDisplay.h>

#include <Physics/Dynamics/Entity/hkpRigidBody.h>
#include <Physics/Utilities/CharacterControl/CharacterRigidBody/hkpCharacterRigidBodyListener.h>

namespace HovUni {

Character::Character( hkpWorld * world, hkpCharacterRigidBodyCinfo * info, hkpCharacterContext * characterContext, Controller * controller ): 
	mPhysicsWorld(world), mCharacterRigidBody(HK_NULL), mCharacterContext(characterContext), mController(controller)
{
	mForward.set( 1.0f, 0.0f, 0.0f );
	mCharacterForward.set( 1.0f, 0.0f, 0.0f );

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
	HavocEntityType::setEntityType(charbody,HavocEntityType::CHARACTER);
	mPhysicsWorld->addEntity( charbody );
	mPhysicsWorld->unmarkForWrite();
}

Character::~Character() {	
	mCharacterContext->removeReference();
	mCharacterContext = HK_NULL;

	//remove the reference
	mPhysicsWorld->removeEntity(mCharacterRigidBody->getRigidBody());
	mCharacterRigidBody->removeReference();
	mCharacterRigidBody = HK_NULL;

	mPhysicsWorld->removeReference();
	mPhysicsWorld = HK_NULL;
}

void Character::update(){
	mController->getEvents();
}
	
}