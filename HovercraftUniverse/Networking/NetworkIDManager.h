#ifndef NETWORKIDMANAGER_H_
#define NETWORKIDMANAGER_H_

#include <map>
#include <string>
#include <zoidcom/zoidcom_control.h>

using std::map;
using std::string;
using std::pair;

namespace HovUni {

/**
 * This class holds the class to ID mapping for the network framework.
 *
 * @author Olivier Berghmans
 */
class NetworkIDManager
{
private:
	/** The map type */
	typedef map<string, ZCom_ClassID> map_type;

	/** The map to ID */
	map_type mMap;

	/** The control */
	ZCom_Control* mControl;

public:
	/**
	 * Constructor
	 *
	 * @param control the network control
	 */
	NetworkIDManager(ZCom_Control* control);

	/**
	 * Destructor
	 */
	~NetworkIDManager();

	/**
	 * Register a class
	 *
	 * @param className the name of the class
	 * @return the ID
	 */
	ZCom_ClassID registerClass(const string& className);

	/**
	 * Get an ID for a class
	 *
	 * @param className the name of the class
	 * @return the ID
	 */
	ZCom_ClassID getID(const string& className) const;

private:
	/**
	 * Hide the copy constructor
	 */
	NetworkIDManager(const NetworkIDManager&) { }

};

}

#endif
