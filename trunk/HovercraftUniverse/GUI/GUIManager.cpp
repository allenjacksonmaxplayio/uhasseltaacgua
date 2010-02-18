#include "GUIManager.h"

#include "BasicOverlay.h"

namespace HovUni {
	GUIManager* GUIManager::msSingleton = 0;

	GUIManager::GUIManager(const Ogre::String& mediaPath, Ogre::Viewport* viewport) : mViewport(viewport) {
		mHikariMgr = new Hikari::HikariManager(mediaPath.c_str());
	}

	GUIManager& GUIManager::getSingleton(void) {
		if (!msSingleton) {
			throw UninitialisedException();
		}
		return (*msSingleton);
	}

	GUIManager* GUIManager::getSingletonPtr(void) {
		if (!msSingleton) {
			throw UninitialisedException();
		}
		return msSingleton;
	}

	void GUIManager::init(const Ogre::String& mediaPath, Ogre::Viewport* viewport) {
		msSingleton = new GUIManager(mediaPath, viewport);
	}
	
	GUIManager::~GUIManager() {

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

	Hikari::FlashControl* GUIManager::createOverlay(const Ogre::String& name, const Ogre::String& fileName, int width, int height, const Hikari::Position& position, Ogre::ushort zOrder) {
		Hikari::FlashControl* flashControl = mHikariMgr->createFlashOverlay(name, mViewport, width, height, position, zOrder);
		flashControl->load(fileName);
		
		return flashControl;
	}

	void GUIManager::activateOverlay(const BasicOverlay& overlay) {

	}
}
