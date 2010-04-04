//Havok
#include <Common/Base/hkBase.h>
#include <Common/Base/System/hkBaseSystem.h>


#include "BoostAction.h"

#include "HavokEntity.h"
#include "Entity.h"
#include "Hovercraft.h"

namespace HovUni {

BoostAction::BoostAction(const hkVector4& boost, hkReal gain, HavokEntity * entity):
	hkpUnaryAction(entity->getRigidBody()), mBoost(boost), mGain(gain)
{
}

BoostAction::~BoostAction(void)
{
}

void BoostAction::applyAction( const hkStepInfo& stepInfo ){
	//if some boost left
	if ( mBoost.lengthSquared3() > 10e-3 ){
/*
		getRigidBody()->applyForce(stepInfo.m_deltaTime,mBoost);
		//getRigidBody()->applyLinearImpulse(mBoost);

		if ( mEntity->isBoosted() ){
			//if in boost GOOOOO
			boostvalue += boostvalue/4.0f;
		}
		else {
			//else slow down
			boostvalue -= boostvalue/10.0f;
		}*/
	}
}

}
