#ifndef RESETSPAWNDATA_H
#define RESETSPAWNDATA_H

#include <tinyxml/tinyxml.h>
#include <OgrePlatform.h>
#include "UserData.h"

namespace HovUni {

/**
 * @author PJ
 */ 
class ResetSpawnData : public UserData
{
private:

public:

	/**
	 * Constructor
	 * @param data, xml element that descripes the reset spawn
	 * @throws ParseException
	 */
	ResetSpawnData( TiXmlElement * data ) throw (ParseException);

	/**
	 * Destructor
	 */
	~ResetSpawnData(void);
};

}

#endif
