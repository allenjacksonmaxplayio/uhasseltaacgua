#ifndef REPRESENTATIONMANAGER_H_
#define REPRESENTATIONMANAGER_H_

#include <vector>
#include "EntityRepresentation.h"
#include "GameView.h"

using namespace std;

namespace HovUni {

/**
 * The representation manager keeps a list of entity representations in a spatial hierarchy
 * suitable for quick visibility determination.
 *
 * @author Kristof Overdulve
 */
class RepresentationManager {
protected:

	/** The list of entity representations to update */
	vector<EntityRepresentation *> mEntityRepresentations;

	/** The list of game views to draw */
	vector<GameView *> mGameViews;

public:

	/**
	 * Constructor.
	 */
	RepresentationManager();

	/**
	 * Destructor.
	 */
	virtual ~RepresentationManager();

	/**
	 * Adds a new entity representation to the manager.
	 *
	 * @param entityRep the entity representation to update
	 */
	void addEntityRepresentation(EntityRepresentation * entityRep);

	/**
	 * Removes the given entity representation from the manager.
	 *
	 * @param entityRep the entity representation to remove
	 */
	void removeEntityRepresentation();

	/**
	 * Adds a game view to draw in each frame.
	 *
	 * @param gameView the game view to draw in each frame
	 */
	void addGameView(GameView * gameView);

protected:

	/**
	 * Updates the representations at frame rate.
	 */
	void updateRepresentations();

	/**
	 * Draw all the game views.
	 */
	void drawGameViews();

};

}

#endif