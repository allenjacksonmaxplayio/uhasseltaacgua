#include "MainMenuState.h"
#include "InGameState.h"
#include "ClientCore.h"
#include <tinyxml/tinyxml.h>

namespace HovUni {
	MainMenuState::MainMenuState() {
		mMenu = new MainMenu();
	}

	void MainMenuState::activate() {
		//Make sure we have a cursor
		mGUIManager->showCursor(true);

		//Activate the menu overlay
		mMenu->activate();
	}

	void MainMenuState::disable() {
		//Deactivate the menu overlay
		mMenu->deactivate();
	}

	bool MainMenuState::frameStarted(const Ogre::FrameEvent & evt) {
		bool result = true;

		//We are using a GUI, so update it
		mGUIManager->update();

		//We have sound, update it
		mSoundManager->update();

		return result;
	}

	bool MainMenuState::mouseMoved(const OIS::MouseEvent & e) {
		bool result = true;

		//We are using a GUI, so update it
		result = result && mGUIManager->mouseMoved(e);

		return result;
	}

	bool MainMenuState::mousePressed(const OIS::MouseEvent & e, OIS::MouseButtonID id) {
		bool result = true;

		///////////////////////////////////////////
		///////////////////////////////////////////
		//For now, load the InGameState on click!
		ClientCore* mClient = new ClientCore("localhost", 3040);

		TiXmlDocument doc("gui/GUIConfig.xml");
		doc.LoadFile();

		InGameState* newState = new InGameState(mClient, doc.RootElement()->FirstChildElement("HUD"));
		mManager->addGameState(GameStateManager::IN_GAME, newState);
		mManager->switchState(GameStateManager::IN_GAME);
		///////////////////////////////////////////
		///////////////////////////////////////////

		//We are using a GUI, so update it
		result = result && mGUIManager->mousePressed(e, id);
		
		return result;
	}

	bool MainMenuState::mouseReleased(const OIS::MouseEvent & e, OIS::MouseButtonID id) {
		bool result = true;

		//We are using a GUI, so update it
		result = result && mGUIManager->mouseReleased(e, id);
		
		return result;
	}

	bool MainMenuState::keyPressed(const OIS::KeyEvent & e) {
		bool result = true;

		//We are using a GUI, so update it
		result = result && mGUIManager->keyPressed(e);
		
		return result;
	}

	bool MainMenuState::keyReleased(const OIS::KeyEvent & e) {
		bool result = true;

		//We are using a GUI, so update it
		result = result && mGUIManager->keyReleased(e);
		
		return result;
	}
}