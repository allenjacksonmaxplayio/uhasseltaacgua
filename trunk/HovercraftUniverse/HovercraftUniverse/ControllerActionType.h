#ifndef CONTROLLERACTIONTYPE_H_
#define CONTROLLERACTIONTYPE_H_

namespace HovUni {

/**
 * This is an enumeration for the different controller actions.
 *
 * @author Tobias Van Bladel
 */
enum ControllerActionType {
	INVALID, ACCELERATE, BRAKE, TURNLEFT, TURNRIGHT, CHANGECAMERA
};

/** String representations of the actions */
static const char * actionNames[]={ "Invalid", "Accelerate", "Brake", "Turn Left", "Turn Right", "Change Camera" };

}

#endif
