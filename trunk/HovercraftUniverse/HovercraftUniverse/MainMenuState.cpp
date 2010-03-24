#include "MainMenuState.h"
#include "InGameState.h"
#include "HUClient.h"
#include <tinyxml/tinyxml.h>

namespace HovUni {
	MainMenuState::MainMenuState() : mContinue(true), mLastGUIUpdate(-1) {
		mMenu = new MainMenu(this, Hikari::FlashDelegate(this, &MainMenuState::onQuit));
	}

	bool MainMenuState::onConnect(const Ogre::String& address) {
		//Connect to the give address
		///////////////////////////////////////////
		///////////////////////////////////////////
		//TODO: Parse IP and Port?
		HUClient* mClient = new HUClient(address.c_str());

		TiXmlDocument doc("gui/GUIConfig.xml");
		doc.LoadFile();

		InGameState* newState = new InGameState(mClient, doc.RootElement()->FirstChildElement("HUD"));
		mManager->addGameState(GameStateManager::IN_GAME, newState);
		mManager->switchState(GameStateManager::IN_GAME);
		///////////////////////////////////////////
		///////////////////////////////////////////

		//should check if connection was successfull
		return true;
	}

	void MainMenuState::onCreate() {
		//Create a new game
	}

	Hikari::FlashValue MainMenuState::onQuit(Hikari::FlashControl* caller, const Hikari::Arguments& args) {
		mContinue = false;

		return Hikari::FlashValue();
	}

	void MainMenuState::activate() {
		//Try and move the mouse to the center of the screen
		mInputManager->moveMouseTo(mGUIManager->getResolutionWidth() / 2, mGUIManager->getResolutionHeight() / 2);

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

		mLastGUIUpdate += evt.timeSinceLastFrame;

		if (mLastGUIUpdate > (1.0f / 25.0f) || mLastGUIUpdate < 0) {
			//We are using a GUI, so update it
			mGUIManager->update();
			mLastGUIUpdate = 0.0f; //Reset
		}

		//We have sound, update it
		mSoundManager->update();

		return (result && mContinue);
	}

	bool MainMenuState::mouseMoved(const OIS::MouseEvent & e) {
		bool result = true;

		//We are using a GUI, so update it
		result = result && mGUIManager->mouseMoved(e);

		return result;
	}

	bool MainMenuState::mousePressed(const OIS::MouseEvent & e, OIS::MouseButtonID id) {
		bool result = true;


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

		OIS::Keyboard * keyboard = InputManager::getSingletonPtr()->getKeyboard();

		switch (e.key) {
			case OIS::KC_ESCAPE:
			case OIS::KC_LMENU:
			case OIS::KC_RMENU:
			case OIS::KC_F4:
				// Check whether right combinations are pressed concurrently
				if (keyboard->isKeyDown(OIS::KC_ESCAPE) || 
					(keyboard->isKeyDown(OIS::KC_LMENU) && keyboard->isKeyDown(OIS::KC_RMENU) && keyboard->isKeyDown(OIS::KC_F4))) {
					// Stop rendering
					mContinue = false;			
				}

				break;
			default:
				// Do nothing
				break;
		}

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
