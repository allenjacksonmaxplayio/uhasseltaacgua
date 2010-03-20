#ifndef HAVOKHOVERCRAFT_H
#define HAVOKHOVERCRAFT_H

#include "HavokEntity.h"

namespace HovUni {

class Hovercraft;

class HavokHovercraft : public HavokEntity
{
public:
	HavokHovercraft(hkpWorld * world, Hovercraft * entity, hkpCharacterRigidBodyCinfo * info,  hkpCharacterContext * characterContext);

	~HavokHovercraft(void);

	/**
	 * Update the character based on movement
	 */
	virtual void preStep();

	/**
	 * Reorient character
	 */
	virtual void postStep();
};

}

#endif