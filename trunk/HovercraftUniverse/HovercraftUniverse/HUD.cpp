#include "HUD.h"

#include "GUIManager.h"

namespace HovUni {

HUD::HUD() {
	//Initialise all the object, this list should be controllable by scripts/Configuration files
	mSpeedometer = new Speedometer("speedometer", "speedometer.swf", 360, 360, Hikari::BottomRight);
	//TODO: Should be accesible trough the overlay object itself!
	//mSpeedometer->getFlashControl()->setTransparent(true, true);

	this->addOverlay("speedometer", mSpeedometer);
}

HUD::~HUD() {
	if (mSpeedometer) {
		delete mSpeedometer;
	}
}

void HUD::activate() {
	GUIManager::getSingletonPtr()->activateOverlayContainer(this);
}

void HUD::deactivate() {
	GUIManager::getSingletonPtr()->disableOverlayContainer(this);
}

}

