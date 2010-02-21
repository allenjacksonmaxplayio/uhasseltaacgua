#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H

#include <BasicOverlay.h>

namespace HovUni {
	/**
	 * An overlay containing a speedometer representation.
	 *
	 * @author Nick De Frangh
	 */
	class Speedometer : public BasicOverlay {
		public:
			Speedometer(const Ogre::String& name, const Ogre::String& fileName, int width, int height, const Hikari::Position& position, Ogre::ushort zOrder = 0);
		
	};
}

#endif //SPEEDOMETER_H