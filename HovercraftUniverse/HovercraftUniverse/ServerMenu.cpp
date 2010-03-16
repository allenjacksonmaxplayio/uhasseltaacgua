#include "ServerMenu.h"
#include "GUIManager.h"

namespace HovUni {
	ServerMenu::ServerMenu(ServerMenuListener* listener, const Hikari::FlashDelegate& onBack) : mListener(listener) {
		//Create the buttons
		//TODO: Make this resolution dependant
		short width = 445;
		short height = 320;

		mCreateButton = new MenuButton("Create game", "createBtn", "menuButton.swf", width, height, Hikari::Position(Hikari::Center, -(width / 2.0f), -(height / 2.0f)));
		mCreateButton->bind("press", Hikari::FlashDelegate(this, &ServerMenu::onCreate));
		mJoinButton = new MenuButton("Join game", "joinBtn", "menuButton.swf", width, height, Hikari::Position(Hikari::Center, (width / 2.0f), -(height / 2.0f)));
		mJoinButton->bind("press", Hikari::FlashDelegate(this, &ServerMenu::onJoin));
		mBackButton = new MenuButton("Back", "backBtn", "menuButton.swf", width, height, Hikari::Position(Hikari::Center, 0, (height / 2.0f)));
		mBackButton->bind("press", onBack);
		
		//Add the buttons to the overlay container
		addOverlay("createBtn", mCreateButton);
		addOverlay("joinBtn", mJoinButton);
		addOverlay("backBtn", mBackButton);

		//Create the connect window
		width = 682;
		height = 181;
		mConnectWindow = new ConnectWindow(Hikari::FlashDelegate(this, &ServerMenu::onOk), Hikari::FlashDelegate(this, &ServerMenu::onCancel), "connectionwindow", "serverMenu.swf", width, height, Hikari::Center);
	}

	Hikari::FlashValue ServerMenu::onOk(Hikari::FlashControl* caller, const Hikari::Arguments& args) {
		Ogre::String address = args.at(0).getString();

		if (mListener->onConnect(address)) {
			//We don't want the input box anymore
			GUIManager::getSingletonPtr()->disableOverlay(mConnectWindow);
			//And the menu isn't needed
			this->deactivate();
		}

		return Hikari::FlashValue();
	}

	Hikari::FlashValue ServerMenu::onCancel(Hikari::FlashControl* caller, const Hikari::Arguments& args) {
		//Hide the connect window
		GUIManager::getSingletonPtr()->disableOverlay(mConnectWindow);

		//TODO: re-enable buttons on background

		return Hikari::FlashValue();
	}

	Hikari::FlashValue ServerMenu::onCreate(Hikari::FlashControl* caller, const Hikari::Arguments& args) {
		mListener->onCreate();

		return Hikari::FlashValue();
	}

	Hikari::FlashValue ServerMenu::onJoin(Hikari::FlashControl* caller, const Hikari::Arguments& args) {
		//show the connectWindow
		GUIManager::getSingletonPtr()->activateOverlay(mConnectWindow);

		//TODO: disable buttons on background
		return Hikari::FlashValue();
	}
}