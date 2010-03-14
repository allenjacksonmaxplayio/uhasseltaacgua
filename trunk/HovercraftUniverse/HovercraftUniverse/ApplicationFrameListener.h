#ifndef APPLICATIONFRAMELISTENER_H_
#define APPLICATIONFRAMELISTENER_H_

#include <OgreFrameListener.h>
#include "EntityManager.h"
//#include <GUIManager.h> //Don't activate, gives strage errors...
#include "InputManager.h"
#include "RepresentationManager.h"
#include "ClientCore.h"
#include "ServerCore.h"

namespace HovUni {

/**
 * Listens to the application frame to forward key and mouse controls.
 *
 * @author Kristof Overdulve
 */
class ApplicationFrameListener : public Ogre::FrameListener, public OIS::MouseListener, public OIS::KeyListener {

protected:
	/** The rotation constant */
	Ogre::Real mRotate;				

	/** The movement constant */
	Ogre::Real mMove;					

	/** The scene manager */
	Ogre::SceneManager * mSceneMgr;

	/** Whether to continue rendering or not */
	bool mContinue;	

	/** The direction to move in */
	Ogre::Vector3 mDirection;	

	/** Pointer tot he GUI Manager */
	GUIManager* mGUIManager;

	EntityManager * mEntityManager;
	RepresentationManager * mRepresentationManager;
	InputManager * mInputManager;
	ServerCore* mServer;
	ClientCore* mClient;
	float mElapsed;

public:

	/**
	 * Constructor.
	 */
	ApplicationFrameListener(Ogre::SceneManager * sceneMgr, EntityManager * entityMgr,
							 RepresentationManager * reprMgr, InputManager * inputMgr, 
							 ClientCore* client);

	/**
	 * Destructor.
	 */
	virtual ~ApplicationFrameListener(void);

	/**
	 * @see FrameListener::frameStarted().
	 */
	bool frameStarted(const Ogre::FrameEvent & evt);

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

};

}

#endif