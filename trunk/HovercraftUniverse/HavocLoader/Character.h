#ifndef CHARACTER_H
#define CHARACTER_H

#include <Physics/Utilities/CharacterControl/CharacterRigidBody/hkpCharacterRigidBody.h>
#include <Physics/Utilities/CharacterControl/StateMachine/hkpDefaultCharacterStates.h>

namespace HovUni {

/**
 * A character
 */
class Character {
protected:

	hkpWorld * mPhysicsWorld;
	
	/**
	 * A vector of what the character sees as up vector	
	 */
	hkVector4 mUp;

	/**
	 * A charater rigid body
	 */
	hkpCharacterRigidBody * mCharacterRigidBody;

	/**
	 * A character context
	 */
	static hkpCharacterContext * mCharacterContext; 

public:

	/**
	 * Constructor
	 */
	Character( hkpWorld * mPhysicsWorld, hkVector4 startpos, hkQuaternion rotation );

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
	 * Set new up vector for the character
	 * @param up
	 */
	inline hkVector4& getUp(){
		return mUp;
	}

	/**
	 * Set new up vector for the character
	 * @param up
	 */
	inline void setUp( hkVector4 up ){
		mUp = up;
	}

};

}

#endif