#include "Results.h"
#include "Exception.h"

namespace HovUni {
	Results::Results(const Ogre::String& name, const Ogre::String& fileName, int width, int height, const Hikari::Position& position, Ogre::ushort zOrder) 
			: BasicOverlay(name, fileName, width, height, position, zOrder) {
		this->setBParameter(BasicOverlay::ALPHAHACK, true);
	}

	void Results::addPlayer(int position, const Ogre::String& name, long time) {

	}
}