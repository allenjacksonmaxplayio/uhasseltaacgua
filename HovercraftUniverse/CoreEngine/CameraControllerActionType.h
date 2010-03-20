#ifndef CAMERACONTROLLERACTIONTYPE_H_
#define CAMERACONTROLLERACTIONTYPE_H_

namespace HovUni {

namespace CameraActions {

/**
 * This is an enumeration for the different camera controller actions.
 *
 * @author Tobias Van Bladel
 */
enum CameraControllerActionType {
	INVALID=0,
	CHANGECAMERA, 
	THIRD_PERSON_CAMERA, 
	FIRST_PERSON_CAMERA, 
	REAR_VIEW_CAMERA, 
	FREE_CAMERA, 
	FREE_CAMERA_FWD, 
	FREE_CAMERA_BACK,
	FREE_CAMERA_UP, 
	FREE_CAMERA_DOWN, 
	FREE_CAMERA_LEFT, 
	FREE_CAMERA_RIGHT
};

/** String representations of the actions */
static const char * cameraActionNames[]={ "Invalid", "Change Camera", "External View", 
	"Cockpit View", "Rear View", "Free Roam Camera", "Forward", "Back",
	"Up", "Down", "Left", "Right"};
}

}

#endif
