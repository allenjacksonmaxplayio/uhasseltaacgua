#ifndef DIRECTION_H
#define DIRECTION_H

#include <BasicOverlay.h>

namespace HovUni {
	/**
	 * An overlay containing a direction representation.
	 *
	 * @author Nick De Frangh
	 */
	class Direction : public BasicOverlay {
		public:
			/**
			 * Direction constructor, see BasicOverlay for parameter description
			 */
			Direction(const Ogre::String& name, const Ogre::String& fileName, int width, int height, const Hikari::Position& position, Ogre::ushort zOrder = 0);

	};
}

#endif //DIRECTION_H