#ifndef CONTROLLER_H_
#define CONTROLLER_H_

namespace HovUni {

/**
 * Provides controls for a game character. This interface is polled by entities in order to check
 * what the entity should do. These controllers could be player controls, AI controls, game controls, 
 * ...
 *
 * @author Kristof Overdulve
 */
class Controller {

public:
	// Empty class, should be inherited
	Controller() {}
	virtual ~Controller() {}

};

}

#endif