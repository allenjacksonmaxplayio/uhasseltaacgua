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
			Ogre::LogManager::getSingleton().getDefaultLog()->stream() << mClassName << "Binding Ogre Classes.";
			OgreLuaBindings ogrebindings(luaState);
			ogrebindings.bindVector3(luaState);
			luabind::module(luaState) [
				luabind::class_<DummyHovercraftAIController>("AIController")
					.def("setAction", &DummyHovercraftAIController::setAction)
					.def("getAction", &DummyHovercraftAIController::getAction)
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

	void DummyHovercraftAIController::initialize() {
		try {
			lua_State* luaState = mScript->getLuaState();
			Ogre::LogManager::getSingleton().getDefaultLog()->stream() << mClassName << "Binding Game Entity Class.";
			bindEntity(luaState);
			luabind::call_function<void>(luaState,"setEntity", getEntity());
		} catch (const luabind::error &er) {
			std::stringstream ss;
			ss << er.what() << " :: " << lua_tostring(mScript->getLuaState(), lua_gettop(mScript->getLuaState()));
			std::string error = ss.str();
			Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "Lua Error: " << error;
			THROW(ScriptingException, error);
		}
	}

	std::vector<ControllerEvent*> DummyHovercraftAIController::getEvents() {
		//AI CONTROL OCCURS HERE
		try {
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

	void DummyHovercraftAIController::bindEntity(lua_State* L) {
		luabind::module(L)
		[
			luabind::class_<Entity>("GameEntity") //"Entity" bestaat al in Lua (Ogre::Entity)
				.def("getName",			&Entity::getName)
				.def("getOrientation",	&Entity::getOrientation)
				.def("getPosition",		&Entity::getPosition)
				.def("getUpVector",		&Entity::getUpVector)
		];
	}


	void DummyHovercraftAIController::setAction(const int action, const bool state) {
		//Ogre::LogManager::getSingleton().getDefaultLog()->stream() << mClassName << "AI SETTING " << action << " TO " << state;
		ControllerActionType a = (ControllerActionType) action;
		mActionMap[a] = state;
	}

	bool DummyHovercraftAIController::getAction(const int action) {
		ControllerActionType a = (ControllerActionType) action;
		return mActionMap[a];
	}

	void DummyHovercraftAIController::luaLog(const std::string message) {
		Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "Lua :: " << message;
	}


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


}