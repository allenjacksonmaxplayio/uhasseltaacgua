#ifndef KEYMANAGER_H_
#define KEYMANAGER_H_

#include <OIS.h>
#include <list>
#include "CameraControllerActionType.h"

namespace HovUni {

/**
 * This class maps keys to their actions.
 *
 * @author Tobias Van Bladel
 */

class KeyManager {
private:
	/** Mapping with keycodes to actions */
	std::map<OIS::KeyCode, int> mKeyMapping;

	/** Mapping with the camera controls (game-independent) */
	std::map<OIS::KeyCode, CameraActions::CameraControllerActionType> mCameraMapping;

	/** Mapping with actions to their name */
	std::map<int, const char *> mActionMapping;

public:
	/**
	 * Constructor
	 */
	KeyManager(void);

	/**
	 * Destructor
	 */
	virtual ~KeyManager(void);

	//TODO: is OIS::KeyCode voldoende? Werkt dit ook voor bv controllers?

	/**
	 * Register an action.
	 *
	 * @param	action	Action you want to register.
	 * @param	name	Name of the action.
	 */
	void registerAction(const int action, const char * name);

	/** 
	 * Get the key for a certain action.
	 *
	 * @param	action	Action you want the keys for.
	 * @return	List with all the keys for this action (could be empty!).
	 */
	const std::list<OIS::KeyCode> getKeys(const int action);

	/** 
	 * Change the key for this action.
	 *
	 * @param	action	Action you want to change the key of.
	 * @param	key		New key for this action.
	 */
	void setKey(const int action, const OIS::KeyCode key);

	/**
	 * Gets the action associated with this key.
	 *
	 * @param	key		The key for which you want the registered action.
	 * @return	The action associated with this key.
	 */
	const int getAction(const OIS::KeyCode key);

	/**
	 * Get all registered actions (as int code).
	 *
	 * @return	All registered user actions.
	 */
	const std::list<int> getRegisteredActions();

	/** 
	 * Get the string representation of the action.
	 *
	 * @param	action	Action for which you want the name.
	 * @return	The name of this action, if it is registered.
	 */
	const char* getName(const int action);

	/** 
	 * Get the key for a certain camera action.
	 *
	 * @param	action	Action you want the keys for.
	 * @return	List with all the keys for this camera action (could be empty!).
	 */
	const std::list<OIS::KeyCode> getCameraKeys(const CameraActions::CameraControllerActionType action);

	/** 
	 * Change the key for this camera action.
	 *
	 * @param	action	Action you want to change the key of.
	 * @param	key		New key for this camera action.
	 */
	void setCameraKey(const CameraActions::CameraControllerActionType action, const OIS::KeyCode key);

	/**
	 * Gets the cameraaction associated with this key.
	 *
	 * @param	key		The key for which you want the registered action.
	 * @return	The action associated with this key.
	 */
	const CameraActions::CameraControllerActionType getCameraAction(const OIS::KeyCode key);

	/** 
	 * Get the string representation of the camera action.
	 *
	 * @param	action	Action for which you want the name.
	 * @return	The name of this camera action.
	 */
	const char* getCameraName(const CameraActions::CameraControllerActionType action);

};

}

#endif