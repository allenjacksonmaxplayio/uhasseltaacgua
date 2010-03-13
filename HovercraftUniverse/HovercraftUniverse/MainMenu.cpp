#include "MainMenu.h"

namespace HovUni {
	MainMenu::MainMenu() {
		//Create buttons

		//TODO: Make this resolution dependant
		float width = 445;
		float height = 320;

		mSingleplayerButton = new MenuButton("Singleplayer", "singleplayerBtn", "menuButton.swf", width, height, Hikari::Position(Hikari::Center, -(width / 2.0f), -(height / 2.0f)));
		mMultiplayerButton = new MenuButton("Multiplayer", "multiplayerBtn", "menuButton.swf", width, height, Hikari::Position(Hikari::Center, (width / 2.0f), -(height / 2.0f)));
		mOptionsButton = new MenuButton("Options", "optionsBtn", "menuButton.swf", width, height, Hikari::Position(Hikari::Center, -(width / 2.0f), (height / 2.0f)));
		mQuitButton = new MenuButton("Quit", "quitBtn", "menuButton.swf", width, height, Hikari::Position(Hikari::Center, (width / 2.0f), (height / 2.0f)));

		addOverlay("singleplayerBtn", mSingleplayerButton);
		addOverlay("multiplayerBtn", mMultiplayerButton);
		addOverlay("optionsBtn", mOptionsButton);
		addOverlay("quitBtn", mQuitButton);
	}

	MainMenu::~MainMenu() {
		delete mSingleplayerButton;
		delete mMultiplayerButton;
		delete mOptionsButton;
		delete mQuitButton;
	}
}