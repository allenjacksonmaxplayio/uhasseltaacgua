#ifndef POWERUPPHANTOM_H
#define POWERUPPHANTOM_H

#include <Physics/Dynamics/Phantom/hkpAabbPhantom.h>

namespace HovUni {

/**
 * A phantom to check if a player has picked up a powerup
 * @author Pieter-Jan Pintens
 */
class PowerupPhantom : public hkpAabbPhantom
{
private:

	//TODO

public:

	PowerupPhantom(const hkAabb& aabb);

	~PowerupPhantom(void);

	virtual void addOverlappingCollidable( hkpCollidable* handle );

	virtual void removeOverlappingCollidable( hkpCollidable* handle );
};

}

#endif