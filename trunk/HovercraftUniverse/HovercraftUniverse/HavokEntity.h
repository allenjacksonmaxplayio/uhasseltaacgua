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

protected:

	/**
	 * Load the character, this method must set up the rigid body and character context
	 * @param position
	 */
	virtual void loadCharacter(const hkVector4& position) = 0;

public:

	/**
	 * Constructor
	 * @param world
	 * @param entity
	 */
	HavokEntity( hkpWorld * world, Entity * entity);

	/**
	 * Load the character, must be called before the character is used
	 * @param position
	 */
	void load(const hkVector4& position);

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
	* Get the linear velocity of the character (Dirk, 24/03/2010)
	* @reurn the linear velocity of the character
	*/
	const hkVector4& getVelocity() const;

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
	 * Update the up vector
	 * @param up vector
	 */
	virtual void updateUp( const hkVector4& newUp);

	/**
	 * Action te be done in the preStep
	 */
	virtual void preStep(){};

	/**
	 * Action to be done in the post step
	 */
	virtual void postStep(){};

		
	
};

}

#endif