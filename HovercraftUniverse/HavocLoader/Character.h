#ifndef CHARACTER_H
#define CHARACTER_H

#include <Physics/Utilities/CharacterControl/CharacterRigidBody/hkpCharacterRigidBody.h>
#include "CharacterContextContainer.h"

namespace HovUni {

/**
 * A character
 */
class Character {
protected:

	hkpWorld * mPhysicsWorld;
	
	/**
	 * A charater rigid body
	 */
	hkpCharacterRigidBody * mCharacterRigidBody;

	/**
	 * The context of the character
	 */
	hkpCharacterContext * mCharacterContext;

public:

	/**
	 * A vector of what the character sees as up vector	
	 */
	hkVector4 mUp;

	hkVector4 mCharacterForward;

	hkVector4 mForward;

	hkReal mTimeStep;

	/**
	 * Constructor
	 */
	Character( hkpWorld * mPhysicsWorld, hkpCharacterRigidBodyCinfo * info, const char * charactertype );

	/**
	 * Destructor
	 */
	virtual ~Character();

	/**
	 * Get the rigid body for the character
	 */
	hkpCharacterRigidBody * getCharacterRigidBody() {
		return mCharacterRigidBody;
	}
	
	/**
	 * Update the character movement
	 */
	void update(hkReal deltaAngle, hkReal posX, hkReal posY);

	hkBool reorientCharacter( const hkRotation& rotation );
};

}

#endif