#include "HovercraftAIController.h"
#include "OgreLogManager.h"
#include <sstream>
#include "Exception.h"

#include "EntityManager.h"
#include "Entity.h"
#include "Hovercraft.h"

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
			table[1] = Ogre::Vector3(-69.6f, 5, -4.9f);
			table[2] = Ogre::Vector3(92, 5, 4.9f);
			table[3] = Ogre::Vector3(120, 4, -6);
			table[4] = Ogre::Vector3(120, -20, -9);
			table[5] = Ogre::Vector3(106, -40, -10);
			table[6] = Ogre::Vector3(80, -50, -10);
			table[7] = Ogre::Vector3(-20, -46, 11);
			table[8] = Ogre::Vector3(-90, -45, 29);

			Ogre::LogManager::getSingleton().getDefaultLog()->stream() << mClassName << "Path table filled. Calling setPath.";
			luabind::call_function<void>(luaState,"setPath", table);
		} catch (const luabind::error &er) {
			std::stringstream ss;
			ss << er.what() << " :: " << lua_tostring(mScript->getLuaState(), lua_gettop(mScript->getLuaState()));
			std::string error = ss.str();
			Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "Lua Error during AI initialisation: " << error;
			THROW(ScriptingException, error);
		} catch (const std::runtime_error &e) {
			Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "Runtime Error during AI initialisation: " << e.what();
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
			luabind::class_<Entity>("GameEntity") //"Entity" bestaat al in onze Lua scope (Ogre::Entity)
				.def("getName",				&Entity::getName)
				.def("getOrientation",		&Entity::getOrientation)
				.def("getPosition",			&Entity::getPosition)
				.def("getVelocity",			&Entity::getVelocity)
				.def("getUpVector",			&Entity::getUpVector),
			luabind::class_<Hovercraft, Entity>("Hovercraft")
				.def("isInCollisionState",	&Hovercraft::isInCollisionState)
				.def("getSpeed",			&Hovercraft::getSpeed)
				.def("getMaximumSpeed",		&Hovercraft::getMaximumSpeed)
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