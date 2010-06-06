#ifndef _BASICVIEW_H
#define _BASICVIEW_H

#include <OgreRoot.h>
#include <OgreCamera.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>

namespace HovUni {

/**
 * A basic view which contains a viewport and a camera. This view is meant to be
 * expanded with more functionality.
 *
 * @author Nick De Frangh
 */
class BasicView {
protected:
	/** The Ogre render window */
	Ogre::RenderWindow* mRenderWindow;

	/** The Ogre scene manager */
	Ogre::SceneManager* mSceneManager;

	/** The name of this view */
	Ogre::String mViewName;

	/** The Ogre camera of the view */
	Ogre::Camera * mOgreCamera;

	/** A viewport associated with this view */
	Ogre::Viewport* mViewport;

public:

	/**
	 * Constructor.
	 *
	 * @param hud the hud to draw for the player
	 * @param sceneMgr the Ogre scene manager
	 */
	BasicView(Ogre::RenderWindow* renderWindow, Ogre::SceneManager* sceneManager, const Ogre::String& name);

	/**
	 * Destructor.
	 */
	virtual ~BasicView();

	/**
	 * Draw the game view.
	 *
	 * @param timeSinceLastFrame the time since the last frame
	 */
	void draw(Ogre::Real timeSinceLastFrame);

	/**
	 * Returns the scene manager associated with this view.
	 *
	 * @return the scenemanager
	 */
	Ogre::SceneManager* getSceneManager() { return mSceneManager; }

	/**
	 * Returns the name of this view.
	 *
	 * @return the name
	 */
	Ogre::String getViewName() { return mViewName; }

	/**
	 * Returns the camera associated with this view.
	 *
	 * @return the camera
	 */
	Ogre::Camera* getCamera() { return mOgreCamera; }

	/**
	 * Returns the viewport associated with this view.
	 *
	 * @return the viewport
	 */
	Ogre::Viewport* getViewport() { return mViewport; }

};

}

#endif //_BASICVIEW_H