#include "HUApplication.h"
#include "MainMenuState.h"
#include "ControlsReader.h"
#include <HovSound.h>

#include <OgreLogManager.h>

namespace HovUni {

ClientPreparationLoader * HUApplication::msPreparationLoader = 0;

HUApplication::HUApplication(const std::string& configINI) :
	Application("Hovercraft Universe", configINI) {
	// Empty
}

HUApplication::~HUApplication() {
	// Empty
}

void HUApplication::playMusic(SoundManager * soundMgr) {
	// Play normal background music
	soundMgr->startAmbient(MUSICCUE_HOVSOUND_BACKGROUND_NORMAL);
	soundMgr->updateListenerPosition(new Ogre::Vector3(-10.0f, 40.0f, 0.0f));
}

BasicGameState * HUApplication::getInitialGameState() {
	return new MainMenuState();
}

void HUApplication::customSceneSetup() {
	// Initialize the client preparation loader
	Ogre::LogManager::getSingleton().getDefaultLog()->stream()
			<< "[HUApplication]: Creating client preparation loader";
	msPreparationLoader = new ClientPreparationLoader();
}

void HUApplication::init() {
	Application::init();

	// read controls
	ControlsReader * controls = new ControlsReader(mInputManager->getKeyManager());
	controls->readControls();
}

}
