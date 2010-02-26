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

public:

	/**
	 * A vector of what the character sees as up vector	
	 */
	hkVector4 mUp;

	/**
	 * Constructor
	 */
	Character( hkpWorld * mPhysicsWorld, hkpCharacterRigidBodyCinfo * info );

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
};

}

#endif