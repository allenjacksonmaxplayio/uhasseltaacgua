#ifndef DUMMYHOVERCRAFTAICONTROLLER_H_
#define DUMMYHOVERCRAFTAICONTROLLER_H_

#include <string>
#include <vector>
#include <map>
#include "DummyHovercraftController.h"
#include "ScriptWrapper.h"
#include "OgreLuaBindings.h"
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

	void bindEntity(lua_State* L);
public:
	/**
	*	Start the AI Controller with a script.
	*	NOTE: MUST CALL "initialize" function after constructing and setting the controller!
	*	1) Construct the controller
	*	2) setController() in the client
	*	3) AIController.initialize();
	*/
	DummyHovercraftAIController(std::string scriptname);

	/**
	*	Initialization function.
	*	Takes care of bindings and definition of entities.
	*/
	void initialize();

	/**
	*	Initiate or stop an action (the AI presses or releases a key)
	*	@param	action	The action (ControllerActionType value).
	*	@pararm	state	The current state (on or off: true or false)
	*/
	void setAction(const int action, const bool state);

	/**
	*	Get the current state of an action.
	*	@param	action	The action (ControllerActionType value)
	*	@return	The current state (true for on, false for off)
	*/
	bool getAction(const int action);

	/**
	*	Provides a logging function for the Lua Script.
	*/
	void luaLog(const std::string message);


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