#ifndef ENTITY_H_
#define ENTITY_H_

#include "Controller.h"
#include <OgreVector3.h>
#include "NetworkEntity.h"
#include "ControllerEvent.h"

namespace HovUni {

/**
 * An entity is an object in the game world that has a game state. This state can be modified by the 
 * interaction of players with the game.
 *
 * @author Kristof Overdulve
 */
class Entity: public NetworkEntity {
protected:
	
	/** The unique name of the entity */
	Ogre::String mName;

	/** The category to which this entity belongs */
	Ogre::String mCategory;

	/** The position of the entity in the world */
	Ogre::Vector3 mPosition;

	/** The orientation of the entity in the world */
	Ogre::Vector3 mOrientation;

	/** The controller that the entity polls to change state */
	Controller * mController;

	/** Whether the entity is registered to the network */
	bool mRegistered;

public:

	/**
	 * Constructor.
	 *
	 * @param name the unique name of the entity
	 * @param category the category to which this entity belongs
	 * @param position the initial position of the entity
	 * @param orientation the initial orientation of the entity
	 */
	Entity(Ogre::String name, Ogre::String category, Ogre::Vector3 position, Ogre::Vector3 orientation);

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
	void changeOrientation(Ogre::Vector3 newOrientation);

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
	 * @param timeSinceLastFrame the time that elapsed since the last frame
	 */
	void update(Ogre::Real timeSinceLastFrame);

	/**
	 * Returns the unique name of this entity.
	 *
	 * @return the unique name
	 */
	Ogre::String getName() { return mName; }

	/**
	 * Returns the category to which this entity belongs.
	 *
	 * @return the category
	 */
	Ogre::String getCategory() { return mCategory; }

	/**
	 * Returns the position of this entity.
	 *
	 * @return the position
	 */
	Ogre::Vector3 getPosition() { return mPosition; }

	/**
	 * Returns the orientation of this entity.
	 *
	 * @return the orientation
	 */
	Ogre::Vector3 getOrientation() { return mPosition; }

	/**
	 * Register the node for the network
	 *
	 * @param id the zoidcom class ID
	 * @param control the zoidcom control
	 */
	void networkRegister(ZCom_ClassID id, ZCom_Control* control);

protected:

	/**
	 * @see NetworkEntity::parseEvents(ZCom_BitStream* stream)
	 */
	void parseEvents(ZCom_BitStream* stream);

	/**
	 * Polls the controller for its current state and processes actions accordingly.
	 *
	 * @param timeSinceLastFrame the time that elapsed since the last frame
	 */
	void processController(Ogre::Real timeSinceLastFrame);

	/**
	 * Process a controller event that got processed by the controller and fire the
	 * correct callback (server, owner or others).
	 *
	 * @param event a controller event
	 */
	void processControllerEvents(ControllerEvent* event);

	/**
	 * Process a controller event at the server that got processed by the controller.  Must
	 * be overriden since this class in itself has no clue which controller properties 
	 * there are.
	 *
	 * @param event a controller event
	 */
	virtual void processControllerEventsInServer(ControllerEvent* event) = 0;

	/**
	 * Process a controller event at the owner that got processed by the controller.  Must
	 * be overriden since this class in itself has no clue which controller properties 
	 * there are.
	 *
	 * @param event a controller event
	 */
	virtual void processControllerEventsInOwner(ControllerEvent* event) = 0;

	/**
	 * Process a controller event at other clients that got processed by the controller.  Must
	 * be overriden since this class in itself has no clue which controller properties 
	 * there are.
	 *
	 * @param event a controller event
	 */
	virtual void processControllerEventsInOther(ControllerEvent* event) = 0;

};

}

#endif