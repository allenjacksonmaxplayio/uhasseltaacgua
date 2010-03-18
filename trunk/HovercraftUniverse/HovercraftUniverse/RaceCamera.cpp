#include "RaceCamera.h"
#include <OgreLogManager.h>

namespace HovUni {

RaceCamera::RaceCamera(Ogre::SceneManager * sceneMgr, int ID) : mSceneMgr(sceneMgr), mID(ID), mCurrCamViewpoint(ThirdPerson) {
	// Create camera for this game view
	mCamera = mSceneMgr->createCamera("Camera" + mID);
	mCamera->setNearClipDistance(5);

	// Create 3rd person view camera
	m3rdPersonViewpointNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mCamera->getName() + "3rdPersonNode");
	m3rdPersonViewpointNode = m3rdPersonViewpointNode->createChildSceneNode(m3rdPersonViewpointNode->getName() + "Pitch");

	// Create 1st person view camera
	m1stPersonViewpointNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mCamera->getName() + "1stPersonNode", 
		Ogre::Vector3(0, 20, -40));
	m1stPersonViewpointNode = m1stPersonViewpointNode->createChildSceneNode(m1stPersonViewpointNode->getName() + "Pitch");

	// Create rear view camera
	mRearViewpointNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mCamera->getName() + "RearPersonNode", 
		Ogre::Vector3(0, 20, -40));
	//mRearViewpointNode->yaw(Ogre::Degree(180));
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

void RaceCamera::setFreeroam(Ogre::Vector3 pos, Ogre::Quaternion orientation) {
	Ogre::LogManager::getSingletonPtr()->getDefaultLog()->stream() << "Position is now: " << pos << "\n";
	mFreeRoamViewpointNode->setPosition(pos);
	mFreeRoamViewpointNode->setOrientation(orientation);
}

void RaceCamera::setFreeroam(Ogre::Vector3 pos, Ogre::Quaternion orientation, Ogre::Vector3 dir) {
	setFreeroam(pos, orientation);
	mFreeRoamViewpointNode->setDirection(dir);
}

bool RaceCamera::keyPressed(const OIS::KeyEvent & e) { 
	ControllerActionType action = mInputManager->getKeyManager()->getAction(e.key);
	// TODO Set the camera controller
	switch (action) {
	case CHANGECAMERA:
		// Switch to next camera
		if (mCurrCamViewpoint == FreeRoam) {
			mCurrCamViewpoint = ThirdPerson;
		} else {
			mCurrCamViewpoint = CameraViewpoint(mCurrCamViewpoint + 1);
		}
		break;
	case THIRD_PERSON_CAMERA:
		// Switch to 3rd person
		mCurrCamViewpoint = ThirdPerson;
		break;
	case FIRST_PERSON_CAMERA:
		// Switch to 1st person
		mCurrCamViewpoint = FirstPerson;
		break;
	case REAR_VIEW_CAMERA:
		// Switch to rear view
		mCurrCamViewpoint = RearView;
		break;
	case FREE_CAMERA:
		// Switch to free roaming
		mCurrCamViewpoint = FreeRoam;
		break;
	default:
		// Do nothing
		break;
	}

	mActiveViewpointNode->detachObject(mCamera);
	if (mCurrCamViewpoint == ThirdPerson) {
		mActiveViewpointNode = m3rdPersonViewpointNode;
	} else if (mCurrCamViewpoint == FirstPerson) {
		mActiveViewpointNode = m1stPersonViewpointNode;
	} else if (mCurrCamViewpoint == RearView) {
		mActiveViewpointNode = mRearViewpointNode;
	} else if (mCurrCamViewpoint == FreeRoam) {
		mActiveViewpointNode = mFreeRoamViewpointNode;
	}
	mActiveViewpointNode->attachObject(mCamera);

	// Succes
	return true; 
}

bool RaceCamera::keyReleased(const OIS::KeyEvent & e) { 
	return true; 
}

void RaceCamera::update(Ogre::Real timeSinceLastFrame) {
	Ogre::Vector3 positionCam;
	Ogre::Quaternion back;

	switch (mCurrCamViewpoint) {
	case ThirdPerson:
		// Determine position camera
		positionCam = mObjectTrackCameraController->getPosition() - (mObjectTrackCameraController->getDirection() * 40) + (mObjectTrackCameraController->getUpVector() * 20);
		
		// Set position and direction to look at
		mActiveViewpointNode->setPosition(positionCam);
		mActiveViewpointNode->setOrientation(mObjectTrackCameraController->getOrientation());
		//turn the camera slightly to the tracked entity
		mActiveViewpointNode->pitch(Ogre::Degree(-20.0f), Ogre::Node::TS_LOCAL);
		
		break;
	case FirstPerson:
		// Determine position camera
		positionCam = mObjectTrackCameraController->getPosition() + (mObjectTrackCameraController->getDirection() * 10);

		// Set position and direction to look at
		mActiveViewpointNode->setPosition(positionCam);
		mActiveViewpointNode->setOrientation(mObjectTrackCameraController->getOrientation());

		break;
	case RearView:
		// Determine position camera
		positionCam = mObjectTrackCameraController->getPosition() - (mObjectTrackCameraController->getDirection() * 10);
		
		// Set position and direction to look at
		mActiveViewpointNode->setPosition(positionCam);
		// turn the camera 180 degrees around the up vector
		back = Ogre::Quaternion(Ogre::Degree(180), mObjectTrackCameraController->getUpVector());
		mActiveViewpointNode->setOrientation(back * mObjectTrackCameraController->getOrientation());

		break;
	case FreeRoam:
		// Get input from free roaming controller and apply
		Ogre::LogManager::getSingletonPtr()->getDefaultLog()->stream() << "Update: " << mActiveViewpointNode->getPosition() << "\n";
		mActiveViewpointNode->translate(mFreeroamCameraController->getDirection() * (timeSinceLastFrame * 10), Ogre::Node::TS_LOCAL);
		mActiveViewpointNode->yaw(mFreeroamCameraController->getYaw(), Ogre::Node::TS_WORLD);
		mActiveViewpointNode->pitch(mFreeroamCameraController->getPitch(), Ogre::Node::TS_LOCAL);
		break;
	default:
		// Impossible
		break;
	}
}

}