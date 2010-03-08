#ifndef DUMMYHOVERCRAFTAICONTROLLER_H_
#define DUMMYHOVERCRAFTAICONTROLLER_H_

#include <string>
#include <vector>
#include <map>
#include "DummyHovercraftController.h"
#include "ScriptWrapper.h"
#include "ControllerActionType.h"

namespace HovUni {

/**
*	The Dummy AI Controller.
*	@author Dirk Delahaye
*/
class DummyHovercraftAIController : public DummyHovercraftController {
	//Provide public accesspoints for AI script.
private:
	ScriptWrapper* mScript;
	std::map<ControllerActionType, bool> mActionMap;
	std::string mClassName;
public:

	/**
	*	Start the AI Controller with a script.
	*/
	DummyHovercraftAIController(std::string scriptname);

	/**
	*	Initiate an action (or: the AI presses a key)
	*	@param	action	The action (ControllerActionType value).
	*/
	void startAction(int action);

	/**
	*	Stop an action (or: the AI releases a key)
	*	@param	action	The action (ControllerActionType value)
	*/
	void stopAction(int action);

	/**
	* @see DummyHovercraftController::moveForward()
	*/
	bool moveForward();

	/**
	* @see DummyHovercraftController::moveBackward()
	*/
	bool moveBackward();

	/**
	* @see DummyHovercraftController::turnLeft()
	*/
	bool turnLeft();

	/**
	* @see DummyHovercraftController::turnRight()
	*/
	bool turnRight();

	/**
	 * @see Controller::getEvents()
	 */
	std::vector<ControllerEvent*> getEvents();
};

}

#endif //DUMMYHOVERCRAFTAICONTROLLER_H_