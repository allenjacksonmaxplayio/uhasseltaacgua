#ifndef POWERUPSPAWN_H
#define POWERUPSPAWN_H

#include "UserData.h"
#include <tinyxml/tinyxml.h>

namespace HovUni {

class PowerupSpawn
{
public:

	/**
	 * Constructor
	 * @param data
	 */
	PowerupSpawn(TiXmlElement * data);

	/**
	 * Destructor
	 */
	~PowerupSpawn(void);
};

}

#endif
