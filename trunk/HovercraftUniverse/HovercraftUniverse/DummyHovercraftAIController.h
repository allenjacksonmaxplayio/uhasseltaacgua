#ifndef DUMMYHOVERCRAFTAICONTROLLER_H_
#define DUMMYHOVERCRAFTAICONTROLLER_H_

#include <string>
#include "DummyHovercraftController.h"
#include "ScriptWrapper.h"

namespace HovUni {

/**
*	The Dummy AI Controller.
*	@author Dirk Delahaye
*/
class DummyHovercraftAIController : public DummyHovercraftController {
	//Provide public accesspoints for AI script.
private:
	ScriptWrapper* mScript;
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


};

}

#endif //DUMMYHOVERCRAFTAICONTROLLER_H_