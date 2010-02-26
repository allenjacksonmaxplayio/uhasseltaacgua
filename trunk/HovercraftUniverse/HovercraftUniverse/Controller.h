#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <vector>
#include "ControllerEvent.h"

namespace HovUni {

/**
 * Provides controls for a game character. This interface is polled by entities in order to check
 * what the entity should do. These controllers could be player controls, AI controls, game controls, 
 * ...
 *
 * @author Kristof Overdulve & Olivier Berghmans
 */
class Controller {

public:
	/**
	 * Destructor
	 */
	virtual ~Controller() {}

	/**
	 * Poll for a list of controller events
	 *
	 * @return the list of events
	 */
	virtual std::vector<ControllerEvent*> getEvents() = 0;

};

}

#endif