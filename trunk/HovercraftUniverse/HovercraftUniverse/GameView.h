#ifndef GAMEVIEW_H_
#define GAMEVIEW_H_

#include <vector>
#include <OgreCamera.h>
#include <OgreSceneManager.h>
#include "EntityRepresentation.h"
#include "HUD.h"
#include "RaceCamera.h"

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
	std::vector<EntityRepresentation *> mEntityRepresentations;

	/** The HUD to draw as an overlay */
	HUD * mHUD;

	/** The camera of the view */
	RaceCamera * mRaceCam;

	/** The Ogre scene manager */
	Ogre::SceneManager * mSceneMgr;

	/** The global ID of the game view */
	static int mGlobalID;

	/** Our ID */
	int mID;

public:

	/**
	 * Constructor.
	 *
	 * @param hud the hud to draw for the player
	 * @param sceneMgr the Ogre scene manager
	 */
	GameView(Ogre::SceneManager * sceneMgr);

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
	void removeEntityRepresentation(Ogre::String entityRep);

	/**
	 * Draw the game view.
	 *
	 * @param timeSinceLastFrame the time since the last frame
	 */
	void draw(Ogre::Real timeSinceLastFrame);

	/**
	 * Set a HUD on this GameView
	 *
	 * @param hud The hud you want to set.
	 */
	void setHud(HUD* hud);

	/**
	 * Returns the camera associated with this game view.
	 *
	 * @return the camera
	 */
	RaceCamera * getCamera() { return mRaceCam; }

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