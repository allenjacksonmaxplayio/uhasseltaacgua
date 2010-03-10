#ifndef WORLD_H
#define WORLD_H

#include <OgreString.h>
#include "CustomOgreMaxSceneCallback.h"

namespace HovUni {

class World;

class WorldLoader {
protected:

	World * mWorld;

private:

	WorldLoader( World * world );

	virtual ~WorldLoader();

	void load( const Ogre::String& world );

	void unload ( const Ogre::String& world );
};

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
	 * Create a world using a specific world reader.
	 * The world reader depends on the context your in.
	 * For instance a client will have a different loader than the server.
	 * @param the mapname
	 * @param the loader
	 */
	static void create(const Ogre::String& map, WorldLoader * loader );
	
	/**
	 * Destroy the world
	 */
	static void destroy();

protected:

	/**
	 * Load
	 * @param map
	 * @param loader
	 */
	virtual void load( const Ogre::String& map, WorldLoader * loader );

	/**
	 * Clear all loaded data
	 */ 
	virtual void unload();
};

}

#endif