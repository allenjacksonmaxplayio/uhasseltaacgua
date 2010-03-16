#ifndef MAINMENU_H
#define MAINMENU_H

#include "MenuButton.h"
#include <OverlayContainer.h>
#include "ServerMenu.h"
#include "ServerMenuListener.h"

namespace HovUni {
	class MainMenu : public OverlayContainer {
		private:
			MenuButton* mSingleplayerButton;
			MenuButton* mMultiplayerButton;
			MenuButton* mOptionsButton;
			MenuButton* mQuitButton;

			ServerMenu* mServerMenu;

		public:
			MainMenu(ServerMenuListener* serverListener);

			virtual ~MainMenu();

			Hikari::FlashValue onSingleplayer(Hikari::FlashControl* caller, const Hikari::Arguments& args);

			Hikari::FlashValue onMultiplayer(Hikari::FlashControl* caller, const Hikari::Arguments& args);

			Hikari::FlashValue onOptions(Hikari::FlashControl* caller, const Hikari::Arguments& args);

			Hikari::FlashValue onQuit(Hikari::FlashControl* caller, const Hikari::Arguments& args);

			Hikari::FlashValue onBack(Hikari::FlashControl* caller, const Hikari::Arguments& args);

		private:
			
	};
}

#endif //MAINMENU_H