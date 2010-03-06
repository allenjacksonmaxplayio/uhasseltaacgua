#ifndef CHECKPOINTPHANTOM_H
#define CHECKPOINTPHANTOM_H

#include <Physics/Dynamics/Phantom/hkpAabbPhantom.h>

namespace HovUni {

/**
 * This is a phantom for a checkpoint. It can be used to detect if a player passes a checkpoint.
 * @author Pieter-Jan Pintens
 */
class CheckpointPhantom : public hkpAabbPhantom
{
private:

	hkString mName;

	hkInt32 mNummer;

public:
	/**
	 * Constructor
	 * @param aabb, the bounding box
	 * @param name, the name of the checkpoint
	 * @param int, the number of the checkpoint
	 */
	CheckpointPhantom(const hkAabb& aabb, hkString name, hkInt32 nummer);

	~CheckpointPhantom(void);

	virtual void addOverlappingCollidable( hkpCollidable* handle );

	virtual void removeOverlappingCollidable( hkpCollidable* handle );
};

}

#endif