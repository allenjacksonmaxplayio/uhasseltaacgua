#ifndef BOOSTPROPERTY_H
#define BOOSTPROPERTY_H

#include "EntityPropertySystem.h"
#include <OgreVector3.h>

namespace HovUni {

/**
 * Boost property
 */
class BoostProperty: public EntityProperty
{
private:

	static EntityPropertyTag<BoostProperty,1> tag;

	Ogre::Real mBoost;

	Ogre::Real mGain;

	Ogre::Vector3 mDirection;

public:

	BoostProperty();

	BoostProperty(int id);

	virtual ~BoostProperty(void);

	/**
	 * Set the boost
	 *
	 * @param boost
	 */
	void setBoost( Ogre::Real boost ){
		mBoost = boost;
		update();
	}

	/**
	 * Set the gain
	 *
	 * @param gain
	 */
	void setGain( Ogre::Real gain ){
		mGain = gain;
		update();
	}

	/**
	 * @see EntityProperty
	 */
	virtual void write(ZCom_BitStream& bitstream) const;

	/**
	 * @see EntityProperty
	 */
	virtual void read(ZCom_BitStream& bitstream);
};

}

#endif
