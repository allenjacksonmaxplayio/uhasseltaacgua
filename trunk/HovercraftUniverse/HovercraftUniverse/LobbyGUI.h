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
			/** The background overlay */
			BasicOverlay* mBackground;

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
			LobbyGUI(const Hikari::FlashDelegate& onChat, const Hikari::FlashDelegate& onStart, const Hikari::FlashDelegate& onLeave);
			
			/**
			 * Destructor
			 */
			virtual ~LobbyGUI();

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

			/**
			 * Add a new user to the userlist. This list will be sorted in order of
			 * calls to this function.
			 *
			 * @param id A unique id for this user
			 * @param username The username of the user
			 * @param character The name of the character of the user
			 * @param car The name of the var of the user
			 */
			void addUser(int id, const std::string& username, const std::string& character, const std::string& car);

			/**
			 * Edit a given user's data, identified by the id.
			 *
			 * @param id A unique id for this user
			 * @param username The username of the user
			 * @param character The name of the character of the user
			 * @param car The name of the var of the user
			 */
			void editUser(int id, const std::string& username, const std::string& character, const std::string& car);

			/**
			 * Delete the user from the list with the given ID.
			 *
			 * @param The id of the user you want to delete
			 */
			void deleteUser(int id);
	};
}

#endif //_LOBBYGUI_H