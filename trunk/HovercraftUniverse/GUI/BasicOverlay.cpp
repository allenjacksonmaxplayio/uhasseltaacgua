#include "BasicOverlay.h"

#include "GUIManager.h"

namespace HovUni {
	BasicOverlay::BasicOverlay(const Ogre::String& name, const Ogre::String& fileName, int width, int height, const Hikari::Position &position, Ogre::ushort zOrder) : mName(name) {
		mFlashControl = GUIManager::getSingletonPtr()->createOverlay(name, fileName, width, height, position, zOrder);
	}

	bool BasicOverlay::keyPressed(const OIS::KeyEvent &evt) {
		return true;
	}

	bool BasicOverlay::keyReleased(const OIS::KeyEvent &evt) {
		return true;
	}

	void BasicOverlay::registerForKeys() {
		GUIManager::getSingletonPtr()->addKeyListener(this);
	}

	void BasicOverlay::unregisterForKeys() {
		GUIManager::getSingletonPtr()->removeKeyListener(this);
	}

	Hikari::FlashControl* BasicOverlay::getFlashControl() {
		return mFlashControl;
	}
}