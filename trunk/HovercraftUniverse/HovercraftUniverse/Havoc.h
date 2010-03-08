#ifndef HAVOC_H
#define HAVOC_H

#include "HoverCraftUniverseWorld.h"

namespace HovUni {

class Havoc
{
private:

	static HoverCraftUniverseWorld * ms_world;

	Havoc(void);
	~Havoc(void);

public:

	/**
	 * Start havoc framework
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
	 * Stop havoc framework
	 */
	static void stop();


};

}

#endif