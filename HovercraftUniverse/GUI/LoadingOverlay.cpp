#include "LoadingOverlay.h"

namespace HovUni {

	LoadingOverlay::LoadingOverlay(const Ogre::String& name, const Ogre::String& fileName, int width, int height, const Hikari::Position& position, Ogre::ushort zOrder) 
		: BasicOverlay(name, fileName, width, height, position, zOrder) {
	}
	
	void LoadingOverlay::setLoaded(Ogre::Real loaded) {
		this->callFunction("setLoaded", Hikari::Args(loaded));
	}
}