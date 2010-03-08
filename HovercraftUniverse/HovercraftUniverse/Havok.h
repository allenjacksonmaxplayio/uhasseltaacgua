#ifndef HAVOK_H
#define HAVOK_H

#include "HoverCraftUniverseWorld.h"

namespace HovUni {

class Havok
{
private:

	static HoverCraftUniverseWorld * ms_world;

	Havok(void);
	~Havok(void);

public:

	/**
	 * Start havok framework
	 */
	static void start();

	/**
	 * Get a pointer to the world object
	 * @return world
	 */
	static HoverCraftUniverseWorld * getSingletonPtr();

	/**
	 * Get a reference to the world object
	 * @return world
	 */
	static HoverCraftUniverseWorld& getSingleton();

	/**
	 * Stop havok framework
	 */
	static void stop();


};

}

#endif