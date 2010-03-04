#ifndef KEYMANAGER_H_
#define KEYMANAGER_H_

#include <OIS.h>
#include <list>
#include "ControllerActionType.h"

namespace HovUni {

/**
 * This class maps keys to their actions.
 *
 * @author Tobias Van Bladel
 */

class KeyManager {
private:
	//std::map<ControllerActionType, std::list<OIS::KeyCode> > mMapping;
	std::map<OIS::KeyCode, ControllerActionType> mMapping;

public:
	KeyManager(void);
	virtual ~KeyManager(void);

	//TODO: is OIS::KeyCode voldoende? Werkt dit ook voor bv controllers?

	/** Get the key for a certain action */
	const std::list<OIS::KeyCode> getKeys(const ControllerActionType);

	/** Change the key for this action */
	void setKey(const ControllerActionType, const OIS::KeyCode);

	/** Gets the action associated with this key */
	const ControllerActionType getAction(const OIS::KeyCode);

	/** Get the string representation of the action */
	const char* getName(const ControllerActionType);

};

}

#endif