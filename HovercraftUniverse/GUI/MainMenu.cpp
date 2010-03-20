#include "MainMenu.h"
#include "GUIManager.h"

namespace HovUni {
	MainMenu::MainMenu(ServerMenuListener* serverListener, const Hikari::FlashDelegate& onQuit) {
		//Create buttons
		mListener = serverListener;

		std::pair<int, int> size = GUIManager::getSingletonPtr()->scale(222, 160, 445, 320);
		int width = size.first;
		int height = size.second;

		mSingleplayerButton = new MenuButton("Singleplayer", "singleplayerBtn", "menuButton.swf", width, height, Hikari::Position(Hikari::Center, -(width / 2), -(height / 2)));
		mSingleplayerButton->bind("press", Hikari::FlashDelegate(this, &MainMenu::onSingleplayer));
		mMultiplayerButton = new MenuButton("Multiplayer", "multiplayerBtn", "menuButton.swf", width, height, Hikari::Position(Hikari::Center, (width / 2), -(height / 2)));
		mMultiplayerButton->bind("press", Hikari::FlashDelegate(this, &MainMenu::onMultiplayer));
		mOptionsButton = new MenuButton("Options", "optionsBtn", "menuButton.swf", width, height, Hikari::Position(Hikari::Center, -(width / 2), (height / 2)));
		mOptionsButton->bind("press", Hikari::FlashDelegate(this, &MainMenu::onOptions));
		mQuitButton = new MenuButton("Quit", "quitBtn", "menuButton.swf", width, height, Hikari::Position(Hikari::Center, (width / 2), (height / 2)));
		mQuitButton->bind("press", onQuit);

		addOverlay("singleplayerBtn", mSingleplayerButton);
		addOverlay("multiplayerBtn", mMultiplayerButton);
		addOverlay("optionsBtn", mOptionsButton);
		addOverlay("quitBtn", mQuitButton);

		size = GUIManager::getSingletonPtr()->scale(356, 86, 713, 173);
		width = size.first;
		height = size.second;
		mTitle = new BasicOverlay("Title", "title.swf", width, height, Hikari::TopCenter);
		mTitle->setBParameter(BasicOverlay::ALPHAHACK, true);

		mServerMenu = new ServerMenu(serverListener, Hikari::FlashDelegate(this, &MainMenu::onBack));
	}

	MainMenu::~MainMenu() {
		delete mSingleplayerButton;
		delete mMultiplayerButton;
		delete mOptionsButton;
		delete mQuitButton;
		delete mServerMenu;
		delete mTitle;
	}

	void MainMenu::onActivate() {
		//Activate the header
		GUIManager::getSingletonPtr()->activateOverlay(mTitle);
	}

	void MainMenu::onDeactivate() {
		//Disable the header
		GUIManager::getSingletonPtr()->disableOverlay(mTitle);
	}

	Hikari::FlashValue MainMenu::onSingleplayer(Hikari::FlashControl* caller, const Hikari::Arguments& args) {
		mListener->onConnect("localhost");
		return Hikari::FlashValue();
	}

	Hikari::FlashValue MainMenu::onMultiplayer(Hikari::FlashControl* caller, const Hikari::Arguments& args) {
		//Deactivate ourself
		this->deactivate();

		//Activate the ServerMenu
		mServerMenu->activate();

		return Hikari::FlashValue();
	}

	Hikari::FlashValue MainMenu::onOptions(Hikari::FlashControl* caller, const Hikari::Arguments& args) {

		return Hikari::FlashValue();
	}

	Hikari::FlashValue MainMenu::onBack(Hikari::FlashControl* caller, const Hikari::Arguments& args) {
		//We came back to the main menu
		mServerMenu->deactivate();

		//activate ourself
		this->activate();

		return Hikari::FlashValue();
	}
}