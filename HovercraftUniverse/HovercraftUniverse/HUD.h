#ifndef HUD_H_
#define HUD_H_

#include <OverlayContainer.h>

#include "Chat.h"
#include "Direction.h"
#include "Position.h"
#include "Speedometer.h"
#include <tinyxml/tinyxml.h>

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

	/** Direction arrow */
	Direction* mDirection;

	/** Position indicator */
	Position* mPosition;

	/** Chat widget */
	Chat* mChat;

	/** Indicates whether the HUD should be activated */
	bool mIsActivated;

	/** Helper data structure */
	struct ComponentData {
		Ogre::String mName;
		Ogre::String mFilename;
		Hikari::Position mPosition;
		int mWidth;
		bool mWidthP;
		int mHeight;
		bool mHeightP;
	};

public:

	/**
	 * Constructor.
	 */
	HUD(TiXmlElement* HUDConfig);

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

private:
	void buildComponents(TiXmlElement* HUDConfig, std::vector<ComponentData*>& components, std::vector<ComponentData*>& percentageComponents );

	int fixPercentageSize(bool width, std::vector<ComponentData*>& components, int percentage, Hikari::Position pos);
};

}

#endif