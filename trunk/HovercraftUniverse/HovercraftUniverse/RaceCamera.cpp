#include "RaceCamera.h"

namespace HovUni {

RaceCamera::RaceCamera(Ogre::SceneManager * sceneMgr, int ID) : mSceneMgr(sceneMgr), mID(ID), mCurrCamViewpoint(ThirdPerson) {
	// Create camera for this game view
	mCamera = mSceneMgr->createCamera("Camera" + mID);
	mCamera->setNearClipDistance(5);

	// Create 3rd person view camera
	m3rdPersonViewpointNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mCamera->getName() + "3rdPersonNode", 
		Ogre::Vector3(0, 200, 400));
	m3rdPersonViewpointNode = m3rdPersonViewpointNode->createChildSceneNode(m3rdPersonViewpointNode->getName() + "Pitch");
	mActiveViewpointNode = m3rdPersonViewpointNode;
	mActiveViewpointNode->attachObject(mCamera);

	// Create 1st person view camera
	m1stPersonViewpointNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mCamera->getName() + "1stPersonNode", 
		Ogre::Vector3(0, 20, -40));
	m1stPersonViewpointNode = m1stPersonViewpointNode->createChildSceneNode(m1stPersonViewpointNode->getName() + "Pitch");

	// Create rear view camera
	mRearViewpointNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mCamera->getName() + "RearPersonNode", 
		Ogre::Vector3(0, 20, -40));
	mRearViewpointNode->yaw(Ogre::Degree(180));
	mRearViewpointNode = mRearViewpointNode->createChildSceneNode(mRearViewpointNode->getName() + "Pitch");

	// Create free roam camera
	mFreeRoamViewpointNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mCamera->getName() + "FreeRoamNode", 
		Ogre::Vector3(-400, 200, 400));
	mFreeRoamViewpointNode->yaw(Ogre::Degree(-45));
	mFreeRoamViewpointNode = mFreeRoamViewpointNode->createChildSceneNode(mFreeRoamViewpointNode->getName() + "Pitch");

	// Fetch input manager object and register controls
	mInputManager = InputManager::getSingletonPtr();
	mInputManager->addKeyListener(this, "RaceCamera");
	mInputManager->addMouseListener(this, "RaceCamera");
}

RaceCamera::~RaceCamera() {
	// Empty
}

bool RaceCamera::mouseMoved(const OIS::MouseEvent & e) { 
	// Handle mouse movements of camera
	if ((e.state.buttonDown(OIS::MB_Right)) && (mCurrCamViewpoint == FreeRoam)) {
		// TODO 
		//mActiveViewpointNode->yaw(Ogre::Degree(-mRotate * mMouse->getMouseState().X.rel), Node::TS_WORLD);
		//mActiveViewpointNode->pitch(Ogre::Degree(-mRotate * mMouse->getMouseState().Y.rel), Node::TS_LOCAL);
	}

	return true; 
}

bool RaceCamera::mousePressed(const OIS::MouseEvent & e, OIS::MouseButtonID id) { 
	return true;
}
bool RaceCamera::mouseReleased(const OIS::MouseEvent & e, OIS::MouseButtonID id) { 
	return true; 
}

bool RaceCamera::keyPressed(const OIS::KeyEvent & e) { 
	// TODO Allow key manager to set keys for the cameras
	switch (e.key) {
	case OIS::KC_1:
		// Switch to 3rd person
		mActiveViewpointNode->detachObject(mCamera);
		mActiveViewpointNode = m3rdPersonViewpointNode;
		mActiveViewpointNode->attachObject(mCamera);
		mCurrCamViewpoint = ThirdPerson;
		break;
	case OIS::KC_2:
		// Switch to 1st person
		mActiveViewpointNode->detachObject(mCamera);
		mActiveViewpointNode = m1stPersonViewpointNode;
		mActiveViewpointNode->attachObject(mCamera);
		mCurrCamViewpoint = FirstPerson;
		break;
	case OIS::KC_3:
		// Switch to rear view
		mActiveViewpointNode->detachObject(mCamera);
		mActiveViewpointNode = mRearViewpointNode;
		mActiveViewpointNode->attachObject(mCamera);
		mCurrCamViewpoint = RearView;
		break;
	case OIS::KC_4:
		// Switch to free roaming
		mActiveViewpointNode->detachObject(mCamera);
		mActiveViewpointNode = mFreeRoamViewpointNode;
		mActiveViewpointNode->attachObject(mCamera);
		mCurrCamViewpoint = FreeRoam;
		break;
// TODO Camera movements
/*
	case OIS::KC_UP:
	case OIS::KC_W:
		// Go further on z axis
		mDirection.z -= mMove;
		break;
	case OIS::KC_DOWN:
	case OIS::KC_S:
		// Go back on z axis
		mDirection.z += mMove;
		break;
	case OIS::KC_LEFT:
	case OIS::KC_A:
		// Go left
		mDirection.x -= mMove;
		break;
	case OIS::KC_RIGHT:
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
*/
	default:
		// Do nothing
		break;
	}
	
	// Succes
	return true; 
}

bool RaceCamera::keyReleased(const OIS::KeyEvent & e) { 
	// Clear movement
	// TODO Clear
	/*
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
	*/

	// Succes
	return true; 
}

}