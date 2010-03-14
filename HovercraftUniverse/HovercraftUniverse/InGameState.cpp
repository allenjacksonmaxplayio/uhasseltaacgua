#include "InGameState.h"

namespace HovUni {
	InGameState::InGameState(TiXmlElement* HUDConfig) {
		mHud = new HUD(HUDConfig);
	}

	void InGameState::activate() {
		//Remove cursor
		mGUIManager->showCursor(false);
	}

	void InGameState::disable() {
		//Restore cursor
		mGUIManager->showCursor(true);
	}

	bool InGameState::frameStarted(const Ogre::FrameEvent & evt) {
		bool result = true;

		//We are using a GUI, so update it
		mGUIManager->update();

		//We have sound, update it
		mSoundManager->update();

		return result;
	}

	bool InGameState::mouseMoved(const OIS::MouseEvent & e) {
		bool result = true;

		//We are using a GUI, so update it
		result = result && mGUIManager->mouseMoved(e);

		return result;
	}

	bool InGameState::mousePressed(const OIS::MouseEvent & e, OIS::MouseButtonID id) {
		bool result = true;

		//We are using a GUI, so update it
		result = result && mGUIManager->mousePressed(e, id);
		
		return result;
	}

	bool InGameState::mouseReleased(const OIS::MouseEvent & e, OIS::MouseButtonID id) {
		bool result = true;

		//We are using a GUI, so update it
		result = result && mGUIManager->mouseReleased(e, id);
		
		return result;
	}

	bool InGameState::keyPressed(const OIS::KeyEvent & e) {
		bool result = true;

		//We are using a GUI, so update it
		result = result && mGUIManager->keyPressed(e);
		
		return result;
	}

	bool InGameState::keyReleased(const OIS::KeyEvent & e) {
		bool result = true;

		//We are using a GUI, so update it
		result = result && mGUIManager->keyReleased(e);
		
		return result;
	}
}