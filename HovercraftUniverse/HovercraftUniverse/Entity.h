#ifndef ENTITY_H_
#define ENTITY_H_

#include "Controller.h"
#include <OgreVector3.h>
#include "NetworkMovementEntity.h"
#include "ControllerEvent.h"
#include <OgreLogManager.h>

namespace HovUni {

/**
 * An entity is an object in the game world that has a game state. This state can be modified by the 
 * interaction of players with the game.
 *
 * @author Kristof Overdulve & Olivier Berghmans
 */
class Entity: public NetworkMovementEntity {
protected:
	
	/** The unique name of the entity */
	Ogre::String mName;

	/** The category to which this entity belongs */
	Ogre::String mCategory;

	/** The orientation of the entity in the world */
	Ogre::Quaternion mOrientation;
	//float mOrientation[3];

	/** The controller that the entity polls to change state */
	Controller * mController;

	/** The interval between two processings of the object */
	const float mProcessInterval;

	/** The time since last process of the object */
	float mProcessElapsed;

public:

	/**
	 * Constructor.
	 *
	 * @param name the unique name of the entity
	 * @param category the category to which this entity belongs
	 * @param track indicates that this object should be tracked by the camera
	 * @param position the initial position of the entity
	 * @param orientation the initial orientation of the entity
	 * @param processInterval the mean interval between two consecutive processings (-1 for no process callbacks)
	 */
	Entity(Ogre::String name, Ogre::String category, bool track, Ogre::Vector3 position, Ogre::Vector3 orientation, float processInterval);

	/**
	 * Constructor.
	 *
	 * @param name the unique name of the entity
	 * @param category the category to which this entity belongs
	 * @param track indicates that this object should be tracked by the camera
	 * @param position the initial position of the entity
	 * @param orientation the initial orientation of the entity
	 * @param processInterval the mean interval between two consecutive processings (-1 for no process callbacks)
	 */
	Entity(Ogre::String name, Ogre::String category, bool track, Ogre::Vector3 position, Ogre::Quaternion orientation, float processInterval);

	/**
	 * Destructor.
	 */
	virtual ~Entity();

	/**
	 * Changes the position to the new position.
	 *
	 * @param newPosition is the new position
	 */
	void changePosition(Ogre::Vector3 newPosition);

	/**
	 * Changes the orientation to the new orientation.
	 *
	 * @param newOrientation is the new orientation
	 */
	void changeOrientation(Ogre::Quaternion newOrientation);

	/**
	 * Sets the controller of the character. This allows for example for live migration between
	 * player controlled characters and AI controlled characters.
	 *
	 * @param controller the controller of the character
	 */
	void setController(Controller * controller);

	/**
	 * Updates the entity.
	 *
	 * @param timeSince the time that elapsed since the last update
	 */
	void update(float timeSince);

	/**
	 * Returns the unique name of this entity.
	 *
	 * @return the unique name
	 */
	Ogre::String getName() const;

	/**
	 * Returns the category to which this entity belongs.
	 *
	 * @return the category
	 */
	Ogre::String getCategory() const;

	/**
	 * Returns the position of this entity.
	 *
	 * @return the position
	 */
	Ogre::Vector3 getPosition() const;

	/**
	 * Returns the orientation of this entity.
	 *
	 * @return the orientation
	 */
	Ogre::Vector3 getOrientation() const;

	/**
	 * Returns the orientation of this entity.
	 *
	 * @return the orientation
	 */
	Ogre::Quaternion getQuaternion() const;

protected:
	/**
	 * Callback to process this entity. This allows to do entity specific processing
	 * (e.g. intermediate actions).
	 *
	 * @param timeSince the time since the last processing of the entity
	 */
	virtual void process(float timeSince) = 0;

	/**
	 * Callback to process a controller event at the server that got processed by the 
	 * controller.  Must be overriden since this class in itself has no clue which 
	 * controller properties there are.
	 *
	 * @param event a controller event
	 */
	virtual void processEventsServer(ControllerEvent* event) = 0;

	/**
	 * Callback to process a controller event at the owner that got processed by the 
	 * controller.  Must be overriden since this class in itself has no clue which 
	 * controller properties there are.
	 *
	 * @param event a controller event
	 */
	virtual void processEventsOwner(ControllerEvent* event) = 0;

	/**
	 * Callback to process a controller event at other clients that got processed by the controller.  Must
	 * be overriden since this class in itself has no clue which controller properties 
	 * there are.
	 *
	 * @param event a controller event
	 */
	virtual void processEventsOther(ControllerEvent* event) = 0;

	/**
	 * @see NetworkMovementEntity::setReplication()
	 */
	void addReplicators();

private:
	/**
	 * @see NetworkEntity::parseEvents(ZCom_BitStream* stream, float timeSince)
	 */
	void parseEvents(ZCom_BitStream* stream, float timeSince);

	/**
	 * Polls the controller for its current state and processes actions accordingly.
	 *
	 * @param timeSince the time that elapsed since the last process
	 */
	void processController(float timeSince);

	/**
	 * Process a controller event that got processed by the controller and fire the
	 * correct callback (server, owner or others).
	 *
	 * @param event a controller event
	 */
	void processControllerEvents(ControllerEvent* event);

};

}

#endif