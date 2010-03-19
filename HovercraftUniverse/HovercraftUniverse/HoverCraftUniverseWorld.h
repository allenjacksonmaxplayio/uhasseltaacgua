#ifndef HoverCraftUniverseWorld_H
#define HoverCraftUniverseWorld_H

#include "AbstractHavokWorld.h"
#include "ServerLoader.h"
#include "HavokEntity.h"
#include "CharacterContextContainer.h"

namespace HovUni {

/**
 * This world describes our game state from the phyiscal point of view
 */
class HoverCraftUniverseWorld : public AbstractHavokWorld
{
private:

	friend class ServerLoader;

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
	hkStorageStringMap<HavokEntity*> mCharactersMap;

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
	 * Get a character with given name
	 * @param name
	 * @return character, HK_NULL if not found
	 */
	HavokEntity * getCharacter(const char * name);

	/**
	 * Add a character of a given type on a given start position
	 * @param name
	 * @param type
	 * @param pos
	 */
	void addCharacter( Hovercraft * entity, int pos );

	virtual void preStep();

	virtual void postStep();

};

}

#endif
