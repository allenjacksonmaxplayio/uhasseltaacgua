#include "BasicOverlay.h"

#include "GUIManager.h"

namespace HovUni {
	BasicOverlay::BasicOverlay(const Ogre::String& name, const Ogre::String& fileName, int width, int height, const Hikari::Position &position, Ogre::ushort zOrder) 
		: mName(name), mFileName(fileName), mWidth(width), mHeight(height), mPosition(position), mZOrder(zOrder) {
		
	}

	BasicOverlay::~BasicOverlay() {
		
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

	void BasicOverlay::activate() {
		mFlashControl = GUIManager::getSingletonPtr()->createOverlay(mName, mFileName, mWidth, mHeight, mPosition, mZOrder);
	}

	void BasicOverlay::disable() {
		GUIManager::getSingletonPtr()->removeOverlay(mName);
		//Remove reference to the pointer since the object will be deleted in the next update
		mFlashControl = 0;
	}
}