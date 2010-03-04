#ifndef CONTROLLERACTIONTYPE_H_
#define CONTROLLERACTIONTYPE_H_

namespace HovUni {

/**
 * This is an enumeration for the different controller actions.
 *
 * @author Tobias Van Bladel
 */
enum ControllerActionType {
	INVALID, ACCELERATE, BRAKE, TURNLEFT, TURNRIGHT, CHANGECAMERA, THIRD_PERSON_CAMERA, 
	FIRST_PERSON_CAMERA, REAR_VIEW_CAMERA, FREE_CAMERA, FREE_CAMERA_FWD, FREE_CAMERA_BACK,
	FREE_CAMERA_UP, FREE_CAMERA_DOWN, FREE_CAMERA_LEFT, FREE_CAMERA_RIGHT
};

/** String representations of the actions */
static const char * actionNames[]={ "Invalid", "Accelerate", "Brake", "Turn Left", "Turn Right",
	"Change Camera", "Eternal View", "Cockpit View", "Rear View", "Free Roam Camera", "Forward", "Back",
	"Up", "Down", "Left", "Right"};

}

#endif
