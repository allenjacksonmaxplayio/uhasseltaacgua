#include "ApplicationFrameListener.h"
#include <OgreLogManager.h>

namespace HovUni {

ApplicationFrameListener::ApplicationFrameListener(Ogre::SceneManager * sceneMgr, EntityManager * entityMgr, 
												   RepresentationManager * reprMgr, InputManager * inputMgr, 
												   ServerCore* server, ClientCore* client)
		: mSceneMgr(sceneMgr), mEntityManager(entityMgr), mRepresentationManager(reprMgr), mInputManager(inputMgr), 
		mRotate(0.13f), mMove(250), mContinue(true), mDirection(Ogre::Vector3::ZERO), mServer(server), mClient(client), mElapsed(0.0f) {
	// Register this class with input manager
	mInputManager->addKeyListener(this, "ApplicationFrameListener");
	mInputManager->addMouseListener(this, "ApplicationFrameListener");
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
		mServer->process();
		mClient->process();
		EntityManager::getServerSingletonPtr()->updateEntities(mElapsed);
		// Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "Client ends input output process";
		mElapsed = 0.0f;
	}

	// Update representation manager
	mRepresentationManager->drawGameViews(evt.timeSinceLastFrame);

	return mContinue;
}

bool ApplicationFrameListener::mouseMoved(const OIS::MouseEvent & e) { 
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

	return true;
}

bool ApplicationFrameListener::mouseReleased(const OIS::MouseEvent & e, OIS::MouseButtonID id) { 
	return true;
}

bool ApplicationFrameListener::keyPressed(const OIS::KeyEvent & e) { 
	switch (e.key) {
	case OIS::KC_ESCAPE:
		// Stop rendering
		mContinue = false;
		break;
	default:
		// Do nothing
		break;
	}
	
	// Succes
	return true; 
}

bool ApplicationFrameListener::keyReleased(const OIS::KeyEvent & e) { 
	// Succes
	return true; 
}

}