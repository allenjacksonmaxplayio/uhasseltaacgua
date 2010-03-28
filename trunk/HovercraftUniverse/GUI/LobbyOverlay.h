#ifndef _LOBBYOVERLAY_H
#define _LOBBYOVERLAY_H

#include "BasicOverlay.h"

namespace HovUni {
	class LobbyOverlay : public BasicOverlay {
		public:
			/**
			 * Basic constructor, see BasicOverlay for info about the parameters
			 * @param chatInput The callback function that will be called when someone
			 *			posts a new chat message
			 */
			LobbyOverlay(const Hikari::FlashDelegate& chatInput, const Ogre::String& name, const Ogre::String& fileName, int width, int height, const Hikari::Position& position, Ogre::ushort zOrder = 0);

			/**
			 * Add a new chat message to the lobby chat
			 *
			 * @param username The name of the user that posted the message
			 * @param message The message the user has posted
			 */
			void addText(const Ogre::String& username, const Ogre::String& message);

			/**
			 * Add a new action to the lobby chat
			 *
			 * @param message The message the action should display
			 */
			void addAction(const Ogre::String& message);

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

			/**
			 * This will be called after the overlay has been activated.
			 * It will mark this overlay for keyboard input
			 */
			void customActionAfterActivate();
	};
}

#endif //_LOBBYOVERLAY_H