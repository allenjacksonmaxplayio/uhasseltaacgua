#ifndef BOOSTACTION_H
#define BOOSTACTION_H

#include <Physics/Dynamics/Action/hkpUnaryAction.h>

namespace HovUni {

class HavokEntity;

/**
 * This action will be triggered when boost is triggered.
 * @author Pieter-Jan Pintens
 */
class BoostAction : hkpUnaryAction
{
private:

	/**
	 * The current boost
	 */
	hkVector4 mBoost;

	/**
	 * The boost gain for each update
	 */
	hkReal mGain;

	/**
	 * The entity this boost works on
	 */
	HavokEntity * mEntity;

public:

	/**
	 * Constructor
	 *
	 * @param boost, the initial boost vector
	 * @param gain, the boost gain for each update 
	 * @param entity, the entity on which the boost works
	 */
	BoostAction( const hkVector4& boost, hkReal gain, HavokEntity * entity );

	~BoostAction(void);

private:

	virtual void applyAction( const hkStepInfo& stepInfo );

	virtual hkpAction* clone( const hkArray<hkpEntity*>& newEntities, const hkArray<hkpPhantom*>& newPhantoms ) const { 
		return HK_NULL; 
	}
};

}

#endif
