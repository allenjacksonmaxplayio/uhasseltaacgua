#ifndef CONTROLSREADER_H_
#define CONTROLSREADER_H_

#include "InputManager.h"

namespace HovUni {

/**
 * Reads the controls from the control.ini file and registers them with the input manager.
 * TODO: Should be able to write the controls back to the ini file, when they are changed?
 *
 * @author by Tobias Van Bladel
 */

class ControlsReader {
protected:

	/** The input manager */
	InputManager * mInputManager;

public:

	/**
	 * Constructor.
	 *
	 * @param	ipm	The inputmanager where we should add our controls.
	 */
	ControlsReader(InputManager * ipm);

	/**
	 * Destructor.
	 */
	~ControlsReader(void);

	/**
	 * Loads the default controls.
	 * Useful when the player has deleted his controls.ini file, or when he wants to reset them.
	 */
	void setDefaultControls();

	/**
	 * Loads the controls from the ini file.
	 */
	void readControls();
};

}

#endif