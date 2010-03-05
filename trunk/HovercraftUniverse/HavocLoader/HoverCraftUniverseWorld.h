#ifndef HoverCraftUniverseWorld_H
#define HoverCraftUniverseWorld_H

#include "AbstractHavocWorld.h"
#include "PhysicsLoader.h"
#include "Character.h"
#include "CharacterContextContainer.h"

namespace HovUni {

class HoverCraftUniverseWorld : public AbstractHavocWorld
{
private:

	friend class PhysicsLoader;

	/**
	 * Start phantom
	 */
	hkpPhantom * mStart;

	/**
	 * Finish phantom
	 */
	hkpPhantom * mFinish;

	/**
	 * An array with start positions
	 */
	hkArray<hkVector4> mStartPositions;

	/**
	 * An array with reset positions
	 */
	hkArray<hkVector4> mResetPositions;

	/**
	 * An array with start powerup positions
	 */
	hkArray<hkVector4> mPowerupPositions;

	/**
	 * Map with checkpoints mapped on their name
	 */
	hkStorageStringMap<hkpPhantom*> mCheckpoint;	

	/**
	 * Map with powerupspawns mapped on their name
	 */
	hkStorageStringMap<hkpPhantom*> mPowerupSpawn;

	/**
	 * Map with asteroids mapped on their name
	 */
	hkStorageStringMap<hkpRigidBody*> mAsteroidsMap;

	/**
	 * Map with characters mapped on their name
	 */
	hkStorageStringMap<Character*> mCharactersMap;

	/**
	 * Container for all types of characters we want
	 */
	CharacterContextContainer mCharacterContainer;

public:

	/**
	 * Constructor
	 */
	HoverCraftUniverseWorld( hkReal timestep );
	
	/**
	 * Destructor
	 */
	virtual ~HoverCraftUniverseWorld(void);

	/**
	 * Load a scene file.
	 * Parse this and load a physics version of in in our havoc world
	 * @param filename
	 */
	virtual bool loadSceneFile ( const char * filename );
};

}

#endif
