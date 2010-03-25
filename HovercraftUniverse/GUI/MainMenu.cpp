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

		//Calculate inition top padding, this is the total space available above the buttons
		int topPadding = ((GUIManager::getSingletonPtr()->getResolutionHeight() / 2) - height);
		size = GUIManager::getSingletonPtr()->scale(356, 86, 713, 173);
		width = size.first;
		height = size.second;
		
		//Adjust the padding to the calculated height
		//topPadding -= (height - (height / 3));
		topPadding = (topPadding / 2) - (height / 4);

		mTitle = new BasicOverlay("Title", "title.swf", width, height, Hikari::Position(Hikari::TopCenter, 0, topPadding), 1);
		mTitle->setBParameter(BasicOverlay::ALPHAHACK, true);
		addOverlay("title", mTitle);

		mServerMenu = new ServerMenu(serverListener, Hikari::FlashDelegate(this, &MainMenu::onBack));
	}

	MainMenu::~MainMenu() {
		if (isActivated()) {
			deactivate();
		}
		if (mServerMenu->isActivated()) {
			mServerMenu->deactivate();
		}

		delete mSingleplayerButton;
		delete mMultiplayerButton;
		delete mOptionsButton;
		delete mQuitButton;
		delete mTitle;
		delete mServerMenu;
	}

	void MainMenu::onActivate() {
	}

	void MainMenu::onDeactivate() {
		if (mServerMenu->isActivated()) {
			mServerMenu->deactivate();
		}
	}

	Hikari::FlashValue MainMenu::onSingleplayer(Hikari::FlashControl* caller, const Hikari::Arguments& args) {
		mListener->onConnect("localhost");

		return "success";
	}

	Hikari::FlashValue MainMenu::onMultiplayer(Hikari::FlashControl* caller, const Hikari::Arguments& args) {
		//Deactivate ourself
		this->deactivate();

		//Activate the ServerMenu
		mServerMenu->activate();

		return "success";
	}

	Hikari::FlashValue MainMenu::onOptions(Hikari::FlashControl* caller, const Hikari::Arguments& args) {

		return "success";
	}

	Hikari::FlashValue MainMenu::onBack(Hikari::FlashControl* caller, const Hikari::Arguments& args) {
		//We came back to the main menu
		mServerMenu->deactivate();

		//activate ourself
		this->activate();

		return "success";
	}
}