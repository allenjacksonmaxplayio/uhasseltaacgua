#include "HoverCraftCharacter.h"

namespace HovUni {

HoverCraftCharacter::HoverCraftCharacter(hkpWorld * world , hkpCharacterRigidBodyCinfo * info,  hkpCharacterContext * characterContext):
	Character(world, info, characterContext )
{
}

HoverCraftCharacter::~HoverCraftCharacter(void)
{
}


void HoverCraftCharacter::update( UserInput& input ){

/*	mPhysicsWorld->markForWrite();

	// Update the character context
	mCharacterRigidBody->m_up = mUp;

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
		mCharacterForward.setRotatedDir( newRotation, mForward );
		mCharacterForward.normalize3();
	}

	HK_TIMER_BEGIN( "set character state", HK_NULL );
	hkpCharacterInput input;
	hkpCharacterOutput output;
	{
		input.m_atLadder = false;
		input.m_inputLR = posX;
		input.m_inputUD = posY;
		input.m_wantJump = false;

		// Check that we have a valid rotation. Probably won't for the first couple of frames.
		if( !( mCharacterRigidBody->getRigidBody()->getRotation().hasValidAxis() ) )
		{
			input.m_up = hkVector4( 0.0f, 0.0f, 1.0f );
			input.m_forward = mForward;
		}
		else
		{
			input.m_up = mUp;

			// Recalculate m_forward so it's perpendicular to m_worldUp
			hkVector4 newRot;
			newRot.setCross( mForward, mUp );
			mForward.setCross( mUp, newRot );

			// Display character's current heading
			hkRotation characterRotation;
			characterRotation.set( mCharacterRigidBody->getRigidBody()->getRotation() );
			HK_DISPLAY_ARROW( mCharacterRigidBody->getPosition(), characterRotation.getColumn(0), hkColor::LIMEGREEN );

			input.m_forward = mForward;
		}

		hkStepInfo stepInfo;
		stepInfo.m_deltaTime = mTimeStep;
		stepInfo.m_invDeltaTime = 1.0f / mTimeStep;

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
		mCharacterRigidBody->setLinearVelocity( output.m_velocity, mTimeStep );

		HK_TIMER_END();		
	}

	mPhysicsWorld->unmarkForWrite();

	// Rotate the character
	{
		hkRotation newOrientation;
		newOrientation.getColumn(0) = mCharacterForward;
		newOrientation.getColumn(1) = mUp;
		newOrientation.getColumn(2).setCross( newOrientation.getColumn(0), newOrientation.getColumn(1) );
		newOrientation.renormalize();
		
		reorientCharacter( newOrientation );
	}	*/
}

hkBool HoverCraftCharacter::reorientCharacter( const hkRotation& rotation )
{
/*	const hkReal gain = 0.5f;

	const hkQuaternion& currentOrient = mCharacterRigidBody->getRigidBody()->getRotation();

	hkQuaternion desiredOrient;
	desiredOrient.set( rotation );

	hkVector4 angle;
	hkVector4 angularVelocity;
	currentOrient.estimateAngleTo( desiredOrient, angle );
	angularVelocity.setMul4( gain * 60.0f, angle );

	mCharacterRigidBody->getRigidBody()->markForWrite();
	mCharacterRigidBody->setAngularVelocity( angularVelocity );
	mCharacterRigidBody->getRigidBody()->unmarkForWrite();
*/
	return true;
}

}
