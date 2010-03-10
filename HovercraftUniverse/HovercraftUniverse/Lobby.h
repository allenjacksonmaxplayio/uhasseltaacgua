#ifndef LOBBY_H
#define LOBBY_H

#include "NetworkEntity.h"
#include "Player.h"
#include <map>

namespace HovUni {

/**
 * The Lobby, object
 */
class Lobby : public NetworkEntity
{
private:

	//TODO MUTEX PROTECT PLAYERS

	/**
	 * The ID of the administrator
	 */
	bool mHasAdmin;

	ZCom_ConnID mAdmin;

	/**
	 * maximum players
	 */
	int mMaximumPlayers;

	int mCurrentPlayers;

	/**
	 * Track filename
	 */
	Ogre::String mTrackFilename;

	/**
	 * Map with all players
	 */
	std::map<ZCom_ConnID,Player*> mPlayers;

public:

	/**
	 * Constructor
	 * @param control
	 */
	Lobby();

	~Lobby(void);

	//CONNECT CALLBACKS

	/**
	 * Called when player is about to connect
	 * return true when there is room for a player, false if Lobby is full
	 */
	bool onConnectAttempt ( );

	/**
	 * Called when player connects
	 * @param id
	 */
	virtual void onConnect( ZCom_ConnID id );

	/**
	 * Called when player disconnects
	 * @param id
	 */
	virtual void onDisconnect ( ZCom_ConnID id );

	//EVENT CALLBACKS

	/**
	 * Called when admin sends start
	 */
	virtual void onStart();

	/**
	 * Called when admin changes the map
	 * @param map filename
	 */
	virtual void onMapChange( const Ogre::String& mapfilename );

	/**
	 * Called when player changes character
	 * @param id
	 * @param character
	 */
	virtual void onPlayerCharacterChange( ZCom_ConnID id, const Ogre::String& character  );

	/**
	 * Called when player changes hovercraft
	 * @param id
	 * @param hovercraft
	 */
	virtual void onPlayerHovercraftChange( ZCom_ConnID id, const Ogre::String& hovercraft );

	//OVERWRITEN FROM NetworkEntity

	virtual void parseEvents(ZCom_BitStream* stream, float timeSince);

	virtual void setupReplication();
};

}

#endif
