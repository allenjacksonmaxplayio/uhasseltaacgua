#ifndef FINISH_H
#define FINISH_H

#include <tinyxml/tinyxml.h>
#include "UserData.h"

namespace HovUni {

/**
 * @author PJ
 */ 
	class Finish : public UserData
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
