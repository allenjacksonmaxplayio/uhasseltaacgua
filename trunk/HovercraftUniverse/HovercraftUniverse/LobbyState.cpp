#include "LobbyState.h"

#include "Config.h"
#include "Application.h"
#include "InGameState.h"
#include <tinyxml/tinyxml.h>
#include <OgreRoot.h>

namespace HovUni {
	LobbyState::LobbyState(HUClient* client) : mClient(client), mLobby(client->getLobby()), mLastGUIUpdate(0), mLastClientUpdate(0) {
		mGUIManager = GUIManager::getSingletonPtr();
		mLobbyGUI = new LobbyGUI(Hikari::FlashDelegate(this, &LobbyState::onChat), Hikari::FlashDelegate(this, &LobbyState::onPressStart), Hikari::FlashDelegate(this, &LobbyState::onPressLeave));

		mClient->setChatListener(mLobbyGUI);
		//mClient->process();
	}

	LobbyState::~LobbyState() {
		delete mLobbyGUI;

		for (map<int, PlayerSettingsInterceptor*>::iterator it = mPlayerInterceptors.begin(); it != mPlayerInterceptors.end(); ++it) {
			//Delete the interceptor
			delete (*it).second;
		}
	}

	Hikari::FlashValue LobbyState::onChat(Hikari::FlashControl* caller, const Hikari::Arguments& args) {
		mClient->getChatClient()->sendText(args.at(0).getString());
		Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "[LobbyState]: " << "Sending chat message: " << args.at(0).getString();

		return "success";
	}

	Hikari::FlashValue LobbyState::onPressStart(Hikari::FlashControl* caller, const Hikari::Arguments& args) {
		mClient->start();

		TiXmlDocument doc("gui/GUIConfig.xml");
		doc.LoadFile();
		InGameState* newState = new InGameState(mClient, doc.RootElement()->FirstChildElement("HUD"));
		mManager->addGameState(GameStateManager::IN_GAME, newState);
		mManager->switchState(GameStateManager::IN_GAME);

		return "success";
	}

	Hikari::FlashValue LobbyState::onPressLeave(Hikari::FlashControl* caller, const Hikari::Arguments& args) {
		mManager->switchState(GameStateManager::MAIN_MENU);
		//Delete the client to save some resources
		delete mClient;

		return "success";
	}

	////////////////////////////////////////
	//	PlayerSettingsListener functions
	////////////////////////////////////////

	void LobbyState::onPlayerUpdate(int id, const std::string& username, const std::string& character, const std::string& car) {
		//Player has been updated, propagate changes
		mLobbyGUI->editUser(id, username, character, car);
	}

	////////////////////////////////////////
	//	LobbyListener functions
	////////////////////////////////////////

	void LobbyState::onLeave(ZCom_ConnID id) {
		
	}

	void LobbyState::onJoin(PlayerSettings * settings) {
		//Ogre::LogManager::getSingletonPtr()->getDefaultLog()->stream() << "[LobbyState]: onJoin was called! " << settings->getPlayerName() << " (" << settings->getID() << ")";
		//Player has joined, add empty player to the visualisation
		mLobbyGUI->addUser(settings->getID(), settings->getPlayerName(), settings->getCharacter(), settings->getHovercraft());
		//Create a new playersettingsinterceptor
		PlayerSettingsInterceptor* intercept = new PlayerSettingsInterceptor(settings, this);
		//Store te interceptor
		mPlayerInterceptors.insert(std::pair<int, PlayerSettingsInterceptor*>(settings->getID(), intercept));
	}

	void LobbyState::onStart() {
		//We need to start loading
	}

	////////////////////////////////////////
	//	BasicGameState functions
	////////////////////////////////////////

	void LobbyState::activate() {
		//We don't want any crazy input keys
		mInputManager->getKeyManager()->setInactive();

		//Make sure we have a cursor
		mGUIManager->showCursor(true);

		//Activate the menu overlay
		mLobbyGUI->activate();

		//Show ourselves in the lobby!
		//Get all the playerconfigs and show them in the lobby
		const Lobby::playermap players = mLobby->getPlayers();
		for (Lobby::playermap::const_iterator i = players.begin(); i != players.end(); ++i) {
			PlayerSettings* player = (*i).second;
			mLobbyGUI->addUser(player->getID(), player->getPlayerName(), player->getCharacter(), player->getHovercraft());
		}

		//Activate all possible interception listeners
		for (map<int, PlayerSettingsInterceptor*>::iterator it = mPlayerInterceptors.begin(); it != mPlayerInterceptors.end(); ++it) {
			//make the interceptor inactive
			(*it).second->setStatus(true);
		}

		//Config* conf = Application::getConfig();
		//mLobbyGUI->addUser(1, conf->getValue("Player", "PlayerName"), conf->getValue("Player", "Character"), conf->getValue("Player", "Hovercraft"));
	}

	void LobbyState::disable() {
		//Disable all the interception listeners
		for (map<int, PlayerSettingsInterceptor*>::iterator it = mPlayerInterceptors.begin(); it != mPlayerInterceptors.end(); ++it) {
			//make the interceptor inactive
			(*it).second->setStatus(false);
		}

		//Deactivate the menu overlay
		mLobbyGUI->deactivate();
	}

	bool LobbyState::frameStarted(const Ogre::FrameEvent & evt) {
		bool result = true;

		mLastGUIUpdate += evt.timeSinceLastFrame;
		mLastClientUpdate += evt.timeSinceLastFrame;

		if (mLastGUIUpdate > (1.0f / 25.0f) || mLastGUIUpdate < 0) {
			//Check if we need to show the start button or not
			if (mLobby->isAdmin()) {
				mLobbyGUI->showStart(true);
			} else {
				mLobbyGUI->showStart(false);
			}

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