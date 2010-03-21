#include "HavokHovercraft.h"
#include "Havok.h"

#include <Common/Base/Types/Color/hkColor.h>
#include <Common/Visualize/hkDebugDisplay.h>

#include <Physics/Dynamics/Entity/hkpRigidBody.h>
#include <Physics/Utilities/CharacterControl/CharacterRigidBody/hkpCharacterRigidBodyListener.h>

#include "Hovercraft.h"

namespace HovUni {

HavokHovercraft::HavokHovercraft(hkpWorld * world, Hovercraft * entity, hkpCharacterRigidBodyCinfo * info,  hkpCharacterContext * characterContext):
	HavokEntity( world, entity, info, characterContext)
{
}

HavokHovercraft::~HavokHovercraft(void)
{
}

void HavokHovercraft::postStep()
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


void HavokHovercraft::preStep(){
	mPhysicsWorld->markForWrite();

	Hovercraft * hovercraft = dynamic_cast<Hovercraft *>(mEntity);

	const BasicEntityEvent& status = hovercraft->getMovingStatus();

	hkStepInfo stepInfo;
	stepInfo.m_deltaTime = Havok::getSingleton().getTimeStep();
	stepInfo.m_invDeltaTime = 1.0f / Havok::getSingleton().getTimeStep();


	//1.0 forward = Hovercraft::MAXSPEED

	//keep speed values
	hkReal maxspeed = hovercraft->getMaximumSpeed();
	hkReal speed = hovercraft->getSpeed();

	//Speed on a scale [0-1]
	//hkReal scaledmaxspeed = hovercraft->getMaximumSpeed() / Hovercraft::MAXSPEED;

	float deltaAngle = 0.f;
	float posX = 0.f;
	float posY = 0.f;

	//speeding
	if ( status.moveForward() ){	
		//accelerate, update speed
		speed += hovercraft->getAcceleration() * Havok::getSingleton().getTimeStep();
		if ( speed > hovercraft->getMaximumSpeed() ){
			hovercraft->setSpeed(hovercraft->getMaximumSpeed());
		} else {
			hovercraft->setSpeed(speed);
		}	
	}

	//braking..
	if ( status.moveBackward() ){
		speed -= hovercraft->getAcceleration() * Havok::getSingleton().getTimeStep();
		
		if ( speed < -1 * hovercraft->getMaximumSpeed() ){
			hovercraft->setSpeed(-1 * hovercraft->getMaximumSpeed());
		} else {
			hovercraft->setSpeed(speed);
		}
	}

	posY = speed / Hovercraft::MAXSPEED; 


	if ( status.moveLeft() ){
		//posX += 1.f;
		//ROTATE

	}
	if ( status.moveRight() ){
		//posX -= 1.f;
		//ROTATE
	}

	

	
	// Update the character context
	mCharacterRigidBody->m_up = mUp;
/*
		float deltaAngle;

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
			newRotation.setAxisAngle( mUp, characterAngle );
 			mForward.setRotatedDir( newRotation, m_cameraForward );
 			mForward.normalize3();
		}
*/
	

	
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

			input.m_forward = mForward;
		}



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
	}


	//DEBUG SHOW FARWARD AS GREEN ARROW
	hkRotation characterRotation;
	characterRotation.set( mCharacterRigidBody->getRigidBody()->getRotation() );
	HK_DISPLAY_ARROW( mCharacterRigidBody->getPosition(), characterRotation.getColumn(0), hkColor::RED );
	HK_DISPLAY_ARROW( mCharacterRigidBody->getPosition(), characterRotation.getColumn(1), hkColor::LIMEGREEN );
	HK_DISPLAY_ARROW( mCharacterRigidBody->getPosition(), characterRotation.getColumn(2), hkColor::BLUE );

	mPhysicsWorld->unmarkForWrite();
}

}