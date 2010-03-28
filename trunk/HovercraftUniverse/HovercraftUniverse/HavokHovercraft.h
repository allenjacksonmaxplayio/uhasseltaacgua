#ifndef HAVOKHOVERCRAFT_H
#define HAVOKHOVERCRAFT_H

#include "HavokEntity.h"
#include <Physics/Utilities/CharacterControl/CharacterRigidBody/hkpCharacterRigidBody.h>
#include <Physics/Utilities/CharacterControl/StateMachine/hkpDefaultCharacterStates.h>
#include <Physics/Utilities/Serialize/hkpHavokSnapshot.h>

namespace HovUni {

class Hovercraft;

class HavokHovercraft : public HavokEntity
{
private:

	hkPackfileReader::AllocatedData* mLoadedData;

	hkpPhysicsData * mPhysicsData;

	/**
	 * The filename from which the hovercraft physic should be read
	 */
	hkString mFilename;

	hkString mEntityName;

	hkpWorld * mWorld;

	Hovercraft * mEntity;
	
 	hkpCharacterRigidBody* mCharacterRigidBody;

	hkpCharacterContext * mCharacterContext;

	// Current world vectors. This changes as the simulation progresses.
 	hkVector4 mUp;
 	hkVector4 mSide;
	hkVector4 mForward;	

public:

	/**
	 * Constructor
	 * @paam world
	 * @param entity
	 * @param filename
	 */
	HavokHovercraft(hkpWorld * world, Hovercraft * entity, const hkString& filename, const hkString& entityname );

	~HavokHovercraft(void);

	/**
	 * Load the hovercraft at given position
	 */
	virtual void load(const hkVector4& position);

	/**
	 * Get the position of the character
	 * @return the position of the character
	 */
	virtual const hkVector4& getPosition() const;

	/**
	* Get the linear velocity of the character (Dirk, 24/03/2010)
	* @reurn the linear velocity of the character
	*/
	virtual const hkVector4& getVelocity() const;

	/**
	 * Get the orientation of the character
	 * @return the orientation of the character
	 */
	virtual const hkQuaternion& getOrientation() const;

	/**
	 * Get the entity
	 * @return entity
	 */
	virtual Entity * getEntity();

	/**
	 * Update the character based on movement
	 */
	virtual void update();

	/**
	 * Update the up vector
	 * @param up vector
	 */
	virtual void updateUp( const hkVector4& newUp);

};



}

#endif