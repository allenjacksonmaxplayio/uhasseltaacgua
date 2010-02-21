#include "HUD.h"

#include "GUIManager.h"

namespace HovUni {

HUD::HUD() {
	//Initialise all the object, this list should be controllable by scripts/Configuration files
	mSpeedometer = new Speedometer("speedometer", "speedometer.swf", 360, 360, Hikari::BottomRight);
	mSpeedometer->setBParameter(BasicOverlay::OverlayParams_B::ALPHAHACK, true);

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

