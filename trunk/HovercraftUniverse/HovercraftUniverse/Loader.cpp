#include "Loader.h"
#include "CustomOgreMaxScene.h"

namespace HovUni {

Loader::Loader(void): mLobby(0) {
}

Loader::~Loader(void){
}

void Loader::load ( const Ogre::String& filename ){
	CustomOgreMaxScene scene;
	scene.Load(filename,this);
}

}