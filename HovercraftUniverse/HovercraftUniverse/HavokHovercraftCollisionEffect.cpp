#include "HavokHovercraftCollisionEffect.h"

#include "HavokHovercraft.h"
#include <Physics/Dynamics/Entity/hkpRigidBody.h>

#include "Hovercraft.h"
#include "HavokEntityType.h"
#include <iostream>

#include "CollisionEvent.h"

namespace HovUni {

HovercraftCollisionListener::HovercraftCollisionListener(HavokHovercraftCollisionEffect * collisionEffect):
	mCollisionEffect(collisionEffect)
{	
}

void  HovercraftCollisionListener::contactPointAddedCallback (hkpContactPointAddedEvent &e){
} 

void  HovercraftCollisionListener::contactPointConfirmedCallback (hkpContactPointConfirmedEvent &e){
}
 
void  HovercraftCollisionListener::contactPointRemovedCallback (hkpContactPointRemovedEvent &e){
} 
 
void  HovercraftCollisionListener::contactProcessCallback (hkpContactProcessEvent &e){
	hkpProcessCollisionData * collisiodata = e.m_collisionData;

	const hkpCollidable * other = e.m_collidableA == mCollisionEffect->mHovercraft->getRigidBody()->getCollidable() ? e.m_collidableB : e.m_collidableA;

	hkpWorldObject * object = static_cast<hkpWorldObject*>(other->getOwner());

	if ( !HavokEntityType::isEntityType(object,HavokEntityType::PLANET) ){
		if ( collisiodata->getNumContactPoints () != 0 ){
			mCollisionEffect->mBounceVector.setZero4();

			Ogre::Vector3 pos;
			Ogre::Vector3 nor;

			for ( int i = 0; i < collisiodata->getNumContactPoints (); i++ ){
				hkpProcessCdPoint & point =  collisiodata->getContactPoint (i);
				mCollisionEffect->mBounceVector.add4(point.m_contact.getNormal());

				const hkVector4& havpos = point.m_contact.getPosition();
				pos[0] += havpos(0);
				pos[1] += havpos(1);
				pos[2] += havpos(2);
			}

			pos /= collisiodata->getNumContactPoints();
			nor[0] = mCollisionEffect->mBounceVector(0);
			nor[1] = mCollisionEffect->mBounceVector(1);
			nor[2] = mCollisionEffect->mBounceVector(2);

			//send collision event!
			mCollisionEffect->mHovercraft->getEntity()->sendEvent(CollisionEvent(pos,nor));

			mCollisionEffect->mBounceVector.mul4( -1.0f * ((Hovercraft*)mCollisionEffect->mHovercraft->getEntity())->getSpeed()/(hkReal) collisiodata->getNumContactPoints ());
			mCollisionEffect->mHasCollision= true;
		}
	}
}


HavokHovercraftCollisionEffect::HavokHovercraftCollisionEffect(HavokHovercraft * hovercraft):
	hkpUnaryAction(hovercraft->getRigidBody()), mHovercraft(hovercraft)
{
	mBounceVector.setZero4();
	mHasCollision = false;
	
	mListener = new HovercraftCollisionListener(this);
	mHovercraft->getRigidBody()->addCollisionListener(mListener);
}

HavokHovercraftCollisionEffect::~HavokHovercraftCollisionEffect(void)
{
	m_entity->removeCollisionListener(mListener);
	delete mListener;
}


void HavokHovercraftCollisionEffect::applyAction( const hkStepInfo& stepInfo ){
	if ( mHasCollision ){
		this->mHovercraft->getRigidBody()->applyLinearImpulse(mBounceVector);
		mBounceVector.setZero4();
		mHasCollision = false;
	}
}

}
