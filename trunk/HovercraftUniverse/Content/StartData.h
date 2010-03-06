#ifndef STARTDATA_H
#define STARTDATA_H

#include "UserData.h"
#include <tinyxml/tinyxml.h>

namespace HovUni {

/**
 * Start 
 * A location in the world on where hovercrafts will be placed when the race begins.
 * @author PJ
 */ 
class StartData : public UserData
{
public:

	/**
	 * Constructor
	 * @param data, xml element that descripes the start
	 * @throws ParseException
	 */
	StartData( TiXmlElement * data ) throw (ParseException);

	/**
	 * Destructor
	 */
	~StartData(void);
};

}

#endif
