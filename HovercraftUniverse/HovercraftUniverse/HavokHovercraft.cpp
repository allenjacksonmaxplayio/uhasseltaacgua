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

std::ostream& operator<<(std::ostream& stream, const hkVector4& v) {
	return stream << "hkVector4(" << v.getSimdAt(0) << ", " << v.getSimdAt(1) << ", " << v.getSimdAt(2) << ", " << "w=" << v.getSimdAt(3) << ")";
}

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
	hkPackfileReader::AllocatedData* LoadedData;

	hkpPhysicsData * PhysicsData = hkpHavokSnapshot::load( infile.getStreamReader(), &LoadedData );
	HK_ASSERT( 0, PhysicsData != HK_NULL );

	hkpRigidBody * body = PhysicsData->findRigidBodyByName( mEntityName.cString() );
	HK_ASSERT( 0x215d080c, body != HK_NULL );

	const hkpShape * shape = body->getCollidable()->getShape();
	shape->addReference();

	//create a temporart shape
	hkpShape * tmp = new hkpSphereShape (5);

	//set up its parameters
	hkpCharacterRigidBodyCinfo info;
	info.m_mass = hovercraft->getMass();
	info.m_shape = tmp;
	info.m_maxLinearVelocity = 500;//Hovercraft::MAXSPEED;
	info.m_maxForce = 800.0f;	//TODO dunno
	info.m_position = position;
	info.m_maxSlope = 45.0f * HK_REAL_DEG_TO_RAD;
	info.m_friction = 0.1f;
	info.m_rotation = hkQuaternion::getIdentity();
	
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

	//set the loaded shape here
	charbody->setShape(shape);

	//set name and type
	charbody->setUserData(reinterpret_cast<hkUlong>(this));
	HavokEntityType::setEntityType(charbody,HavokEntityType::CHARACTER);
	mPhysicsWorld->addEntity( charbody );

	//Remove some data
	tmp->removeReference();


	//PhysicsData->removeReference();
	//LoadedData->removeReference();


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
	if ( status.moveBackward() || !status.moveForward() ){

		speed -= hovercraft->getAcceleration() * Havok::getSingleton().getTimeStep();
		
		if ( !status.moveBackward() && !status.moveForward() && (speed < 0.0f) ){
			speed = 0.0f;
		}

		if ( speed < -1 * hovercraft->getMaximumSpeed() ){
			hovercraft->setSpeed(-1 * hovercraft->getMaximumSpeed());
		} else {
			hovercraft->setSpeed(speed);
		}
	}

	posX = speed / Hovercraft::MAXSPEED; 

	


	//std::cout << "MAX " << Hovercraft::MAXSPEED << std::endl;
	//std::cout << "HOV-MAX " << hovercraft->getMaximumSpeed() << std::endl;
	//std::cout << "HOV-SPEED " << hovercraft->getSpeed() << " " << posX << std::endl;
	if (status.moveLeft() || status.moveRight()) {
		//Rotation
		double epsilon = 0.001;
		double delta = 0.01;
		const double PI = 3.1415926535;

		float angle = mCharacterRigidBody->getRigidBody()->getRotation().getAngle();
		if (angle != 0.0f) {
			hkVector4 axis;
			mCharacterRigidBody->getRigidBody()->getRotation().getAxis(axis);
			//angle = angle * axis(1); //Multiply by y-component of  rotation axis, to get the sign for the angel
			//TODO I assume this only works with a rotation axis that points straight up, so this is basically a 2D solution. (Dirk)
			//Tobias may fix this :)
			//std::cout << "Axis = " << axis << std::endl;

			hkVector4 crossProduct;
			crossProduct.setCross( hkVector4(1,0,0,0), mForward );

			if ( crossProduct(1) < 0 ){
				angle = angle * -1;
			}

		}

		if ( status.moveLeft() ){
			angle = angle + delta;
			hkQuaternion q(mUp,angle);
			mForward.setRotatedDir(q,hkVector4(1,0,0,0));
			mForward.normalize3();
		}
		if ( status.moveRight() ){
			angle = angle - delta;	
			hkQuaternion q(mUp,angle);
			mForward.setRotatedDir(q,hkVector4(1,0,0,0));
			mForward.normalize3();

		}

		//std::cout << "UP = " << mUp << std::endl;
		//std::cout << "FORWARD = " << mForward << std::endl;
	}



	hkRotation characterRotation;
	characterRotation.set( mCharacterRigidBody->getRigidBody()->getRotation() );

	HK_DISPLAY_ARROW( mCharacterRigidBody->getPosition(), mForward, hkColor::PALEGOLDENROD );
	HK_DISPLAY_ARROW( mCharacterRigidBody->getPosition(), characterRotation.getColumn(0), hkColor::BLUE );
	HK_DISPLAY_ARROW( mCharacterRigidBody->getPosition(), characterRotation.getColumn(1), hkColor::RED );
	HK_DISPLAY_ARROW( mCharacterRigidBody->getPosition(), characterRotation.getColumn(2), hkColor::AQUAMARINE );
	
	// Update the character context
	mCharacterRigidBody->m_up = mUp;

	
	hkpCharacterInput input;
	hkpCharacterOutput output;
	{
		HK_TIMER_BEGIN( "set character state", HK_NULL );

		input.m_atLadder = false;
		input.m_inputLR = posX;
		input.m_inputUD = posY;
		input.m_wantJump = false;

		input.m_up = mUp;
		input.m_forward = mForward;
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

	mPhysicsWorld->unmarkForWrite();
}

}