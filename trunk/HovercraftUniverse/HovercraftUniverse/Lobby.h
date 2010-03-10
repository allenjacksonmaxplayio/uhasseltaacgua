#ifndef LOBBY_H
#define LOBBY_H

#include "NetworkEntity.h"
#include "Player.h"
#include <map>
#include <string>

namespace HovUni {

/**
 * The Lobby which holds the connected players, assigns an 
 * administrator and holds the map info.
 *
 * @author Pieter-Jan Pintens & Olivier Berghmans
 */
class Lobby : public NetworkEntity
{
private:

	//TODO MUTEX PROTECT PLAYERS

	/** Indicator of whether there is an administrator */
	bool mHasAdmin;

	/** The ID of the administrator */
	ZCom_ConnID mAdmin;

	/** The maximum number of players allowed */
	int mMaximumPlayers;

	/** The current number of players */
	int mCurrentPlayers;

	/** The filename of the track */
	Ogre::String mTrackFilename;

	/** Map with all players */
	std::map<ZCom_ConnID,Player*> mPlayers;

public:

	/**
	 * Constructor
	 */
	Lobby();

	/**
	 * Destructor
	 */
	~Lobby();

	// Connect callback on authority

	/**
	 * Called when player is about to connect
	 *
	 * @return true when there is room for a player, false if Lobby is full
	 */
	bool onConnectAttempt();

	/**
	 * Called when player connects
	 *
	 * @param id the ID of the new connected player
	 */
	virtual void onConnect(ZCom_ConnID id);

	/**
	 * Called when player disconnects
	 * 
	 * @param id the ID of the disconnected player
	 */
	virtual void onDisconnect(ZCom_ConnID id);

	// Event callbacks on authority, issued by owner

	/**
	 * Called when admin sends start
	 */
	virtual void onStart();

	/**
	 * Called when admin changes the map

	 * @param filename the new filename of the map
	 */
	virtual void onTrackChange(const Ogre::String& filename);

	/**
	 * Called when player changes character
	 * 
	 * @param id the ID of the player
	 * @param character the character of the player
	 */
	virtual void onPlayerCharacterChange(ZCom_ConnID id, const Ogre::String& character);

	/**
	 * Called when player changes hovercraft
	 *
	 * @param id the ID of the player
	 * @param hovercraft the hovercraft of the player
	 */
	virtual void onPlayerHovercraftChange(ZCom_ConnID id, const Ogre::String& hovercraft);

	//OVERWRITEN FROM NetworkEntity

	virtual void parseEvents(ZCom_BitStream* stream, float timeSince);

	virtual void setupReplication();

	/**
	 * Get the class name for this class. This is used for registering
	 * the class with the network
	 *
	 * @return the class name
	 */
	static std::string getClassName();

};

}

#endif
