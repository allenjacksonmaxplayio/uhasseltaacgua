#ifndef _LOBBYSTATE_H
#define _LOBBYSTATE_H

#include <BasicGameState.h>
#include "HUClient.h"
#include "PlayerSettingsListener.h"
#include "PlayerSettingsInterceptor.h"
#include "Lobby.h"
#include "LobbyGUI.h"
#include "LobbyListener.h"
#include <map>

namespace HovUni {
	/**
	 * This class represents the lobby state of the game. When a client
	 * connects to a server and a game has not started, the client will
	 * reside in this state.
	 *
	 * @author Nick De Frangh
	 */
	class LobbyState : public BasicGameState, public LobbyListener, public PlayerSettingsListener {
		private:
			/** The client which represents our connection */
			HUClient* mClient;

			/** The lobby we are in*/
			Lobby* mLobby;

			/** A reference to the GUI manager */
			GUIManager* mGUIManager;

			/** The vieualisation for the GUI */
			LobbyGUI* mLobbyGUI;

			/** Time since last GUI update, in seconds */
			Ogre::Real mLastGUIUpdate;

			/** Time since the last client update, in seconds */
			Ogre::Real mLastClientUpdate;

			/** Mapping of ID's to playersettingsinterceptors */
			std::map<int, PlayerSettingsInterceptor*> mPlayerInterceptors;

		public:
			/**
			 * Constructor
			 *
			 * @param client The client to which the user is connected
			 */
			LobbyState(HUClient* client);

			/** Destructor */
			virtual ~LobbyState();

			/**
			 * Function that will handle new Chat Input
			 */
			Hikari::FlashValue onChat(Hikari::FlashControl* caller, const Hikari::Arguments& args);

			/**
			 * Function that will be called when a user clicks on the start button
			 */
			Hikari::FlashValue onStart(Hikari::FlashControl* caller, const Hikari::Arguments& args);

			/**
			 * Function that will be calles when a user clicks on the leave button
			 */
			Hikari::FlashValue onLeave(Hikari::FlashControl* caller, const Hikari::Arguments& args);

			////////////////////////////////////////
			//	PlayerSettingsListener functions
			////////////////////////////////////////

			/**
			 * @inheritDoc
			 */
			void onPlayerUpdate(int id, const std::string& username, const std::string& character, const std::string& car);

			////////////////////////////////////////
			//	LobbyListener functions
			////////////////////////////////////////

			/**
			 * @inheritDoc
			 */
			virtual void onLeave(ZCom_ConnID id);

			/**
			 * @inheritDoc
			 */
			virtual void onJoin(PlayerSettings * settings);

			/**
			 * @inheritDoc
			 */
			virtual void onCharacterChange();

			/**
			 * @inheritDoc
			 */
			virtual void onHovercraftChange();

			/**
			 * @inheritDoc
			 */
			virtual void onTrackChange();

			////////////////////////////////////////
			//	BasicGameState functions
			////////////////////////////////////////

			/**
			 * Function called when the state gets activated
			 */
			virtual void activate();

			/**
			 * Function called when the state gets disabled
			 */
			virtual void disable();

			/**
			 * Function called every frame, do drawing functions and stuff in here
			 */
			virtual bool frameStarted(const Ogre::FrameEvent & evt);

			/**
			 * @see MouseListener::mouseMoved().
			 * Can be implemented as needed.
			 */
			virtual bool mouseMoved(const OIS::MouseEvent & e);

			/**
			 * @see MouseListener::mousePressed().
			 * Can be implemented as needed.
			 */
			virtual bool mousePressed(const OIS::MouseEvent & e, OIS::MouseButtonID id);
			
			/**
			 * @see MouseListener::mouseReleased().
			 * Can be implemented as needed.
			 */
			virtual bool mouseReleased(const OIS::MouseEvent & e, OIS::MouseButtonID id);

			/**
			 * @see KeyListener::keyPressed().
			 * Can be implemented as needed.
			 */
			virtual bool keyPressed(const OIS::KeyEvent & e);

			/**
			 * @see KeyListener::keyReleased().
			 * Can be implemented as needed.
			 */
			virtual bool keyReleased(const OIS::KeyEvent & e);
	};
}

#endif //_LOBBYSTATE_H