#ifndef OGRELUABINDINGS_H_
#define OGRELUABINDINGS_H_

extern "C" {
  #include "lua.h"
  #include "lualib.h"
  #include "lauxlib.h"
}
#include "luabind/luabind.hpp"
#include <OgreRoot.h>
#include <OgreEntity.h>

namespace HovUni {
	/**
	*	Bindings that add the following Ogre classes to the given Lua State	:
	*		<ul>	
	*			<li>Vector3</li>
	*			<li>ColourValue</li>
	*			<li>Entity</li>
	*			<li>SceneNode</li>
	*			<li>Camera</li>
	*		</ul>
	*	@author Dirk Delahaye, Nigel Atkinson
	*/
	class OgreLuaBindings {
	private:
		lua_State* mLuaState;

	public:
		OgreLuaBindings(lua_State* L);
		~OgreLuaBindings();

		void OgreLuaBindings::bindVector3( lua_State* L );
		void OgreLuaBindings::bindColourValue( lua_State* L );
		void OgreLuaBindings::bindEntity( lua_State* L );
		//Ogre::SceneNode* OgreLuaBindings::createChildSceneNode( SceneNode *obj, const String name );
		//void OgreLuaBindings::SceneNode_yaw( SceneNode *obj, const Real degrees );
		void OgreLuaBindings::bindSceneNode( lua_State* L );
		void OgreLuaBindings::bindCamera( lua_State* L );
		void OgreLuaBindings::bindLua();
	};
}

#endif //OGRELUABINDINGS_H_