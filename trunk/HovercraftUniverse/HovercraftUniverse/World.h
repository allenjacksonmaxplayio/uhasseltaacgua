#ifndef WORLD_H
#define WORLD_H

#include <OgreString.h>
#include "CustomOgreMaxSceneCallback.h"

namespace HovUni {

class World{
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
	static void create(const Ogre::String& map);
	
	/**
	 * Destroy the world
	 */
	static void destroy();
};

}

#endif