#ifndef RACECAMERA_H_
#define RACECAMERA_H_

#include <OgreSceneManager.h>
#include "InputManager.h"

namespace HovUni {

/**
 * Defines a racing camera to use in racing games. This camera has a 3rd person front view, a first person front view,
 * a rear view and a free roaming view.
 *
 * @author Kristof Overdulve
 */
class RaceCamera : public OIS::KeyListener, public OIS::MouseListener {
private:

	/** The Ogre scene manager */
	Ogre::SceneManager * mSceneMgr;

	/** The camera of the view */
	Ogre::Camera * mCamera;

	/** The ID of the camera */
	int mID;

	/** The 3d person viewpoint of the camera */
	Ogre::SceneNode * m3rdPersonViewpointNode;

	/** The first person viewpoint of the camera */
	Ogre::SceneNode * m1stPersonViewpointNode;

	/** The rear viewpoint of the camera */
	Ogre::SceneNode * mRearViewpointNode;

	/** The free roaming viewpoint of the camera */
	Ogre::SceneNode * mFreeRoamViewpointNode;

	/** The currently active camera viewpoint */
	Ogre::SceneNode * mActiveViewpointNode;

	/**
	 * The camera viewpoints
	 */
	enum CameraViewpoint {
		ThirdPerson,
		FirstPerson,
		RearView,
		FreeRoam
	};

	/** The camera currently active */
	CameraViewpoint mCurrCamViewpoint;

	/** The input manager */
	InputManager * mInputManager;


public:

	/**
	 * Constructor.
	 *
	 * @param sceneMgr the Ogre scene manager
	 * @param the ID of the camera created here
	 */
	RaceCamera(Ogre::SceneManager * sceneMgr, int ID);

	/**
	 * Destructor.
	 */
	~RaceCamera(void);

	/**
	 * @see MouseListener::mouseMoved().
	 */
	bool mouseMoved(const OIS::MouseEvent & e);

	/**
	 * @see MouseListener::mousePressed().
	 */
	bool mousePressed(const OIS::MouseEvent & e, OIS::MouseButtonID id);

	/**
	 * @see MouseListener::mouseReleased().
	 */
	bool mouseReleased(const OIS::MouseEvent & e, OIS::MouseButtonID id);

	/**
	 * @see KeyListener::keyPressed().
	 */
	bool keyPressed(const OIS::KeyEvent & e);

	/**
	 * @see KeyListener::keyReleased().
	 */
	bool keyReleased(const OIS::KeyEvent & e);

	/**
	 * Returns the camera associated with this game view.
	 *
	 * @return the camera
	 */
	Ogre::Camera * getCamera() { return mCamera; }

};

}

#endif