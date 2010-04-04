#include "HavokHovercraft.h"
#include "Havok.h"
#include "HavokEntityType.h"

#include <Common/Base/Types/Color/hkColor.h>
#include <Common/Visualize/hkDebugDisplay.h>

#include <Physics/Dynamics/Entity/hkpRigidBody.h>
#include <Physics/Utilities/CharacterControl/CharacterRigidBody/hkpCharacterRigidBodyListener.h>
#include <Physics/Collide/Shape/Convex/Sphere/hkpSphereShape.h>
#include <Physics/Utilities/CharacterControl/CharacterRigidBody/hkpCharacterRigidBodyCinfo.h>


#include <Common/Base/System/Error/hkDefaultError.h>
#include <Common/Base/Monitor/hkMonitorStream.h>
#include <Common/Base/System/Io/IStream/hkIStream.h>


#include "Hovercraft.h"
#include "DedicatedServer.h"


namespace HovUni {

std::ostream& operator<<(std::ostream& stream, const hkVector4& v) {
	return stream << "hkVector4(" << v.getSimdAt(0) << ", " << v.getSimdAt(1) << ", " << v.getSimdAt(2) << ", " << "w=" << v.getSimdAt(3) << ")";
}

HavokHovercraft::HavokHovercraft(hkpWorld * world, Hovercraft * entity, const hkString& filename, const hkString& entityname):
		HavokEntity(world), mEntity(entity), mFilename(filename), mEntityName(entityname), mCharacterRigidBody(HK_NULL),
		mUp(HavokEntity::UP), mSide(HavokEntity::FORWARD), mCharacterContext(HK_NULL),
		mRotationDelta(DedicatedServer::getEngineSettings()->getFloatValue("Movement", "TurnAngle")),
		mSpeedDamping(DedicatedServer::getEngineSettings()->getFloatValue("Movement", "Damping")),
		mCharacterGravity(DedicatedServer::getEngineSettings()->getFloatValue("Havok", "CharacterGravity"))
		
{
}

HavokHovercraft::~HavokHovercraft(void)
{
	mCharacterRigidBody->removeReference();
	mCharacterRigidBody = HK_NULL;

	mCharacterContext->removeReference();
	mCharacterContext = HK_NULL;

	mPhysicsData->removeReference();
	mPhysicsData = HK_NULL;
	
	//TODO look at this memory leak thing
	mLoadedData->disableDestructors();
	mLoadedData->callDestructors();
	mLoadedData->removeReference();

}

const hkVector4& HavokHovercraft::getPosition() const {
	return mCharacterRigidBody->getPosition();
}

const hkVector4& HavokHovercraft::getVelocity() const {
	return mCharacterRigidBody->getLinearVelocity();
}

const hkQuaternion& HavokHovercraft::getOrientation() const {
	return mCharacterRigidBody->getRigidBody()->getRotation();
}

Entity * HavokHovercraft::getEntity() {
	return mEntity;
}

hkpRigidBody * HavokHovercraft::getRigidBody() const {
	return mCharacterRigidBody->getRigidBody();
}

void HavokHovercraft::updateUp( const hkVector4& newUp ) {
	mUp = newUp;
}

void HavokHovercraft::update(){
	//PRE STEP
	mWorld->markForWrite();

	//Update SIDE with new UP
	hkRotation rbRotation; rbRotation.set(mCharacterRigidBody->getRigidBody()->getRotation());
	hkVector4& oldForward = rbRotation.getColumn(0);
	hkVector4 newRot;
	newRot.setCross(oldForward, mUp);
	mSide.setCross(mUp, newRot);
	mSide.normalize3();
	mForward.setCross(mSide,mUp);
	
	// Update the character context
	mCharacterRigidBody->m_up = mUp;
	

	//Get the hovercraft and input
	Hovercraft * hovercraft = dynamic_cast<Hovercraft *>(mEntity);
	const BasicEntityEvent& status = hovercraft->getMovingStatus();
	hkReal speed = hovercraft->getSpeed();


	//Speed on a scale [0-1]
	float scaledspeed = 0.f;

	//speeding
	if (status.moveForward()) {	

		speed += hovercraft->getAcceleration() * Havok::getSingleton().getTimeStep() * 20;
		
		if (speed > hovercraft->getMaximumSpeed()) {
			speed = hovercraft->getMaximumSpeed();
		}
		
	}

	//braking..
	if (status.moveBackward()) {
		
		if (speed > 0.0f) {
			// braking should be harder than moving backwards
			speed -= hovercraft->getAcceleration() * Havok::getSingleton().getTimeStep() * 20;
		} else {
			speed -= hovercraft->getAcceleration() * Havok::getSingleton().getTimeStep() * 10;
		}
		
		if (speed < -1 * hovercraft->getMaximumSpeed()) {
			speed = -1 * hovercraft->getMaximumSpeed();
		}
		
	}

	// slow down when idle
	if (!status.moveBackward() && !status.moveForward()) {
		speed *= mSpeedDamping;
		if ((speed < 1.0f) && (speed > -1.0f)) {
			speed = 0.0f;
		}
	}

	hovercraft->setSpeed(speed);

	
	//rotations
	if (status.moveLeft() || status.moveRight()) {

		// we can only turn while we're moving
		if ((hovercraft->getSpeed() > 1.0f) || (hovercraft->getSpeed() < -1.0f)) {
			float angle = mCharacterRigidBody->getRigidBody()->getRotation().getAngle();
			if (angle != 0.0f) {
				hkVector4 axis = mUp;
				hkVector4 crossProduct;
				crossProduct.setCross(mUp, mSide);

				if (crossProduct(1) < 0) {
					angle = angle * -1;
				}
			}

			if (status.moveLeft()) {
				if (speed > 0.0f) {
					angle = mRotationDelta;
				} else if (speed < 0.0f) {
					angle = -mRotationDelta;
				}
			}
			if (status.moveRight()) {
				if (speed > 0.0f) {
					angle = -mRotationDelta;
				} else if (speed < 0.0f) {
					angle = mRotationDelta;
				}
			}


			hkQuaternion q(mUp,angle);
			mSide.setRotatedDir(q, mSide);
			mSide.normalize3();
		}
	}

	scaledspeed = speed / Hovercraft::MAXSPEED; 
	/*
	if (status.moveForward()) {
		scaledspeed = 1000.0f;
	} else if (status.moveBackward()) {
		scaledspeed = -1000.0f;
	} else {
		scaledspeed = 0.0f;
	}
	*/

	hkStepInfo stepInfo;
	stepInfo.m_deltaTime = Havok::getSingleton().getTimeStep();
	stepInfo.m_invDeltaTime = 1.0f / Havok::getSingleton().getTimeStep();

	hkpCharacterInput input;
	hkpCharacterOutput output;
	{
		HK_TIMER_BEGIN("set character state", HK_NULL);

		input.m_atLadder = false;
		input.m_inputLR = 0;
		input.m_inputUD = scaledspeed;
		input.m_wantJump = false;

		input.m_up = mUp;
		input.m_forward = mForward;
		input.m_stepInfo = stepInfo;
		input.m_characterGravity.setMul4(-mCharacterGravity, mUp);
		input.m_velocity = mCharacterRigidBody->getRigidBody()->getLinearVelocity();
		input.m_position = mCharacterRigidBody->getRigidBody()->getPosition();
		mCharacterRigidBody->checkSupport(stepInfo, input.m_surfaceInfo);

		HK_TIMER_END();
	}

	// Apply the character state machine
	{
		HK_TIMER_BEGIN("update character state", HK_NULL);
		mCharacterContext->update(input, output);
		HK_TIMER_END();
	}

	//Apply the player character controller
	{
		HK_TIMER_BEGIN("simulate character", HK_NULL);
		// Set output velocity from state machine into character rigid body
		mCharacterRigidBody->setLinearVelocity(output.m_velocity, Havok::getSingleton().getTimeStep());
		HK_TIMER_END();
	}

	//POST STEP
	hkRotation newOrientation;
	newOrientation.getColumn(0) = mSide;
	newOrientation.getColumn(1) = mUp;
	newOrientation.getColumn(2).setCross(mSide, mUp);
	newOrientation.renormalize();
	HK_DISPLAY_ARROW(mCharacterRigidBody->getPosition(), mForward, hkColor::BLUE);
	HK_DISPLAY_ARROW(mCharacterRigidBody->getPosition(), mUp, hkColor::RED);

	const hkReal gain = 0.25f;
	const hkQuaternion& currentOrient = mCharacterRigidBody->getRigidBody()->getRotation();
	hkQuaternion desiredOrient;
	desiredOrient.set(newOrientation);
	hkVector4 angle;
	hkVector4 angularVelocity;
	currentOrient.estimateAngleTo(desiredOrient, angle);
	angularVelocity.setMul4(gain / Havok::getSingleton().getTimeStep(), angle);
	mCharacterRigidBody->setAngularVelocity(angularVelocity);

	hkVector4 newSpeed = output.m_velocity;
	hkSimdReal speedSize = -newSpeed.dot3(mForward)/mForward.dot3(mForward);
	//hovercraft->setSpeed(speedSize);
	//std::cout << scaledspeed << "  " << speed << "  " << speedSize << std::endl;
	


	//if some boost left
	float boostvalue = mEntity->getBoost();
	if ( fabs(boostvalue) > 10e-3 ){
		hkVector4 boost = mForward;
		boost.mul4(-1*boostvalue);
		getRigidBody()->applyLinearImpulse(boost);
		boostvalue -= boostvalue/10.0f;

		if ( mEntity->isBoosted() ){
			//if in boost GOOOOO
			boostvalue += boostvalue/4.0f;
		}
		else {
			//else slow down
			boostvalue -= boostvalue/10.0f;
		}

		mEntity->setBoost(boostvalue);
	}

	mWorld->unmarkForWrite();
}


void HavokHovercraft::load(const hkVector4& position){
	mWorld->markForWrite();

	//Hovercrafts right
	Hovercraft * hovercraft = dynamic_cast<Hovercraft*>(mEntity);

	//load the hovercraft hull from file

	hkIstream infile( mFilename.cString() );
	HK_ASSERT( 0x215d080c, infile.isOk() );

	/**
	 * The world in memory as loaded from file
	 */
	mPhysicsData = hkpHavokSnapshot::load( infile.getStreamReader(), &mLoadedData );
	HK_ASSERT( 0, mPhysicsData != HK_NULL );

	hkpRigidBody * body = mPhysicsData->findRigidBodyByName( mEntityName.cString() );
	HK_ASSERT( 0x215d080c, body != HK_NULL );

	const hkpShape * shape = body->getCollidable()->getShape();
	shape->addReference();

	//create a temporart shape
	hkpShape * tmp = new hkpSphereShape (5);

	//set up its parameters
	hkpCharacterRigidBodyCinfo info;
	info.m_mass = hovercraft->getMass();
	info.m_shape = tmp;
	info.m_maxLinearVelocity = Hovercraft::MAXSPEED;
	info.m_maxForce = 1000.0f;
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
	mWorld->addEntity( charbody );

	//Remove some data
	tmp->removeReference();

	hkAabb aabb ( hkVector4(0,0,0),hkVector4(5,5,5));
	addCollisionPrevention(aabb, 20);

	mWorld->unmarkForWrite();
}

}