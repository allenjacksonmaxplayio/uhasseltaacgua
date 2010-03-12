#ifndef USERDATA_H
#define USERDATA_H

namespace HovUni {

class UserData
{

public:

	/**
	 * Constructor
	 * @param parameters, export data
	 * @throw ParseException
	 */
	UserData();

	/**
	 * Destructor
	 */
	virtual ~UserData(void);
};

}

#endif