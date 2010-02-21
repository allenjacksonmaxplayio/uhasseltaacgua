#include "ApplicationFrameListener.h"

namespace HovUni {

ApplicationFrameListener::ApplicationFrameListener(Ogre::SceneManager * sceneMgr, EntityManager * entityMgr, 
												   RepresentationManager * reprMgr, InputManager * inputMgr)
		: mSceneMgr(sceneMgr), mEntityManager(entityMgr), mRepresentationManager(reprMgr), mInputManager(inputMgr), 
		mRotate(0.13f), mMove(250), mContinue(true), mDirection(Ogre::Vector3::ZERO) {
	// Register this class with input manager
	mInputManager->addKeyListener(this, "ApplicationFrameListener");
	mInputManager->addMouseListener(this, "ApplicationFrameListener");
}

ApplicationFrameListener::~ApplicationFrameListener(void) {
	// Empty
}

bool ApplicationFrameListener::frameStarted(const Ogre::FrameEvent& evt) {
	// Notify manager of new frame
	mInputManager->capture();

	//Ogre::Log * log = Ogre::LogManager::getSingletonPtr()->getLog("applicationframelistener.log");
	//log->logMessage("Frame started");
	
	// Perform camera movement
	//mSceneMgr->getCamera("CamView1")->getParentSceneNode()->translate(mDirection * evt.timeSinceLastFrame, Node::TS_LOCAL);

	// Update entity manager
	mEntityManager->updateEntities(evt.timeSinceLastFrame);

	// Update representation manager
	mRepresentationManager->drawGameViews();

	return mContinue;
}

bool ApplicationFrameListener::mouseMoved(const OIS::MouseEvent & e) { 
	// Handle mouse movements of camera
	// TODO 
	/*
	if (e.state.buttonDown(OIS::MB_Right)) {
		Ogre::SceneNode * camNode = mSceneMgr->getCamera("Camera")->getParentSceneNode();
		camNode->yaw(Ogre::Degree(-mRotate * mMouse->getMouseState().X.rel), Node::TS_WORLD);
		camNode->pitch(Ogre::Degree(-mRotate * mMouse->getMouseState().Y.rel), Node::TS_LOCAL);
	}
	*/

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
	//Ogre::Log * log = Ogre::LogManager::getSingletonPtr()->getLog("applicationframelistener.log");
	//log->logMessage("Key pressed: " + e.key);

	// TODO Fix
//	Ogre::Camera * cam = mSceneMgr->getCamera("CamView1");
	switch (e.key) {
	case OIS::KC_ESCAPE:
		// Stop rendering
		mContinue = false;
		break;
	case OIS::KC_1:
		// Switch to camera 1
//		cam->getParentSceneNode()->detachObject(cam);
//		mSceneMgr->getSceneNode("CamNode1")->attachObject(cam);
		break;
	case OIS::KC_2:
		// Switch to camera 2
//		cam->getParentSceneNode()->detachObject(cam);
//		mSceneMgr->getSceneNode("CamNode2")->attachObject(cam);
		break;
	case OIS::KC_W:
		// Go further on z axis
		mDirection.z -= mMove;
		break;
	case OIS::KC_S:
		// Go back on z axis
		mDirection.z += mMove;
		break;
	case OIS::KC_A:
		// Go left
		mDirection.x -= mMove;
		break;
	case OIS::KC_D:
		// Go right
		mDirection.x += mMove;
		break;
	case OIS::KC_PGUP:
	case OIS::KC_Q:
		// Go up
		mDirection.y += mMove;
		break;
	case OIS::KC_PGDOWN:
	case OIS::KC_E:
		// Go down
		mDirection.y -= mMove;
		break;
	default:
		// Do nothing
		break;
	}
	
	// Succes
	return true; 
}

bool ApplicationFrameListener::keyReleased(const OIS::KeyEvent & e) { 
	// Clear movement
	switch (e.key) {
	case OIS::KC_UP:
	case OIS::KC_W:
	case OIS::KC_DOWN:
	case OIS::KC_S:
		// Clear z-axis movement
		mDirection.z = 0;
		break;
	case OIS::KC_LEFT:
	case OIS::KC_A:
	case OIS::KC_RIGHT:
	case OIS::KC_D:
		// Clear x-axis movement
		mDirection.x = 0;
		break;
	case OIS::KC_PGUP:
	case OIS::KC_Q:
	case OIS::KC_PGDOWN:
	case OIS::KC_E:
		// Clear y-axis movement
		mDirection.y = 0;
		break;
	default:
		// Do nothing
		break;
	}

	// Succes
	return true; 
}

}