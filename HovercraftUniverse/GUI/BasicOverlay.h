#ifndef BASICOVERLAY_H
#define BASICOVERLAY_H

/**
 * The BasicOverlay class will be a pure virtual class abstracting the notion of
 * a Hikari::FlashControl object and providing additional functionality.
 *
 * @author Nick De Frangh
 */

#include <Hikari.h>
 
using std::string;

namespace HovUni {
	class BasicOverlay {
		private:
			Ogre::String mName;
			Hikari::FlashControl* mFlashControl;

		public:
			BasicOverlay(const Ogre::String& name, const Ogre::String& fileName, Ogre::Viewport* viewport, int width, int height, const Hikari::Position& position, Ogre::ushort zOrder = 0);

			Hikari::FlashControl* getFlashControl();
	};
}

#endif //BASICOVERLAY_H