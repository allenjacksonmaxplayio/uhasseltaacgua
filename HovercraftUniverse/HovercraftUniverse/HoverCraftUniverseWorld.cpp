#include "HoverCraftUniverseWorld.h"

#include "ServerLoader.h"
#include "CustomOgreMaxScene.h"

#include "HavokEntityType.h"
#include "PhantomTrackAction.h"

#include "Hovercraft.h"

#include <Physics/Collide/Shape/Convex/Capsule/hkpCapsuleShape.h>
#include <Physics/Collide/Filter/Group/hkpGroupFilterSetup.h>

namespace HovUni {

HoverCraftUniverseWorld::HoverCraftUniverseWorld(hkReal timestep):
	AbstractHavokWorld(timestep), mStartPositions(0), mPowerupPositions(128), mResetPositions(32)
{
	mStart = HK_NULL;
	mFinish = HK_NULL;

}

HoverCraftUniverseWorld::~HoverCraftUniverseWorld(void)
{
	if ( mStart != HK_NULL ) {
		mStart->removeReference();
	}

	if ( mFinish != HK_NULL ) {
		mFinish->removeReference();
	}

	//TODO
	//delete checkpoints
	//delete characters
	//...
}

void HoverCraftUniverseWorld::postStep() {
	// Rotate the character
	hkStorageStringMap<HavokEntity*>::Iterator i = mCharactersMap.getIterator ();
	while ( mCharactersMap.isValid(i) ){
		HavokEntity * ch = mCharactersMap.getValue(i); 
		ch->reorientCharacter();	
		i = mCharactersMap.getNext(i);
	}
}

void HoverCraftUniverseWorld::preStep() {
	//SETUP CHARACTERS

	hkStorageStringMap<HavokEntity*>::Iterator i = mCharactersMap.getIterator ();
	while ( mCharactersMap.isValid(i) ){
		HavokEntity * ch = mCharactersMap.getValue(i); 
		ch->update();	
		i = mCharactersMap.getNext(i);
	}
}

HavokEntity * HoverCraftUniverseWorld::getCharacter(const char * name) {
	if (name == 0 )
		return HK_NULL;

	HavokEntity * result = HK_NULL;
	mCharactersMap.get(name,&result);
	return result;
}

void HoverCraftUniverseWorld::addCharacter( Hovercraft * entity, int pos ){

	//	Create a character rigid body object
	// Construct a shape
	hkVector4 vertexA( 0.0f,  0.4f, 0.0f );
	hkVector4 vertexB( 0.0f, -0.4f, 0.0f );

	// Construct a character rigid body
	hkpCharacterRigidBodyCinfo info;
	info.m_mass = 80.0f;
	info.m_shape = new hkpCapsuleShape( vertexA, vertexB, 0.6f );;

	info.m_maxForce = 8000.0f;
	info.m_position = mStartPositions[pos];
	info.m_maxSlope = 45.0f * HK_REAL_DEG_TO_RAD;
	info.m_friction = 0.25f;
	

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

	hkpCharacterContext * m_characterContext = new hkpCharacterContext( manager, HK_CHARACTER_IN_AIR );
	manager->removeReference();

	// Set character type
	m_characterContext->setCharacterType( hkpCharacterContext::HK_CHARACTER_RIGIDBODY );

	HavokEntity * c = new HavokEntity(mPhysicsWorld,entity,&info,m_characterContext);
	mCharactersMap.insert(entity->getName().c_str(),c);

	m_characterContext->removeReference();


}

}
