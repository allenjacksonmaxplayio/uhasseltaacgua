#ifndef RESETSPAWN_H
#define RESETSPAWN_H

#include <tinyxml/tinyxml.h>
#include <OgrePlatform.h>
#include "UserData.h"

namespace HovUni {

/**
 * @author PJ
 */ 
class ResetSpawn : public UserData
{
private:

public:

	/**
	 * Constructor
	 * @param data, xml element that descripes the reset spawn
	 * @throws ParseException
	 */
	ResetSpawn( TiXmlElement * data ) throw (ParseException);

	/**
	 * Destructor
	 */
	~ResetSpawn(void);
};

}

#endif
