#include "HovercraftAIController.h"
#include "OgreLogManager.h"
#include <sstream>
#include "Exception.h"

#include "EntityManager.h"
#include "Entity.h"
#include "Start.h"
#include "CheckPoint.h"
#include "Finish.h"

namespace HovUni {
	HovercraftAIController::HovercraftAIController(std::string scriptname) {
		mClassName = "[HovercraftAIController]: ";
	
		Ogre::LogManager::getSingleton().getDefaultLog()->stream() << mClassName << "Starting.";
		this->mScript = new ScriptWrapper();
		try {
			//Register our controller and its functions.
			lua_State *luaState = mScript->getLuaState();
			//Bind Ogre stuff
			Ogre::LogManager::getSingleton().getDefaultLog()->stream() << mClassName << "Binding Ogre Classes.";
			OgreLuaBindings ogrebindings(luaState);
			ogrebindings.bindVector3();
			luabind::module(luaState) [
				luabind::class_<HovercraftAIController>("AIController")
					.def("setAction", &HovercraftAIController::setAction)
					.def("getAction", &HovercraftAIController::getAction)
					.def("luaLog", &HovercraftAIController::luaLog)
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
		} catch (const std::runtime_error &e) {
			Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "Runtime error while initialising: " << e.what();
			THROW(ScriptingException, e.what());
		}
	}

	void HovercraftAIController::initialize() {
		try {
			lua_State* luaState = mScript->getLuaState();
			Ogre::LogManager::getSingleton().getDefaultLog()->stream() << mClassName << "Binding Game Entity Class.";
			bindEntity(luaState);
			luabind::call_function<void>(luaState,"setEntity", getEntity());
			
			
			//Temporary Path! 
			Ogre::LogManager::getSingleton().getDefaultLog()->stream() << mClassName << "Setting Path.";
			luabind::object table = luabind::newtable(luaState);
			std::vector<Entity*> checkpoints = EntityManager::getClientSingletonPtr()->getEntities(CheckPoint::CATEGORY);
			int index = 1; // Lua tables start at 1.
			table[index] = EntityManager::getClientSingletonPtr()->getEntity(Start::CATEGORY);
			index++;
			for(unsigned int i = 0; i < checkpoints.size(); i++) {
				Ogre::LogManager::getSingleton().getDefaultLog()->stream() << mClassName << "Setting Path[" << index << "] to checkpoints[" << i << "].";
				table[index] = checkpoints[i];
				index++;
			}
			table[index] = EntityManager::getClientSingletonPtr()->getEntity(Finish::CATEGORY);
			Ogre::LogManager::getSingleton().getDefaultLog()->stream() << mClassName << "Path table filled. Calling setPath.";
			luabind::call_function<void>(luaState,"setPath", table);
		} catch (const luabind::error &er) {
			std::stringstream ss;
			ss << er.what() << " :: " << lua_tostring(mScript->getLuaState(), lua_gettop(mScript->getLuaState()));
			std::string error = ss.str();
			Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "Lua Error: " << error;
			THROW(ScriptingException, error);
		} catch (const std::runtime_error &e) {
			Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "Runtime Error: " << e.what();
			THROW(ScriptingException, e.what());
		}
	}

	std::vector<ControllerEvent*> HovercraftAIController::getEvents() {
		//AI CONTROL OCCURS HERE
		try {
			this->mScript->execute("decide");
		} catch (const luabind::error &er) {
			std::stringstream ss;
			ss << er.what() << " :: " << lua_tostring(mScript->getLuaState(), lua_gettop(mScript->getLuaState()));
			Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "Lua Error: " << ss.str();
			THROW(ScriptingException, ss.str());
		} catch (const std::runtime_error &e) {
			Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "Runtime Error: " << e.what();
			THROW(ScriptingException, e.what());
		}
		return HovercraftController::getEvents();
	}

	void HovercraftAIController::bindEntity(lua_State* L) {
		luabind::module(L)
		[
			luabind::class_<Entity>("GameEntity") //"Entity" bestaat al in Lua (Ogre::Entity)
				.def("getName",			&Entity::getName)
				.def("getOrientation",	&Entity::getOrientation)
				.def("getPosition",		&Entity::getPosition)
				.def("getVelocity",		&Entity::getVelocity)
				.def("getUpVector",		&Entity::getUpVector)
		];
	}


	void HovercraftAIController::setAction(const int action, const bool state) {
		//Ogre::LogManager::getSingleton().getDefaultLog()->stream() << mClassName << "AI SETTING " << action << " TO " << state;
		ControllerActions::ControllerActionType a = (ControllerActions::ControllerActionType) action;
		mActionMap[a] = state;
	}

	bool HovercraftAIController::getAction(const int action) {
		ControllerActions::ControllerActionType a = (ControllerActions::ControllerActionType) action;
		return mActionMap[a];
	}

	void HovercraftAIController::luaLog(const std::string message) {
		Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "Lua :: " << message;
	}


	//stupid functions...
	bool HovercraftAIController::moveForward() {
		return mActionMap[ControllerActions::ACCELERATE];
	}

	bool HovercraftAIController::moveBackward() {
		return mActionMap[ControllerActions::BRAKE];
	}

	bool HovercraftAIController::turnLeft() {
		return mActionMap[ControllerActions::TURNLEFT];
	}

	bool HovercraftAIController::turnRight() {
		return mActionMap[ControllerActions::TURNRIGHT];
	}


}