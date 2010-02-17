#include "GUIManager.h"

namespace HovUni {
	GUIManager::GUIManager(const Ogre::String& mediaPath) {

	}
	
	GUIManager::~GUIManager() {

	}

	void GUIManager::activateOverlay(const Ogre::String& name, const Ogre::String& fileName, Ogre::Viewport* viewport, int width, int height, const Hikari::Position& position, Ogre::ushort zOrder) {

	}

	void GUIManager::removeOverlay(const Ogre::String& name) {

	}

	void GUIManager::removeAllOverlays() {

	}

	void GUIManager::update() {

	}

	bool GUIManager::mouseMoved(const OIS::MouseEvent &evt) {
		return true;
	}

	bool GUIManager::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
		return true;
	}

	bool GUIManager::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
		return true;
	}

	bool GUIManager::keyPressed(const OIS::KeyEvent &evt) {
		return true;
	}

	bool GUIManager::keyReleased(const OIS::KeyEvent &evt) {
		return true;
	}
}
