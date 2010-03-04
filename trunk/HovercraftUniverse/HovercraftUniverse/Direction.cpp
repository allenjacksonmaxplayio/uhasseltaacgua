#include "Direction.h"

namespace HovUni {
	Direction::Direction(const Ogre::String& name, const Ogre::String& fileName, int width, int height, const Hikari::Position& position, Ogre::ushort zOrder)
		: BasicOverlay(name, fileName, width, height, position, zOrder) {
	}
}