#ifndef HoverCraftUniverseWorld_H
#define HoverCraftUniverseWorld_H

#include "AbstractHavocWorld.h"

namespace HovUni {

class HoverCraftUniverseWorld : public AbstractHavocWorld
{
private:

	static HoverCraftUniverseWorld * singe_ms;

public:

	/**
	 * Constructor
	 */
	HoverCraftUniverseWorld( hkReal timestep );

	static void create( hkReal timestep );

	static void destroy ();

	static HoverCraftUniverseWorld * getSingletonPtr();

	static HoverCraftUniverseWorld& getSingleton();
	
	/**
	 * Destructor
	 */
	virtual ~HoverCraftUniverseWorld(void);

	/**
	 * Load a world
	 * @param filename
	 */
	virtual void load ( const char * filename );
};

}

#endif
