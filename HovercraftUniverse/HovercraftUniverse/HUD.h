#ifndef HUD_H_
#define HUD_H_

namespace HovUni {

/**
 * The HUD is a 2D display that overlays the 3D scene to a player. It contains useful information
 * about the game state and/or provides controls that the player can use.
 *
 * @author Kristof Overdulve
 */
class HUD {
public:

	/**
	 * Constructor.
	 */
	HUD();

	/**
	 * Destructor.
	 */
	virtual ~HUD();

	/**
	 * Draws the HUD
	 */
	void draw();

};

}

#endif