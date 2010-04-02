#ifndef LOBBY_LISTENER_H
#define LOBBY_LISTENER_H

#include "zoidcom/zoidcom.h"
#include "PlayerSettings.h"

namespace HovUni {

class LobbyListener
{
public:

	virtual void onLeave(ZCom_ConnID id) = 0;

	virtual void onJoin(PlayerSettings * settings) = 0;

	virtual void onCharacterChange() = 0;

	virtual void onHovercraftChange() = 0;

	virtual void onTrackChange() = 0;
};

}

#endif
