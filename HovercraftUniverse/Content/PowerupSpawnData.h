#ifndef POWERUPSPAWNDATA_H
#define POWERUPSPAWNDATA_H

#include "UserData.h"
#include <tinyxml/tinyxml.h>

namespace HovUni {

class PowerupSpawnData
{
public:

	/**
	 * Constructor
	 * @param data
	 * @throws ParseException
	 */
	PowerupSpawnData(TiXmlElement * data) throw (ParseException);

	/**
	 * Destructor
	 */
	~PowerupSpawnData(void);
};

}

#endif
