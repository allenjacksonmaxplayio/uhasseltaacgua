#ifndef _MAINMENU_H
#define _MAINMENU_H

#include "MenuButton.h"
#include "OverlayContainer.h"
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
			
			//TEMP
			ServerMenuListener* mListener;

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

#endif //_MAINMENU_H