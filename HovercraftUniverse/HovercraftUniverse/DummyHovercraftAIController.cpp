#include "DummyHovercraftAIController.h"
#include "OgreLogManager.h"

namespace HovUni {

	DummyHovercraftAIController::DummyHovercraftAIController(std::string scriptname) {
		Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "DummyHovercraftAIController Starting.";
		this->mScript = new ScriptWrapper();
		try {
			//Register our controller and its functions.
			lua_State *luaState = mScript->getLuaState();
			luabind::module(luaState) [
				//luabind::def("startAction", (void(DummyHovercraftAIController::*)(int))&DummyHovercraftAIController::startAction)
				luabind::class_<DummyHovercraftAIController>("DummyHovercraftAIController")
					//.def(luabind::constructor<>())
					.def("startAction", &DummyHovercraftAIController::startAction)
			];
			this->mScript->load(scriptname);
			Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "DummyHovercraftAIController Registering Controller.";
			luabind::call_function<void>(luaState,"registerController", this);
		} catch (const luabind::error &er) {
			Ogre::LogManager::getSingleton().getDefaultLog()->stream() << er.what();
		}
	}

	void DummyHovercraftAIController::startAction(int action) {
		Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "DummyHovercraftAIController Starting Action " << action;
		ControllerActionType a = (ControllerActionType) action;
		mActionMap[a] = true;
	}

	void DummyHovercraftAIController::stopAction(int action) {
		ControllerActionType a = (ControllerActionType) action;
		mActionMap[a] = false;
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

	std::vector<ControllerEvent*> DummyHovercraftAIController::getEvents() {
		//Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "DummyHovercraftAIController deciding";
		//AI CONTROL OCCURS HERE?
		try {
			this->mScript->execute("decide");
		} catch (const luabind::error &er) {
			Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "Lua Error: " << er.what() << " :: " << lua_tostring(mScript->getLuaState(), -1);
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