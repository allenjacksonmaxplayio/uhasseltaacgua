#ifndef _LOBBYGUI_H
#define _LOBBYGUI_H

#include <OverlayContainer.h>
#include "HUClient.h"
#include "MenuButton.h"
#include "Lobby.h"
#include "LobbyOverlay.h"
#include "ChatListener.h"

namespace HovUni {
	/**
	 * This class represents the GUI for our lobby object
	 *
	 * @author Nick De Frangh
	 */
	class LobbyGUI : public OverlayContainer, public ChatListener {
		private:
			/** The actual lobby overlay */
			LobbyOverlay* mLobbyOverlay;

			/** A button to pick a hovercraft */
			MenuButton* mPickCar;

			/** A button to pick a new character */
			MenuButton* mPickChar;

			/** A button to leave the lobby */
			MenuButton* mLeave;

			/** A button to start the race (admin only) */
			MenuButton* mStart;

		public:
			/**
			 * Constructor for the LobbyGUI
			 *
			 * @param onChat Function to be called when a user gives new chat input
			 */
			LobbyGUI(const Hikari::FlashDelegate& onChat);

			/**
			 * Add a new chat message to the lobby chat
			 *
			 * @param username The name of the user that posted the message
			 * @param message The message the user has posted
			 */
			virtual void newMessage(const std::string& user, const std::string& line);

			/**
			 * An incoming notification from the server
			 *
			 * @param notif the notification
			 */
			virtual void newNotification(const std::string& notif);

			virtual ~LobbyGUI();
	};
}

#endif //_LOBBYGUI_H