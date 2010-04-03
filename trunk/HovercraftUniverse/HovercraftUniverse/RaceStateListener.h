#ifndef RACESTATELISTENER_H
#define RACESTATELISTENER_H

#include "RacePlayer.h"

namespace HovUni {

class RaceStateListener {
public:
	/**
	 * The player changed position
	 *
	 * @param player the player
	 */
	virtual void onPositionChange(RacePlayer* player) = 0;
};

}

#endif
