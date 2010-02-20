#ifndef APPLICATIONFRAMELISTENER_H_
#define APPLICATIONFRAMELISTENER_H_

#include "ExampleApplication.h"
#include "EntityManager.h"
#include "InputManager.h"
#include "RepresentationManager.h"

namespace HovUni {

/**
 * Listens to the application frame to forward key and mouse controls.
 *
 * @author Kristof Overdulve
 */
class ApplicationFrameListener : public ExampleFrameListener, public OIS::MouseListener, public OIS::KeyListener {

protected:
	/** The rotation constant */
	Real mRotate;				

	/** The movement constant */
	Real mMove;					

	/** The scene manager */
	SceneManager * mSceneMgr;

	/** The camera node */
	SceneNode * mCamNode;

	/** Whether to continue rendering or not */
	bool mContinue;	

	/** The direction to move in */
	Vector3 mDirection;	

	EntityManager * mEntityManager;
	RepresentationManager * mRepresentationManager;
	InputManager * mInputManager;

public:

	/**
	 * Constructor.
	 */
	ApplicationFrameListener(RenderWindow * win, Camera * cam, SceneManager * sceneMgr, EntityManager * entityMgr,
							 RepresentationManager * reprMgr, InputManager * inputMgr);

	/**
	 * Destructor.
	 */
	virtual ~ApplicationFrameListener(void);

	/**
	 * @see FrameListener::frameStarted().
	 */
	bool frameStarted(const FrameEvent & evt);

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

#endif

}