#include "BasicOverlay.h"

#include "GUIManager.h"

namespace HovUni {
	BasicOverlay::BasicOverlay(const Ogre::String& name, const Ogre::String& fileName, int width, int height, const Hikari::Position &position, Ogre::ushort zOrder) : mName(name) {
		mFlashControl = GUIManager::getSingletonPtr()->createOverlay(name, fileName, width, height, position, zOrder);
	}

	Hikari::FlashControl* BasicOverlay::getFlashControl() {
		return mFlashControl;
	}
}