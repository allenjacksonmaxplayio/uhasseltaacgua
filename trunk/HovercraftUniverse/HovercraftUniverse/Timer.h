#ifndef TIMER_H
#define TIMER_H

#include <BasicOverlay.h>

namespace HovUni {
	/**
	 * An overlay containing a timer representation.
	 *
	 * @author Nick De Frangh
	 */
	class Timer : public BasicOverlay {
		public:
			/**
			 * Timer constructor, see BasicOverlay for parameter description
			 */
			Timer(const Ogre::String& name, const Ogre::String& fileName, int width, int height, const Hikari::Position& position, Ogre::ushort zOrder = 0);

	};
}

#endif //TIMEBEHIND_H