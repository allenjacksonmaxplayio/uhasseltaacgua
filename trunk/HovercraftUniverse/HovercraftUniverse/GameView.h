#ifndef GAMEVIEW_H_
#define GAMEVIEW_H_

#include <vector>
#include <OgreCamera.h>
#include "EntityRepresentation.h"
#include "HUD.h"

using namespace std;

namespace HovUni {

/**
 * A game view draws the world for one player. This includes keeping track of the active
 * camera, drawing all entity representations in view and the static world around it, and
 * finally drawing the HUD as a 2D overlay.
 *
 * @author Kristof Overdulve
 */
class GameView {
protected:

	/** The list of entity representations to visualize for this player */
	vector<EntityRepresentation *> mEntityRepresentations;

	/** The HUD to draw as an overlay */
	HUD * mHUD;

	/** The camera of the view */
	Ogre::Camera * mCamera;

public:

	/**
	 * Constructor.
	 *
	 * @param hud the hud to draw for the player
	 * @param camera the camera for this player view
	 */
	GameView(HUD * hud, Ogre::Camera * camera);

	/**
	 * Destructor.
	 */
	virtual ~GameView();

	/**
	 * Adds a new entity representation to the view.
	 *
	 * @param entityRep the entity representation to visualize
	 */
	void addEntityRepresentation(EntityRepresentation * entityRep);

	/**
	 * Removes the given entity representation from the view.
	 *
	 * @param entityRep the entity representation to remove
	 */
	void removeEntityRepresentation();

	/**
	 * Draw the game view.
	 */
	void draw();

protected:

	/**
	 * Draw the entity representations.
	 */
	void drawEntityRepresentations();

	/**
	 * Draw the HUD as a 2D overlay.
	 */
	void drawHUD();

};

}

#endif