#ifndef HAVOKENTITY_H
#define HAVOKENTITY_H

#include <Common/Base/hkBase.h>


namespace HovUni {

class Entity;

/**
 * A character
 */
class HavokEntity {

public:

	static const hkVector4 UP;

	static const hkVector4 FORWARD;

	/**
	 * Constructor
	 * @param world
	 * @param entity
	 */
	HavokEntity();

	/**
	 * Destructor
	 */
	virtual ~HavokEntity();

	/**
	 * Load the character, must be called before the character is used
	 * @param position
	 */
	virtual void load(const hkVector4& position) = 0;

	/**
	 * Get the position of the character
	 * @return the position of the character
	 */
	virtual const hkVector4& getPosition() const = 0;

	/**
	* Get the linear velocity of the character (Dirk, 24/03/2010)
	* @reurn the linear velocity of the character
	*/
	virtual const hkVector4& getVelocity() const = 0;

	/**
	 * Get the orientation of the character
	 * @return the orientation of the character
	 */
	virtual const hkQuaternion& getOrientation() const = 0;

	/**
	 * Get the entity
	 * @return entity
	 */
	virtual Entity * getEntity() = 0;

	/**
	 * Update the character based on movement
	 */
	virtual void update() = 0;

	/**
	 * Update the up vector
	 * @param up vector
	 */
	virtual void updateUp( const hkVector4& newUp) = 0;
	
};

}

#endif