#include "LobbyState.h"

#include "Config.h"
#include "Application.h"
#include "InGameState.h"
#include <tinyxml/tinyxml.h>
#include <OgreRoot.h>

namespace HovUni {
	LobbyState::LobbyState(HUClient* client) : mClient(client), mLobby(client->getLobby()), mLastGUIUpdate(0), mLastClientUpdate(0) {
		mGUIManager = GUIManager::getSingletonPtr();
		mLobbyGUI = new LobbyGUI(Hikari::FlashDelegate(this, &LobbyState::onChat), Hikari::FlashDelegate(this, &LobbyState::onStart), Hikari::FlashDelegate(this, &LobbyState::onLeave));

		mClient->setChatListener(mLobbyGUI);
		mClient->process();
	}

	LobbyState::~LobbyState() {
		delete mLobbyGUI;
	}

	Hikari::FlashValue LobbyState::onChat(Hikari::FlashControl* caller, const Hikari::Arguments& args) {
		mClient->getChatClient()->sendText(args.at(0).getString());
		Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "LobbyState :: " << "Sending chat message: " << args.at(0).getString();
		return "success";
	}

	Hikari::FlashValue LobbyState::onStart(Hikari::FlashControl* caller, const Hikari::Arguments& args) {
		mClient->start();

		TiXmlDocument doc("gui/GUIConfig.xml");
		doc.LoadFile();
		InGameState* newState = new InGameState(mClient, doc.RootElement()->FirstChildElement("HUD"));
		mManager->addGameState(GameStateManager::IN_GAME, newState);
		mManager->switchState(GameStateManager::IN_GAME);

		return "success";
	}

	Hikari::FlashValue LobbyState::onLeave(Hikari::FlashControl* caller, const Hikari::Arguments& args) {
		mManager->switchState(GameStateManager::MAIN_MENU);
		//Delete the client to save some resources
		delete mClient;

		return "success";
	}

	void LobbyState::activate() {
		//We don't want any crazy input keys
		mInputManager->getKeyManager()->setInactive();

		//Make sure we have a cursor
		mGUIManager->showCursor(true);

		//Activate the menu overlay
		mLobbyGUI->activate();

		//Show ourselves in the lobby!
		Config* conf = Application::getConfig();
		mLobbyGUI->addUser(1, conf->getValue("Player", "PlayerName"), conf->getValue("Player", "Character"), conf->getValue("Player", "Hovercraft"));
	}

	void LobbyState::disable() {
		//Deactivate the menu overlay
		mLobbyGUI->deactivate();
	}

	bool LobbyState::frameStarted(const Ogre::FrameEvent & evt) {
		bool result = true;

		mLastGUIUpdate += evt.timeSinceLastFrame;
		mLastClientUpdate += evt.timeSinceLastFrame;

		if (mLastGUIUpdate > (1.0f / 25.0f) || mLastGUIUpdate < 0) {
			//We are using a GUI, so update it
			mGUIManager->update();
			mLastGUIUpdate = 0.0f; //Reset
		}

		if (mLastClientUpdate > 0.016f) {
			mClient->process();
			mLastClientUpdate = 0.0f;
		}

		//We have sound, update it
		mSoundManager->update();

		return result;
	}

	bool LobbyState::mouseMoved(const OIS::MouseEvent & e) {
		bool result = true;

		//We are using a GUI, so update it
		result = result && mGUIManager->mouseMoved(e);

		return result;
	}

	bool LobbyState::mousePressed(const OIS::MouseEvent & e, OIS::MouseButtonID id) {
		bool result = true;

		//We are using a GUI, so update it
		result = result && mGUIManager->mousePressed(e, id);
		
		return result;
	}

	bool LobbyState::mouseReleased(const OIS::MouseEvent & e, OIS::MouseButtonID id) {
		bool result = true;

		//We are using a GUI, so update it
		result = result && mGUIManager->mouseReleased(e, id);
		
		return result;
	}

	bool LobbyState::keyPressed(const OIS::KeyEvent & e) {
		bool result = true;

		//We are using a GUI, so update it
		result = result && mGUIManager->keyPressed(e);
		
		return result;
	}

	bool LobbyState::keyReleased(const OIS::KeyEvent & e) {
		bool result = true;

		//We are using a GUI, so update it
		result = result && mGUIManager->keyReleased(e);
		
		return result;
	}
}