#include "HavokHovercraft.h"
#include "Havok.h"
#include "HavokEntityType.h"

#include <Common/Base/Types/Color/hkColor.h>
#include <Common/Visualize/hkDebugDisplay.h>

#include <Physics/Dynamics/Entity/hkpRigidBody.h>
#include <Physics/Utilities/CharacterControl/CharacterRigidBody/hkpCharacterRigidBodyListener.h>
#include <Physics/Collide/Shape/Convex/Sphere/hkpSphereShape.h>
#include <Physics/Utilities/CharacterControl/CharacterRigidBody/hkpCharacterRigidBodyCinfo.h>

#include <Physics/Utilities/Serialize/hkpHavokSnapshot.h>
#include <Common/Base/System/Error/hkDefaultError.h>
#include <Common/Base/Monitor/hkMonitorStream.h>
#include <Common/Base/System/Io/IStream/hkIStream.h>


#include "Hovercraft.h"



namespace HovUni {

HavokHovercraft::HavokHovercraft(hkpWorld * world, Hovercraft * entity, const hkString& filename, const hkString& entityname):
	HavokEntity( world, entity), mFilename(filename), mEntityName(entityname)
{
}

HavokHovercraft::~HavokHovercraft(void)
{
}

void HavokHovercraft::loadCharacter(const hkVector4& position){
	mPhysicsWorld->markForWrite();

	//Hovercrafts right
	Hovercraft * hovercraft = dynamic_cast<Hovercraft*>(mEntity);

	//load the hovercraft hull from file

	hkIstream infile( mFilename.cString() );
	HK_ASSERT( 0x215d080c, infile.isOk() );

	/**
	 * The world in memory as loaded from file
	 */
	hkPackfileReader::AllocatedData* mLoadedData;

	hkpPhysicsData * mPhysicsData = hkpHavokSnapshot::load( infile.getStreamReader(), &mLoadedData );
	HK_ASSERT( 0, mPhysicsData != HK_NULL );

	hkpRigidBody * body = mPhysicsData->findRigidBodyByName( mEntityName.cString() );
	HK_ASSERT( 0x215d080c, body != HK_NULL );

	const hkpShape * shape = body->getCollidable()->getShape();
	shape->addReference();

	//mPhysicsData->removeReference();
	//mLoadedData->removeReference();


	hkpShape * tmp = new hkpSphereShape (5);

	//set up its parameters
	hkpCharacterRigidBodyCinfo info;
	info.m_mass = hovercraft->getMass();
	info.m_shape = tmp;
	info.m_maxLinearVelocity = hovercraft->getMaximumSpeed();	//TODO should this be Hovercraft::MAXSPEED??
	info.m_maxForce = 8000.0f;	//TODO dunno
	info.m_position = position;
	info.m_maxSlope = 45.0f * HK_REAL_DEG_TO_RAD;
	info.m_friction = 0.1f;
	
	//set up the actions
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
	mCharacterContext->setCharacterType( hkpCharacterContext::HK_CHARACTER_RIGIDBODY );

	//Create a character rigid body
	mCharacterRigidBody = new hkpCharacterRigidBody( info );
	hkpCharacterRigidBodyListener* listener = new hkpCharacterRigidBodyListener();
	mCharacterRigidBody->setListener( listener );

	listener->removeReference();		
	hkpRigidBody * charbody = mCharacterRigidBody->getRigidBody();

	charbody->setShape(shape);
	tmp->removeReference();

	//set name and type
	charbody->setUserData(reinterpret_cast<hkUlong>(this));
	HavokEntityType::setEntityType(charbody,HavokEntityType::CHARACTER);

	mPhysicsWorld->addEntity( charbody );
	mPhysicsWorld->unmarkForWrite();
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
		posX += 1.f;
		//ROTATE

	}
	if ( status.moveRight() ){
		posX -= 1.f;
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