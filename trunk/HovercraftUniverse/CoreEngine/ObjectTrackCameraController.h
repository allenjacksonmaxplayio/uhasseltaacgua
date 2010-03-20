#ifndef OBJECTTRACKCAMERACONTROLLER_H_
#define OBJECTTRACKCAMERACONTROLLER_H_

#include "Controller.h"
#include "Entity.h"
#include <OgreVector3.h>
#include "InputManager.h"
#include <vector>

namespace HovUni {

/**
 * Object tracking Camera controller interface that follows an object.
 *
 * @author Kristof Overdulve
 */
class ObjectTrackCameraController : public Controller {
private:

	/** The entity that this camera tracks */
	Entity * mEntity;

public:

	/**
	 * Constructor.
	 */
	ObjectTrackCameraController();

	/**
	 * Destructor
	 */
	virtual ~ObjectTrackCameraController();

	/**
	 * @see Controller::getEvents()
	 */
	virtual std::vector<ControllerEvent*> getEvents();

	/**
	 * Tells the position of the object that is being tracked.
	 *
	 * @return the position
	 */
	virtual Ogre::Vector3 getPosition();

	/**
	 * Tells the direction in which the object that is being tracked is moving.
	 *
	 * @return the direction
	 */
	virtual Ogre::Vector3 getDirection();

	/**
	 * Tells the orientaion of the object that is being tracked.
	 *
	 * @return the orientation
	 */
	virtual Ogre::Quaternion getOrientation();

	/**
	 * Tells the up vector of the object that is being tracked.
	 *
	 * @return the up vector
	 */
	virtual Ogre::Vector3 getUpVector();

private:

	/**
	 * Initializes the entity that is being tracked. We do not perform this in the constructor, since the
	 * entity might not have been initialized by then yet. Therefore, we delay the fetching until absolutely
	 * needed.
	 */
	void initialize();

};

}

#endif
