#include "HoverCraftUniverseWorld.h"

#include "PhysicsLoader.h"
#include "CustomOgreMaxScene.h"

#include "HavokEntityType.h"
#include "PhantomTrackAction.h"

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

bool HoverCraftUniverseWorld::loadSceneFile ( const char * filename ){
	
	PhysicsLoader loader(this, ".\\..\\..\\..\\art\\models\\");

	CustomOgreMaxScene scene;

	/**
	 * Load world
	 */
	scene.Load(Ogre::String(filename),CustomOgreMaxScene::SKIP_ENVIRONMENT | CustomOgreMaxScene::SKIP_SHADOWS | CustomOgreMaxScene::SKIP_SKY | CustomOgreMaxScene::SKIP_TERRAIN | CustomOgreMaxScene::SKIP_VISIBILITY_FLAG_ALIASES,&loader);

	return true;
}

void HoverCraftUniverseWorld::update() {
	//SETUP CHARACTERS

}

Character * HoverCraftUniverseWorld::getCharacter(const char * name) {
	if (name == 0 )
		return HK_NULL;

	Character * result = HK_NULL;
	mCharactersMap.get(name,&result);
	return result;
}

void HoverCraftUniverseWorld::addCharacter( const char * name, const char * type, int pos ){

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

	Character * c = new Character(mPhysicsWorld,name,&info,m_characterContext);
	mCharactersMap.insert(name,c);

	m_characterContext->removeReference();


}

}
