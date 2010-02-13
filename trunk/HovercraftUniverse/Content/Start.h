#ifndef START_H
#define START_H

#include <tinyxml/tinyxml.h>

namespace HovUni {

/**
 * @author PJ
 */ 
class Start
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
