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

	/**
	 * A vector of what the character sees as up vector	
	 */
	hkVector4 mUp;

	hkVector4 mForward;

	

public:



	/**
	 * Constructor
	 * @param info
	 * @param characterContext
	 * @param controllor
	 */
	Character( hkpWorld * world, const char * name, hkpCharacterRigidBodyCinfo * info,  hkpCharacterContext * characterContext);

	/**
	 * Destructor
	 */
	virtual ~Character();

	/**
	 * Get forward vector
	 * @return forward
	 */
	const hkVector4& getForward() const {
		return mForward;
	}

	/**
	 * Get forward vector
	 * @return forward
	 */
	hkVector4& getForward(){
		return mForward;
	}

	/**
	 * Get the rigid body for the character
	 */
	hkpCharacterRigidBody * getCharacterRigidBody() {
		return mCharacterRigidBody;
	}

	void reorientCharacter();

	void updateUp( hkVector4& newUp );
	
	/**
	 * Update the character movement
	 */
	void update();

	
};

}

#endif