#include "GUIManager.h"

#include "BasicOverlay.h"
#include "OverlayContainer.h"

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
		if(mHikariMgr) {
			removeAllOverlays();
			delete mHikariMgr;
		}
	}

	void GUIManager::removeOverlay(const Ogre::String& name) {
		mHikariMgr->destroyFlashControl(name);
	}

	void GUIManager::removeAllOverlays() {
		mHikariMgr->destroyAllControls();
	}

	void GUIManager::update() {
		mHikariMgr->update();
	}

	bool GUIManager::mouseMoved(const OIS::MouseEvent &evt) {
		return mHikariMgr->injectMouseMove(evt.state.X.abs, evt.state.Y.abs) || mHikariMgr->injectMouseWheel(evt.state.Z.rel);
	}

	bool GUIManager::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
		return mHikariMgr->injectMouseDown(id);
	}

	bool GUIManager::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
		return mHikariMgr->injectMouseUp(id);
	}

	bool GUIManager::keyPressed(const OIS::KeyEvent &evt) {
		std::vector<OIS::KeyListener*>::iterator it;

		for (it = mKeyListeners.begin(); it != mKeyListeners.end(); ++it) {
			(*it)->keyPressed(evt);
		}

		return true;
		
		//Quite meaningless code, taken from Hikari demo, will change when needed
		if(mHikariMgr->isAnyFocused()) {
			return true;
		}

		return true;
	}

	bool GUIManager::keyReleased(const OIS::KeyEvent &evt) {
		std::vector<OIS::KeyListener*>::iterator it;

		for (it = mKeyListeners.begin(); it != mKeyListeners.end(); ++it) {
			(*it)->keyReleased(evt);
		}

		return true;
	}

	void GUIManager::addKeyListener(OIS::KeyListener* listener) {
		mKeyListeners.push_back(listener);
	}

	void GUIManager::removeKeyListener(OIS::KeyListener* listener) {
		std::vector<OIS::KeyListener*>::iterator it;

		for (it = mKeyListeners.begin(); it != mKeyListeners.end(); ++it) {
			if ( (*it) == listener ) {
				//Remove it!
				mKeyListeners.erase(it);
				break;
			}
		}
	}

	Hikari::FlashControl* GUIManager::createOverlay(const Ogre::String& name, const Ogre::String& fileName, int width, int height, const Hikari::Position& position, Ogre::ushort zOrder) {
		Hikari::FlashControl* flashControl = mHikariMgr->createFlashOverlay(name, mViewport, width, height, position, zOrder);
		flashControl->load(fileName);
		
		return flashControl;
	}

	void GUIManager::activateOverlay(BasicOverlay* overlay) {
		overlay->activate();
	}

	void GUIManager::disableOverlay(BasicOverlay* overlay) {
		overlay->disable();
	}

	void GUIManager::activateOverlayContainer(OverlayContainer* overlayContainer) {
		std::map<std::string, BasicOverlay*> overlays = overlayContainer->getOverlays();

		for(std::map<std::string, BasicOverlay*>::iterator it = overlays.begin(); it != overlays.end(); ++it) {
			(*it).second->activate();
		}
	}
			
	void GUIManager::disableOverlayContainer(OverlayContainer* overlayContainer) {
		std::map<std::string, BasicOverlay*> overlays = overlayContainer->getOverlays();

		for(std::map<std::string, BasicOverlay*>::iterator it = overlays.begin(); it != overlays.end(); ++it) {
			(*it).second->disable();
		}
	}
}
