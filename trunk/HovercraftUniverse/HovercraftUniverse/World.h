#ifndef WORLD_H
#define WORLD_H

#include <OgreString.h>

namespace HovUni {

class World
{
private:

	// singleton pointer
	static World * ms_world;

protected:

	World(void);

private:

	//SHOULD NOT BE REPLICATED

	//flag is loaded
	bool mIsLoaded;


private:

	//SHOULD BE REPLICATED



public:

	~World(void);

	/**
	 * Get the singleton
	 * @return world
	 */
	static World * getSingletonPtr();

	/**
	 * Get the world
	 * @return world
	 */
	static World& getSingleton();

	/**
	 * Create a world
	 */
	static void create(const Ogre::String& map);
	
	/**
	 * Destroy the world
	 */
	static void destroy();

protected:

	/**
	 * Load
	 * @param map
	 */
	void load( const Ogre::String& map );

	/**
	 * Clear all loaded data
	 */ 
	void unload();
};

}

#endif
