#include "UpdatePositionAction.h"
#include "StaticBody.h"

namespace HovUni {

UpdatePositionAction::UpdatePositionAction( hkpRigidBody * body, StaticBody * gamebody, hkReal delta ):
	hkpUnaryAction(body), mStaticBody(gamebody), mDelta(delta) {
	mPreviousPosition = body->getPosition();
	mPreviousOrientation = body->getRotation();

	update();	
}

UpdatePositionAction::~UpdatePositionAction(void){
}

void UpdatePositionAction::update(){
	hkpRigidBody* body = dynamic_cast<hkpRigidBody*>(m_entity);
	const hkVector4& position = body->getPosition();
	const hkQuaternion& quaternion = body->getRotation();
	
	mStaticBody->changePosition(Ogre::Vector3(position(0),position(1),position(2)));
	mStaticBody->changeOrientation( Ogre::Quaternion( quaternion(3), quaternion(0), quaternion(1), quaternion(2)));
}

void UpdatePositionAction::applyAction( const hkStepInfo& stepInfo ){
	//TODO check if realy needed
	//if ( !mPreviousPosition.equals3(position, delta) ){

	update();
}

}
