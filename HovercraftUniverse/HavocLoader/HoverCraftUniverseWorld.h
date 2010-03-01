#ifndef HoverCraftUniverseWorld_H
#define HoverCraftUniverseWorld_H

#include "AbstractHavocWorld.h"

namespace HovUni {

class HoverCraftUniverseWorld : public AbstractHavocWorld
{
public:

	static HoverCraftUniverseWorld * world;

	/**
	 * Constructor
	 */
	HoverCraftUniverseWorld(void);

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
