#ifndef CHARACTER_H
#define CHARACTER_H

#include <Physics/Utilities/CharacterControl/CharacterRigidBody/hkpCharacterRigidBody.h>
#include <Physics/Utilities/CharacterControl/StateMachine/hkpDefaultCharacterStates.h>
#include "Controller.h"

namespace HovUni {

/**
 * A character
 */
class Character {
protected:

	/**
	 * Refernce to world
	 */
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

	/**
	 * Constructor
	 * @param info
	 * @param characterContext
	 * @param controllor
	 */
	Character( hkpWorld * world, hkpCharacterRigidBodyCinfo * info,  hkpCharacterContext * characterContext);

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
	virtual void update();
};

}

#endif