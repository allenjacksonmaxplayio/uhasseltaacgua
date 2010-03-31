#include "LobbyGUI.h"
#include "GUIManager.h"

namespace HovUni {
	LobbyGUI::LobbyGUI(const Hikari::FlashDelegate& onChat, const Hikari::FlashDelegate& onStart, const Hikari::FlashDelegate& onLeave) {
		//Show the background
		mBackground = new BasicOverlay("Background_LB", "background.swf", GUIManager::getSingletonPtr()->getResolutionWidth(), GUIManager::getSingletonPtr()->getResolutionHeight(), Hikari::Center, 1);
		mBackground->setExactFit(true);
		addOverlay("Background__LB", mBackground);
		
		//Lets make the buttons first, calculate their size
		int height = GUIManager::getSingletonPtr()->getResolutionHeight() / 4; //We want to fill the entire screen
		float scale = (height * 1.0f) / 320.0f;
		int width = (int) (445 * scale);
		
		mPickCar = new MenuButton("Change\nHovercraft", "pickCarBtn", "menuButton.swf", width, height, Hikari::Position(Hikari::Right, 0, -(3 * (height / 2))));
		//mSingleplayerButton->bind("press", Hikari::FlashDelegate(this, &MainMenu::onSingleplayer));;
		mPickChar = new MenuButton("Change\nCharacter", "pickCharBtn", "menuButton.swf", width, height, Hikari::Position(Hikari::Right, 0, -(height / 2)));
		mLeave = new MenuButton("Leave Lobby", "leaveBtn", "menuButton.swf", width, height, Hikari::Position(Hikari::Right, 0, (height / 2)));
		mLeave->bind("press", onLeave);
		mStart = new MenuButton("Start", "startBtn", "menuButton.swf", width, height, Hikari::Position(Hikari::Right, 0, (3 * (height / 2))));
		mStart->bind("press", onStart);

		addOverlay("pickCarBtn", mPickCar);
		addOverlay("pickCharBtn", mPickChar);
		addOverlay("leaveBtn", mLeave);
		addOverlay("startBtn", mStart);

		int lobbyWidth = GUIManager::getSingletonPtr()->getResolutionWidth() - width; //The maximum width we have
		scale = (lobbyWidth * 1.0f) / 1500.0f;
		int lobbyHeight = (int) (scale * 1000);

		//Now show the lobby itself
		mLobbyOverlay = new LobbyOverlay(onChat, "lobbyVisual", "lobby.swf", lobbyWidth, lobbyHeight, Hikari::BottomLeft);
		addOverlay("lobbyVisual", mLobbyOverlay);
	}

	LobbyGUI::~LobbyGUI() {
		delete mPickCar;
		delete mPickChar;
		delete mLeave;
		delete mStart;
	}

	void LobbyGUI::newMessage(const std::string& user, const std::string& line) {
		mLobbyOverlay->addText(user, line);
	}

	void LobbyGUI::newNotification(const std::string& notif) {
		mLobbyOverlay->addAction(notif);
	}

	void LobbyGUI::addUser(int id, const std::string& username, const std::string& character, const std::string& car) {
		mLobbyOverlay->addUser(id, username, character, car);
	}

	void LobbyGUI::editUser(int id, const std::string& username, const std::string& character, const std::string& car) {
		mLobbyOverlay->editUser(id, username, character, car);
	}

	void LobbyGUI::deleteUser(int id) {
		mLobbyOverlay->deleteUser(id);
	}
}