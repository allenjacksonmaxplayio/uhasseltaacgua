#ifndef FINISHDATA_H
#define FINISHDATA_H

#include <tinyxml/tinyxml.h>
#include "UserData.h"

namespace HovUni {

/**
 * @author PJ
 */ 
class FinishData : public UserData
{
public:

	/**
	 * Constructor
	 * @param data, xml element that descripes the finish
	 * @throws ParseException
	 */
	FinishData( TiXmlElement * data ) throw (ParseException);

	/**
	 * Destructor
	 */
	~FinishData(void);
};

}

#endif
