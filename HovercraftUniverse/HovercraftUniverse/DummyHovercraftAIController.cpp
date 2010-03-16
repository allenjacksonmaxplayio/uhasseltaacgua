#include "DummyHovercraftAIController.h"
#include "OgreLogManager.h"
#include <sstream>
#include "Exception.h"
#include "EntityManager.h"
#include "Entity.h"

namespace HovUni {
	DummyHovercraftAIController::DummyHovercraftAIController(std::string scriptname) {
		mClassName = "[DummyHovercraftAIController]: ";
	
		Ogre::LogManager::getSingleton().getDefaultLog()->stream() << mClassName << "Starting.";
		this->mScript = new ScriptWrapper();
		try {
			//Register our controller and its functions.
			lua_State *luaState = mScript->getLuaState();
			//Bind Ogre stuff
			OgreLuaBindings ogrebindings(luaState);
			ogrebindings.bindVector3(luaState);

			luabind::module(luaState) [
				luabind::class_<DummyHovercraftAIController>("DummyHovercraftAIController")
					.def("startAction", &DummyHovercraftAIController::startAction)
					.def("stopAction", &DummyHovercraftAIController::stopAction)
					.def("luaLog", &DummyHovercraftAIController::luaLog)
			];
			Ogre::LogManager::getSingleton().getDefaultLog()->stream() << mClassName << "Loading file " << scriptname;
			this->mScript->load(scriptname);
			Ogre::LogManager::getSingleton().getDefaultLog()->stream() << mClassName << "Registering Controller.";
			luabind::call_function<void>(luaState,"registerController", this);
		} catch (const luabind::error &er) {
			std::stringstream ss;
			ss << er.what() << " :: " << lua_tostring(mScript->getLuaState(), lua_gettop(mScript->getLuaState()));
			std::string error = ss.str();
			Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "Lua error while initialising: " << error;
			THROW(ScriptingException, error);
		}
	}

	void DummyHovercraftAIController::startAction(const int action) {
		//Ogre::LogManager::getSingleton().getDefaultLog()->stream() << mClassName << "Starting Action " << action;
		ControllerActionType a = (ControllerActionType) action;
		mActionMap[a] = true;
	}

	void DummyHovercraftAIController::stopAction(const int action) {
		ControllerActionType a = (ControllerActionType) action;
		mActionMap[a] = false;
	}

	void DummyHovercraftAIController::luaLog(const std::string message) {
		Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "Lua :: " << message;
	}

	//void DummyHovercraftAIController::getVariable(const int variable) {
	//	//something?
	//}



	//stupid functions...
	bool DummyHovercraftAIController::moveForward() {
		return mActionMap[ACCELERATE];
	}

	bool DummyHovercraftAIController::moveBackward() {
		return mActionMap[BRAKE];
	}

	bool DummyHovercraftAIController::turnLeft() {
		return mActionMap[TURNLEFT];
	}

	bool DummyHovercraftAIController::turnRight() {
		return mActionMap[TURNRIGHT];
	}

	std::vector<ControllerEvent*> DummyHovercraftAIController::getEvents() {
		//AI CONTROL OCCURS HERE
		try {
		//Position test
		//Ogre::LogManager::getSingleton().getDefaultLog()->stream() << mClassName << "Setting position.";
		luabind::call_function<void>(mScript->getLuaState(),"setPosition", getEntity()->getPosition());

		
			this->mScript->execute("decide");
		} catch (const luabind::error &er) {
			std::stringstream ss;
			ss << er.what() << " :: " << lua_tostring(mScript->getLuaState(), lua_gettop(mScript->getLuaState()));
			std::string error = ss.str();
			Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "Lua Error: " << error;
			THROW(ScriptingException, error);
		}

		std::vector<ControllerEvent*> events;
		BasicEntityEvent current(moveForward(), moveBackward(), turnLeft(), turnRight());

		// Only send an event when there is a change
		if (!(current == mLast)) {
			events.push_back(new BasicEntityEvent(current));
			mLast = current;
		}
		return events;
	}

}