#ifndef MAINMENU_H
#define MAINMENU_H

#include "MenuButton.h"
#include <OverlayContainer.h>

namespace HovUni {
	class MainMenu : public OverlayContainer {
		private:
			MenuButton* mSingleplayerButton;
			MenuButton* mMultiplayerButton;
			MenuButton* mOptionsButton;
			MenuButton* mQuitButton;

		public:
			MainMenu();
			virtual ~MainMenu();

		private:
			
	};
}

#endif //MAINMENU_H