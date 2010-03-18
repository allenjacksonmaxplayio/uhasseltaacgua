#include "Loader.h"
#include "CustomOgreMaxScene.h"

namespace HovUni {

Loader::Loader(void): mLobby(0) {
	// All was initialized
}

Loader::~Loader(void) {
	// All was initialized
}

void Loader::load ( const Ogre::String& filename ){
	CustomOgreMaxScene scene;
	scene.Load(filename,this);
}

void Loader::load() {
	// The lobby must have been initialized
	assert(mLobby);
	load(mLobby->getTrackFilename());
}

}