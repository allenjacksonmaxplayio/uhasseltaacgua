#include "MainMenu.h"

namespace HovUni {
	MainMenu::MainMenu(ServerMenuListener* serverListener) {
		//Create buttons

		//TODO: Make this resolution dependant
		short width = 445;
		short height = 320;

		mSingleplayerButton = new MenuButton("Singleplayer", "singleplayerBtn", "menuButton.swf", width, height, Hikari::Position(Hikari::Center, -(width / 2.0f), -(height / 2.0f)));
		mSingleplayerButton->bind("press", Hikari::FlashDelegate(this, &MainMenu::onSingleplayer));
		mMultiplayerButton = new MenuButton("Multiplayer", "multiplayerBtn", "menuButton.swf", width, height, Hikari::Position(Hikari::Center, (width / 2.0f), -(height / 2.0f)));
		mMultiplayerButton->bind("press", Hikari::FlashDelegate(this, &MainMenu::onMultiplayer));
		mOptionsButton = new MenuButton("Options", "optionsBtn", "menuButton.swf", width, height, Hikari::Position(Hikari::Center, -(width / 2.0f), (height / 2.0f)));
		mOptionsButton->bind("press", Hikari::FlashDelegate(this, &MainMenu::onOptions));
		mQuitButton = new MenuButton("Quit", "quitBtn", "menuButton.swf", width, height, Hikari::Position(Hikari::Center, (width / 2.0f), (height / 2.0f)));
		mQuitButton->bind("press", Hikari::FlashDelegate(this, &MainMenu::onQuit));

		addOverlay("singleplayerBtn", mSingleplayerButton);
		addOverlay("multiplayerBtn", mMultiplayerButton);
		addOverlay("optionsBtn", mOptionsButton);
		addOverlay("quitBtn", mQuitButton);

		mServerMenu = new ServerMenu(serverListener, Hikari::FlashDelegate(this, &MainMenu::onBack));
	}

	MainMenu::~MainMenu() {
		delete mSingleplayerButton;
		delete mMultiplayerButton;
		delete mOptionsButton;
		delete mQuitButton;
		delete mServerMenu;
	}

	Hikari::FlashValue MainMenu::onSingleplayer(Hikari::FlashControl* caller, const Hikari::Arguments& args) {

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

	Hikari::FlashValue MainMenu::onQuit(Hikari::FlashControl* caller, const Hikari::Arguments& args) {

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