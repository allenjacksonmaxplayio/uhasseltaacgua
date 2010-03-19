#include "HavokEntity.h"
#include "HavokEntityType.h"
#include "Havok.h"

#include <Common/Base/Types/Color/hkColor.h>
#include <Common/Visualize/hkDebugDisplay.h>

#include <Physics/Dynamics/Entity/hkpRigidBody.h>
#include <Physics/Utilities/CharacterControl/CharacterRigidBody/hkpCharacterRigidBodyListener.h>

namespace HovUni {

HavokEntity::HavokEntity( hkpWorld * world, Entity * entity, hkpCharacterRigidBodyCinfo * info, hkpCharacterContext * characterContext ): 
	mPhysicsWorld(world), mCharacterRigidBody(HK_NULL), mCharacterContext(characterContext), mEntity(entity)
{
	mForward.set( 1.0f, 0.0f, 0.0f );
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

void HavokEntity::reorientCharacter()
{
	mPhysicsWorld->markForWrite();
	hkRotation newOrientation;
	newOrientation.getColumn(0) = mForward;
	newOrientation.getColumn(1) = mUp;
	newOrientation.getColumn(2).setCross( newOrientation.getColumn(0), newOrientation.getColumn(1) );
	newOrientation.renormalize();	

	const hkReal gain = 0.5f;

	const hkQuaternion& currentOrient = mCharacterRigidBody->getRigidBody()->getRotation();

	hkQuaternion desiredOrient;
	desiredOrient.set( newOrientation );

	hkVector4 angle;
	hkVector4 angularVelocity;
	currentOrient.estimateAngleTo( desiredOrient, angle );
	angularVelocity.setMul4( gain / Havok::getSingleton().getTimeStep(), angle );

	mCharacterRigidBody->setAngularVelocity( angularVelocity );

	mPhysicsWorld->unmarkForWrite();
}

void HavokEntity::update(){
	mPhysicsWorld->markForWrite();

	//const BasicEntityEvent& status = mEntity->getMovingStatus();


	//if ( status.moveForward() )
	//	mCharacterRigidBody->getRigidBody()->applyForce(Havok::getSingleton().getTimeStep(),mForward);


/*	hkVector4 accumulatedDirection = hkVector4::getZero();
	float accumulatedRotation = 0.0f;
	float accumulatedTilt = mTilt;

	// calculate new direction
	if (mMovingStatus.moveLeft()) { 
		// check direction, we won't allow turning without moving
		if (mMovingStatus.moveForward()) {
			accumulatedRotation += 1.0f;
		} else if (mMovingStatus.moveBackward()) {
			accumulatedRotation -= 1.0f;
		}
		// set tilt
		if ((mMovingStatus.moveForward() || mMovingStatus.moveBackward()) && mTilt > -20.0f) {
			mTilt -= 0.5f;
		}
	}
	if (mMovingStatus.moveRight()) { 
		// check direction, we won't allow turning without moving
		if (mMovingStatus.moveForward()) {
			accumulatedRotation -= 1.0f;
		} else if (mMovingStatus.moveBackward()) {
			accumulatedRotation += 1.0f;
		}
		// set tilt
		if ((mMovingStatus.moveForward() || mMovingStatus.moveBackward()) && mTilt < 20.0f) {
			mTilt += 0.5f;
		}
	}
	// if not turning, lower tilt
	if ((!mMovingStatus.moveLeft() && !mMovingStatus.moveRight()) || 
				((mMovingStatus.moveLeft() || mMovingStatus.moveRight()) && (!mMovingStatus.moveForward() && !mMovingStatus.moveBackward()))) {
		mTilt *= 0.9f;
	}
	

	// calculate orientation
	// TODO: Should be the UpVector, but in the tilt test this would give weird results...
	//Ogre::Quaternion quat = Ogre::Quaternion(Ogre::Degree(Ogre::Real(accumulatedRotation)), getUpVector());
	Ogre::Quaternion rotation = Ogre::Quaternion(Ogre::Degree(Ogre::Real(accumulatedRotation)), Ogre::Vector3::UNIT_Y);
	changeOrientation(rotation);

	//calculate tilt
	accumulatedTilt = mTilt - accumulatedTilt;
	Ogre::Quaternion tilt = Ogre::Quaternion(Ogre::Degree(Ogre::Real(accumulatedTilt)), getOrientation());
	changeOrientation(tilt);
	

	// move forward and/or backward
	if (mMovingStatus.moveForward()) { 
		accumulatedDirection += getOrientation(); 
	}
	if (mMovingStatus.moveBackward()) { 
		accumulatedDirection -= getOrientation(); 
	}
	accumulatedDirection.normalise();

	accumulatedDirection * timeSince * 100);*/



/*


	//TODO INPUT MAKE THE DUDE DO WHAT YOU WANT HIM TO DO

	
	// Update the character context
	mCharacterRigidBody->m_up = mUp;
	hkReal posX = 0.0f;
	hkReal posY = 0.0f;
	
	
	if( !m_detachedCamera )
	{
		float deltaAngle;
		CharacterUtils::getUserInputForCharacter( m_env, deltaAngle, posX, posY );

		if( ( ( hkMath::fabs( posX ) < HK_REAL_MAX ) && ( hkMath::fabs( posY ) < HK_REAL_MAX ) ) && ( posX || posY ) )
		{
			// find new orientation in local space
			hkVector4 newForward( -posY, 0.0f, -posX );
			hkVector4 absoluteForward( 1.0f, 0.0f, 0.0f );
			hkReal characterAngle = hkMath::acos( absoluteForward.dot3( newForward ) );

			// Calculate cross product to get sign of rotation.
			hkVector4 crossProduct;
			crossProduct.setCross( absoluteForward, newForward );

			if( crossProduct(1) < 0.0f )
			{
				characterAngle *= -1.0f;
			}

			// Rotate the character's rigid body to face in the direction it's moving
			hkRotation newRotation;
			newRotation.setAxisAngle( m_worldUp, characterAngle );
 			m_characterForward.setRotatedDir( newRotation, m_cameraForward );
 			m_characterForward.normalize3();
		}
	}
	

	
	hkpCharacterInput input;
	hkpCharacterOutput output;
	{
		HK_TIMER_BEGIN( "set character state", HK_NULL );

		input.m_atLadder = false;
		input.m_inputLR = posX;
		input.m_inputUD = posY;
		input.m_wantJump = false;


		// Check that we have a valid rotation. Probably won't for the first couple of frames.
		if( !( mCharacterRigidBody->getRigidBody()->getRotation().hasValidAxis() ) )
		{
			input.m_up = mUp;
			input.m_forward = mForward;
		}
		else
		{
			input.m_up = mUp;

			// Recalculate m_forward so it's perpendicular to m_worldUp
			hkVector4 newRot;
			newRot.setCross( mForward, mUp );

			// Display character's current heading
			hkRotation characterRotation;
			characterRotation.set( mCharacterRigidBody->getRigidBody()->getRotation() );
			HK_DISPLAY_ARROW( mCharacterRigidBody->getPosition(), characterRotation.getColumn(0), hkColor::LIMEGREEN );

			input.m_forward = mForward;
		}

		hkStepInfo stepInfo;
		stepInfo.m_deltaTime = Havok::getSingleton().getTimeStep();
		stepInfo.m_invDeltaTime = 1.0f / Havok::getSingleton().getTimeStep();

		input.m_stepInfo = stepInfo;
		input.m_characterGravity.setMul4( -20.0f, mUp );
		input.m_velocity = mCharacterRigidBody->getRigidBody()->getLinearVelocity();
		input.m_position = mCharacterRigidBody->getRigidBody()->getPosition();
		mCharacterRigidBody->checkSupport( stepInfo, input.m_surfaceInfo );

		HK_TIMER_END();
	}

	// Apply the character state machine
	{
		HK_TIMER_BEGIN( "update character state", HK_NULL );

		mCharacterContext->update( input, output );

		HK_TIMER_END();
	}

	//Apply the player character controller
	{
		HK_TIMER_BEGIN( "simulate character", HK_NULL );

		// Set output velocity from state machine into character rigid body
		mCharacterRigidBody->setLinearVelocity( output.m_velocity, Havok::getSingleton().getTimeStep() );

		HK_TIMER_END();
	}*/


	//DEBUG SHOW FARWARD AS GREEN ARROW
	hkRotation characterRotation;
	characterRotation.set( mCharacterRigidBody->getRigidBody()->getRotation() );
	HK_DISPLAY_ARROW( mCharacterRigidBody->getPosition(), characterRotation.getColumn(0), hkColor::RED );
	HK_DISPLAY_ARROW( mCharacterRigidBody->getPosition(), characterRotation.getColumn(1), hkColor::LIMEGREEN );
	HK_DISPLAY_ARROW( mCharacterRigidBody->getPosition(), characterRotation.getColumn(2), hkColor::BLUE );

	mPhysicsWorld->unmarkForWrite();
}
	
}