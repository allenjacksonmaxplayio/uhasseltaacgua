#ifndef HUD_H_
#define HUD_H_

#include <OverlayContainer.h>

#include "Speedometer.h"

namespace HovUni {

/**
 * The HUD is a 2D display that overlays the 3D scene to a player. It contains useful information
 * about the game state and/or provides controls that the player can use.
 *
 * @author Kristof Overdulve & Nick De Frangh
 */
class HUD : public OverlayContainer {
private:

	/** The meter indicating the speed of the racer */
	Speedometer* mSpeedometer;

	/** Indicates whether the HUD should be activated */
	bool mIsActivated;

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
	void activate();

	/**
	 * Hides the HUD
	 */
	void deactivate();

	/** 
	 * Indicates whether the HUD is visible or hidden.
	 *
	 * @return true if the HUD is visible and false if hidden
	 */
	bool isActivated() { return mIsActivated; }

};

}

#endif