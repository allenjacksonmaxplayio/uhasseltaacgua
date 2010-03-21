#ifndef HAVOKHOVERCRAFT_H
#define HAVOKHOVERCRAFT_H

#include "HavokEntity.h"

namespace HovUni {

class Hovercraft;

class HavokHovercraft : public HavokEntity
{
private:

	/**
	 * The filename from which the hovercraft physic should be read
	 */
	hkString mFilename;

	hkString mEntityName;

protected:

	virtual void loadCharacter(const hkVector4& position);

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