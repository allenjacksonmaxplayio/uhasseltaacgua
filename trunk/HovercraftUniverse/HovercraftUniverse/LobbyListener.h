#ifndef LOBBY_LISTENER_H
#define LOBBY_LISTENER_H

#include "PlayerSettings.h"

namespace HovUni {

/**
 * A listener for the lobby. Implement the methods in order to receive callbacks on events
 *
 * @author Nick De Frangh
 */
class LobbyListener {
public:
	/**
	 * The player with a certain connection ID left
	 *
	 * @param id the connection ID of the leaving player
	 */
	virtual void onLeave(ZCom_ConnID id) = 0;

	/**
	 * Listeners will be notified of new players trough this function
	 *
	 * @param settings The settings of the new player
	 */
	virtual void onJoin(PlayerSettings * settings) = 0;

	/**
	 * The admin has started the game and send out the start event
	 */
	virtual void onStart() = 0;
};

}

#endif
