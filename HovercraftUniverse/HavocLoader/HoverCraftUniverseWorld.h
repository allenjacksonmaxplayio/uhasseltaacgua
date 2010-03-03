#ifndef HoverCraftUniverseWorld_H
#define HoverCraftUniverseWorld_H

#include "AbstractHavocWorld.h"
#include "Character.h"
#include "CharacterContextContainer.h"

namespace HovUni {

class HoverCraftUniverseWorld : public AbstractHavocWorld
{
private:

	/**
	 * Map with characters mapped on their name
	 */
	hkStorageStringMap<Character*> CharactersMap;

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
	virtual void load ( const char * filename );
};

}

#endif
