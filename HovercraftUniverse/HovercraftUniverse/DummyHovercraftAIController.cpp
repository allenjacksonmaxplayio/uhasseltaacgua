#include "DummyHovercraftAIController.h"
#include <iostream>

namespace HovUni {

	DummyHovercraftAIController::DummyHovercraftAIController(std::string scriptname) {
		this->mScript = new ScriptWrapper();
		
		//Register startAction
		lua_State *luaState = mScript->getLuaState();
		luabind::module(luaState) [
			luabind::def("startAction", (void(DummyHovercraftAIController::*)(int))&DummyHovercraftAIController::startAction)
		];
		this->mScript->load(scriptname);
	}

	void DummyHovercraftAIController::startAction(int action) {
		//...
	}

	void DummyHovercraftAIController::stopAction(int action) {
		//...
	}



}