#ifndef ENTITY_H_
#define ENTITY_H_

#include "Controller.h"
#include <OgreVector3.h>
#include "NetworkEntity.h"
#include "ControllerEvent.h"
#include <OgreLogManager.h>

namespace HovUni {

/**
 * An entity is an object in the game world that has a game state. This state can be modified by the 
 * interaction of players with the game.
 *
 * @author Kristof Overdulve & Olivier Berghmans
 */
class Entity: public NetworkEntity {
protected:
	
	/** The unique name of the entity */
	Ogre::String mName;

	/** The category to which this entity belongs */
	Ogre::String mCategory;

	/** The position */
	Ogre::Vector3 mPosition;

	/** The up-vector */
	Ogre::Vector3 mUpVector;

	/** The orientation of the entity in the world */
	Ogre::Quaternion mOrientation;

	/** The name of the ogre entity that represents this entity, can be empty */
	Ogre::String mOgreEntity;

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
	 * @param name of the ogre entity that represents this entity
	 * @param processInterval the mean interval between two consecutive processings (-1 for no process callbacks)
	 * @param replicators the number of replicator to be used
	 */
	Entity(Ogre::String name, Ogre::String category, bool track, Ogre::Vector3 position, Ogre::Vector3 orientation, Ogre::Vector3 upvector, Ogre::String mOgreEntity, float processInterval, unsigned short replicators );

	/**
	 * Constructor.
	 *
	 * @param name the unique name of the entity
	 * @param category the category to which this entity belongs
	 * @param track indicates that this object should be tracked by the camera
	 * @param position the initial position of the entity
	 * @param orientation the initial orientation of the entity
 	 * @param name of the ogre entity that represents this entity
	 * @param processInterval the mean interval between two consecutive processings (-1 for no process callbacks)
	 * @param replicators the number of replicator to be used
	 */
	Entity(Ogre::String name, Ogre::String category, bool track, Ogre::Vector3 position, Ogre::Quaternion orientation, Ogre::Vector3 upvector, Ogre::String mOgreEntity, float processInterval, unsigned short replicators);

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
	 * Changes the up vector to the new orientation.
	 *
	 * @param newUp is the new up vector
	 */
	void changeUpVector(Ogre::Vector3 newUp);

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
	 * Returns the up vector of this entity.
	 *
	 * @return the up vector
	 */
	Ogre::Vector3 getUpVector() const;

	/**
	 * Returns the orientation of this entity.
	 *
	 * @return the orientation
	 */
	Ogre::Vector3 getOrientation() const;

	/**
	 * Returns the unique name of the ogre entity that represents this entity,
	 * Can be empty if no such ogre entity exists.
	 *
	 * @return the name of the ogre entity
	 */
	Ogre::String getOgreEntity() const;

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

	/**
	 * @see NetworkEntity::setReplication()
	 */
	void setupReplication();

};

}

#endif