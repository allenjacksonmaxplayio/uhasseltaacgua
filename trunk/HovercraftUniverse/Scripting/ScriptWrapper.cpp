#include "ScriptWrapper.h"

namespace HovUni {
	ScriptWrapper::ScriptWrapper() {
		//Open2X?
		mLuaState = lua_open();
	}

	ScriptWrapper::~ScriptWrapper() {
		lua_close(mLuaState);
	}

	lua_State* ScriptWrapper::getLuaState() {
		return mLuaState;
	}

	void ScriptWrapper::registerFunction( std::string name, void (*function)(int)) {
		luabind::module(mLuaState) [
			luabind::def(name.c_str(), function)
		];
	}

	int ScriptWrapper::execute( std::string function) {
		return luabind::call_function<int>(mLuaState, function.c_str());
	}

	void ScriptWrapper::load( std::string filename) {
		luaL_dofile(mLuaState, filename.c_str());
	}
}