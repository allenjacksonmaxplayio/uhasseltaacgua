#ifndef START_H
#define START_H

#include "UserData.h"
#include <tinyxml/tinyxml.h>

namespace HovUni {

/**
 * Start 
 * A location in the world on where hovercrafts will be placed when the race begins.
 * @author PJ
 */ 
class Start : public UserData
{
public:

	/**
	 * Constructor
	 * @param data, xml element that descripes the start
	 */
	Start( TiXmlElement * data );

	/**
	 * Destructor
	 */
	~Start(void);
};

}

#endif
