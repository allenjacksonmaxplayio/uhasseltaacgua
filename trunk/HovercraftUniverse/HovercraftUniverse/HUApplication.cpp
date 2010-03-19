#include "HUApplication.h"
#include <HovSound.h>

namespace HovUni {

	HUApplication::HUApplication() : Application("Hovercraft Universe", "HovercraftUniverse.ini") { 
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

	void HUApplication::customSceneSetup() {
		// Empty
	}

}