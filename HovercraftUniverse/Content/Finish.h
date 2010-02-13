#ifndef FINISH_H
#define FINISH_H

#include <tinyxml/tinyxml.h>

namespace HovUni {

/**
 * @author PJ
 */ 
class Finish
{
public:

	/**
	 * Constructor
	 * @param data, xml element that descripes the finish
	 */
	Finish( TiXmlElement * data );

	/**
	 * Destructor
	 */
	~Finish(void);
};

}

#endif
