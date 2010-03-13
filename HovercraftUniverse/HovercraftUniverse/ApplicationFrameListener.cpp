#include "ApplicationFrameListener.h"
#include <GUIManager.h>
#include "InputManager.h"
#include <OgreLogManager.h>

namespace HovUni {

ApplicationFrameListener::ApplicationFrameListener(Ogre::SceneManager * sceneMgr, EntityManager * entityMgr, 
												   RepresentationManager * reprMgr, InputManager * inputMgr, 
												   ClientCore* client)
		: mSceneMgr(sceneMgr), mEntityManager(entityMgr), mRepresentationManager(reprMgr), mInputManager(inputMgr), 
		mRotate(0.13f), mMove(250), mContinue(true), mDirection(Ogre::Vector3::ZERO), mMouseVisual(),
		mClient(client), mElapsed(0.0f) {
	// Register this class with input manager
	mInputManager->addKeyListener(this, "ApplicationFrameListener");
	mInputManager->addMouseListener(this, "ApplicationFrameListener");

	mGUIManager = GUIManager::getSingletonPtr();

	mMouseVisual.setImage("cursor.png");
	mMouseVisual.setVisible(true);
	mMouseVisual.setWindowDimensions(mGUIManager->getResolutionWidth(), mGUIManager->getResolutionHeight());
}

ApplicationFrameListener::~ApplicationFrameListener(void) {
	// Empty
}

bool ApplicationFrameListener::frameStarted(const Ogre::FrameEvent& evt) {
	mElapsed += evt.timeSinceLastFrame;

	// Notify manager of new frame
	mInputManager->capture();

	// Update entity manager
	mEntityManager->updateEntities(evt.timeSinceLastFrame);

	// Process the client
	if (mElapsed > 0.016f) {
		// Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "Client start input output process";
		mClient->process();
		// Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "Client ends input output process";
		mElapsed = 0.0f;
		// TODO Remove
		mClient->start();
	}

	// Update representation manager
	mRepresentationManager->drawGameViews(evt.timeSinceLastFrame);

	return mContinue;
}

bool ApplicationFrameListener::mouseMoved(const OIS::MouseEvent & e) { 
	//Update the mous cursor
	mMouseVisual.updatePosition(e.state.X.abs, e.state.Y.abs);
	//Update GUI elements
	mGUIManager->mouseMoved(e);
	return true; 
}

bool ApplicationFrameListener::mousePressed(const OIS::MouseEvent & e, OIS::MouseButtonID id) { 
	// Switch light on and off
	Ogre::Light * light = mSceneMgr->getLight("Light1");
	switch (id) {
	case OIS::MB_Left:
		light->setVisible(!light->isVisible());
		break;
	default:
		break;
	}

	//Update GUI elements
	mGUIManager->mousePressed(e, id);
	return true;
}

bool ApplicationFrameListener::mouseReleased(const OIS::MouseEvent & e, OIS::MouseButtonID id) { 
	//Update GUI elements
	mGUIManager->mouseReleased(e, id);
	return true;
}

bool ApplicationFrameListener::keyPressed(const OIS::KeyEvent & e) { 
	OIS::Keyboard * keyboard = InputManager::getSingletonPtr()->getKeyboard();

	switch (e.key) {
	case OIS::KC_ESCAPE:
	case OIS::KC_LMENU:
	case OIS::KC_RMENU:
	case OIS::KC_F4:
		// Check whether right combinations are pressed concurrently
		if (keyboard->isKeyDown(OIS::KC_ESCAPE) || 
			(keyboard->isKeyDown(OIS::KC_LMENU) && keyboard->isKeyDown(OIS::KC_RMENU) && keyboard->isKeyDown(OIS::KC_F4))) {
			// Stop rendering
			mContinue = false;			
		}

		break;
	default:
		// Do nothing
		break;
	}
	
	//Update GUI elements
	mGUIManager->keyPressed(e);

	// Succes
	return true; 
}

bool ApplicationFrameListener::keyReleased(const OIS::KeyEvent & e) { 
	// Succes
	//Update GUI elements
	mGUIManager->keyReleased(e);
	return true; 
}

}