#include "Timer.h"

namespace HovUni {
	Timer::Timer(const Ogre::String& name, const Ogre::String& fileName, int width, int height, const Hikari::Position& position, Ogre::ushort zOrder)
		: BasicOverlay(name, fileName, width, height, position, zOrder) {
	}
}