#ifndef HAVOKENTITY_H
#define HAVOKENTITY_H

#include <Physics/Utilities/CharacterControl/CharacterRigidBody/hkpCharacterRigidBody.h>
#include <Physics/Utilities/CharacterControl/StateMachine/hkpDefaultCharacterStates.h>


namespace HovUni {

class Entity;

/**
 * A character
 */
class HavokEntity {
protected:

	/**
	 * Entity
	 */
	Entity * mEntity;

	/**
	 * Reference to world
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

	/**
	 * A vector of what the character sees as forward vector	
	 */
	hkVector4 mForward;

	/**
	 * 
	 */

public:

	/**
	 * Constructor
	 * @param info
	 * @param characterContext
	 * @param controllor
	 */
	HavokEntity( hkpWorld * world, Entity * entity, hkpCharacterRigidBodyCinfo * info,  hkpCharacterContext * characterContext);

	/**
	 * Destructor
	 */
	virtual ~HavokEntity();

	/**
	 * Get the position of the character
	 * @return the position of the character
	 */
	const hkVector4& getPosition() const;

	/**
	 * Get the orientation of the character
	 * @return the orientation of the character
	 */
	const hkQuaternion& getOrientation() const;

	/**
	 * Get the entity
	 * @return entity
	 */
	Entity * getEntity();

	/**
	 * Get forward vector
	 * @return forward
	 */
	const hkVector4& getForward() const;

	/**
	 * Get forward vector
	 * @return forward
	 */
	hkVector4& getForward();

	/**
	 * Get the rigid body for the character
	 */
	hkpCharacterRigidBody * getCharacterRigidBody();

	/**
	 * Action te be done in the preStep
	 */
	virtual void preStep(){};

	/**
	 * Action to be done in the post step
	 */
	virtual void postStep(){};

	virtual void updateUp( hkVector4& newUp);		
	
};

}

#endif