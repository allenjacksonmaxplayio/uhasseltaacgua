#ifndef CONTROLLERACTIONTYPE_H_
#define CONTROLLERACTIONTYPE_H_

namespace HovUni {

/**
 * This is an enumeration for the different controller actions.
 *
 * @author Tobias Van Bladel
 */
enum ControllerActionType {
	//Note by Dirk: Do NOT change the values that have explicit constants assigned to them.
	//These values are also used in the scripts and are assumed to be the same.
	INVALID=0, ACCELERATE=1, BRAKE=2, TURNLEFT=3, TURNRIGHT=4, CHANGECAMERA, THIRD_PERSON_CAMERA, 
	FIRST_PERSON_CAMERA, REAR_VIEW_CAMERA, FREE_CAMERA, FREE_CAMERA_FWD, FREE_CAMERA_BACK,
	FREE_CAMERA_UP, FREE_CAMERA_DOWN, FREE_CAMERA_LEFT, FREE_CAMERA_RIGHT
};

/** String representations of the actions */
static const char * actionNames[]={ "Invalid", "Accelerate", "Brake", "Turn Left", "Turn Right",
	"Change Camera", "External View", "Cockpit View", "Rear View", "Free Roam Camera", "Forward", "Back",
	"Up", "Down", "Left", "Right"};

}

#endif
