#ifndef LOBY_H
#define LOBY_H

#include "Player.h"
#include <zoidcom/zoidcom.h>
#include <map>

namespace HovUni {

/**
 * The loby, object
 */
class Loby
{
private:

	/**
	 * maximum players
	 */
	int mMaximumPlayers;

	/**
	 * Track filename
	 */
	Ogre::String mTrackFilename;

	/**
	 * Map with all players
	 */
	std::map<ZCom_ConnID,Player> mPlayers;

public:

	/**
	 * Constructor
	 */
	Loby(void);

	~Loby(void);

	virtual void onConnect( ZCom_ConnID id ) {
		//request extra info
		//add player to map
	}

	virtual void onDisconnect ( ZCom_ConnID id ) {
		//remove from map
		//if admin set new admin
	}

	virtual void onStart() {
		//called when map should be loaded

		

	}

};

}

#endif
