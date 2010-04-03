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
	 * A player joined
	 *
	 * @param setting the settings of the player
	 */
	virtual void onJoin(PlayerSettings* settings) = 0;

	/**
	 * The track was changed by the administrator
	 */
	virtual void onTrackChange() = 0;
};

}

#endif
