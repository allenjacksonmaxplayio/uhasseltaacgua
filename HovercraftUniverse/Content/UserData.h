#ifndef USERDATA_H
#define USERDATA_H

#include "ParseException.h"

namespace HovUni {

class UserData
{

public:

	/**
	 * Constructor
	 * @param parameters, export data
	 * @throw ParseException
	 */
	UserData() throw (ParseException);

	/**
	 * Destructor
	 */
	virtual ~UserData(void);
};

}

#endif