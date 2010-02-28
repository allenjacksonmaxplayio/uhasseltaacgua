#include "RaceCamera.h"
#include <OgreLogManager.h>

namespace HovUni {

RaceCamera::RaceCamera(Ogre::SceneManager * sceneMgr, int ID) : mSceneMgr(sceneMgr), mID(ID), mCurrCamViewpoint(ThirdPerson) {
	// Create camera for this game view
	mCamera = mSceneMgr->createCamera("Camera" + mID);
	mCamera->setNearClipDistance(5);

	// Create 3rd person view camera
	m3rdPersonViewpointNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mCamera->getName() + "3rdPersonNode", Ogre::Vector3(0, 200, 400));
	m3rdPersonViewpointNode = m3rdPersonViewpointNode->createChildSceneNode(m3rdPersonViewpointNode->getName() + "Pitch");

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

	// Create camera controllers
	mFreeroamCameraController = new FreeroamCameraController();
	mObjectTrackCameraController = new ObjectTrackCameraController();

	// Set default camera and controller
	mActiveViewpointNode = m3rdPersonViewpointNode;
	mActiveViewpointNode->attachObject(mCamera);
	mCurrCamViewpoint = ThirdPerson;
}

RaceCamera::~RaceCamera() {
	// Delete camera controller
	delete mFreeroamCameraController;
	mFreeroamCameraController = 0;

	// Unregister controls
	mInputManager->removeKeyListener("RaceCamera");
}

bool RaceCamera::keyPressed(const OIS::KeyEvent & e) { 
	// TODO Allow key manager to set keys for the cameras
	// TODO Set the camera controller
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
	default:
		// Do nothing
		break;
	}
	
	// Succes
	return true; 
}

bool RaceCamera::keyReleased(const OIS::KeyEvent & e) { 
	return true; 
}

void RaceCamera::update(Ogre::Real timeSinceLastFrame) {
	Ogre::Vector3 positionCam;
	switch (mCurrCamViewpoint) {
	case ThirdPerson:
		// Determine position camera
		positionCam = mObjectTrackCameraController->getPosition() - (mObjectTrackCameraController->getDirection() * 30);
		positionCam.y = 50;

		// Set position and direction to look at
		mActiveViewpointNode->setPosition(positionCam);
		mActiveViewpointNode->lookAt(mObjectTrackCameraController->getPosition() + Ogre::Vector3(0.0, 0.0, -100.0), Ogre::Node::TS_WORLD);

		break;
	case FirstPerson:
		// Determine position camera
		positionCam = mObjectTrackCameraController->getPosition() - Ogre::Vector3(0.0, 0.0, 100.0);
		positionCam.y = 20;

		// Set position and direction to look at
		mActiveViewpointNode->setPosition(positionCam);
		// TODO This looks at a random point for now
		//mActiveViewpointNode->lookAt(positionCam + mObjectTrackCameraController->getDirection(), Ogre::Node::TS_WORLD);

		break;
	case RearView:
		// TODO Set rear view
		break;
	case FreeRoam:
		// Get input from free roaming controller and apply
		mActiveViewpointNode->translate(mFreeroamCameraController->getDirection() * (timeSinceLastFrame * 100), Ogre::Node::TS_LOCAL);
		mActiveViewpointNode->yaw(mFreeroamCameraController->getYaw(), Ogre::Node::TS_WORLD);
		mActiveViewpointNode->pitch(mFreeroamCameraController->getPitch(), Ogre::Node::TS_LOCAL);
		break;
	default:
		// Impossible
		break;
	}
}

}