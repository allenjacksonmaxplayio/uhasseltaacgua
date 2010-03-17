#ifndef _SERVERMENU_H
#define _SERVERMENU_H

#include "OverlayContainer.h"

#include "ConnectWindow.h"
#include "MenuButton.h"
#include "ServerMenuListener.h"

namespace HovUni {
	/**
	 * An overlay containing a server menu
	 *
	 * @author Nick De Frangh
	 */
	class ServerMenu : public OverlayContainer {
		private:
			MenuButton* mJoinButton;
			MenuButton* mCreateButton;
			MenuButton* mBackButton;
			ConnectWindow* mConnectWindow;

			ServerMenuListener* mListener;

		public:
			ServerMenu(ServerMenuListener* listener, const Hikari::FlashDelegate& onBack);

			Hikari::FlashValue onOk(Hikari::FlashControl* caller, const Hikari::Arguments& args);

			Hikari::FlashValue onCancel(Hikari::FlashControl* caller, const Hikari::Arguments& args);

			Hikari::FlashValue onCreate(Hikari::FlashControl* caller, const Hikari::Arguments& args);

			Hikari::FlashValue onJoin(Hikari::FlashControl* caller, const Hikari::Arguments& args);
	};
}

#endif //_SERVERMENU_H