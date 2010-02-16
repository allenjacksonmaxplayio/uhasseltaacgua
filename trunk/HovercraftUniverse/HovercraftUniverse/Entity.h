#ifndef ENTITY_H_
#define ENTITY_H_

#include "Controller.h"
#include <OgreVector3.h>

namespace HovUni {

/**
 * An entity is an object in the game world that has a game state. This state can be modified by the 
 * interaction of players with the game.
 *
 * @author Kristof Overdulve
 */
class Entity {
protected:

	/** The position of the entity in the world */
	Ogre::Vector3 mPosition;

	/** The orientation of the entity in the world */
	Ogre::Vector3 mOrientation;

	/** The controller that the entity polls to change state */
	Controller * mController;

public:

	/**
	 * Constructor.
	 *
	 * @param position the initial position of the entity
	 * @param orientation the initial orientation of the entity
	 * @param controller the controller of the entity
	 */
	Entity(Ogre::Vector3 position, Ogre::Vector3 orientation, Controller * controller);

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
	 */
	void update();

protected:

	/**
	 * Polls the controller for its current state and processes actions accordingly.
	 */
	void processController();

};

}

#endif