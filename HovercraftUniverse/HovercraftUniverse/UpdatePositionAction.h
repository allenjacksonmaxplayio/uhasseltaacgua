#ifndef UPDATEPOSITIONACTION_H
#define UPDATEPOSITIONACTION_H

#include <Physics/Dynamics/Action/hkpUnaryAction.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>

namespace HovUni {

class StaticBody;

/**
 * This action will keep the position of a static body entity equal to the position of a havok rigid body
 * @author Pieter-Jan Pintens
 */
class UpdatePositionAction : public hkpUnaryAction
{
public:

	/**
	 * Constructor
	 */
	UpdatePositionAction( hkpRigidBody * body, StaticBody * gamebody, hkReal delta = 0.01f );

	~UpdatePositionAction(void);

private:

	hkReal mDelta;

	StaticBody * mStaticBody;

	hkVector4 mPreviousPosition;

	hkQuaternion mPreviousOrientation;

private:

	void update();

	virtual void applyAction( const hkStepInfo& stepInfo );

	virtual hkpAction* clone( const hkArray<hkpEntity*>& newEntities, const hkArray<hkpPhantom*>& newPhantoms ) const { 
		return HK_NULL; 
	}
};

}

#endif