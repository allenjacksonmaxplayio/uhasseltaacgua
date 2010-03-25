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
			 * This will be called after the overlay has been activated.
			 * It will mark this overlay for keyboard input
			 */
			void customActionAfterActivate();
	};
}

#endif //_LOBBYOVERLAY_H