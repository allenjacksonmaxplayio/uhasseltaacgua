#ifndef USERDATACALLBACK_H
#define USERDATACALLBACK_H

#include "Start.h"
#include "Finish.h"
#include "Asteroid.h"
#include "Hovercraft.h"
#include "CheckPoint.h"
#include "StartPosition.h"
#include "Boost.h"
#include "Track.h"
#include "Portal.h"
#include "PowerupSpawn.h"
#include "ResetSpawn.h"

namespace HovUni {

/**
 * User data Callback
 */
class UserDataCallback {

public:

	/**
	 * Constructor
	 * @param flag, true if component should register itself with the UserDataFactory, false if the component should not
	 */
	UserDataCallback( bool register = true);

	/**
	 * Destructor
	 * Deregisters automaticly from UserDataFactory
	 */
	virtual ~UserDataCallback();

	/**
	 * Callback when asteroid is loaded
	 * @param asteroid
	 */
	virtual void onAsteroid( Asteroid * asteroid ) {};

	/**
	 * Callback when start is loaded
	 * @param start
	 */
	virtual void onStart( Start * start ) {};

	/**
	 * Callback when startposition is loaded
	 * @param startposition
	 */
	virtual void onStartPosition( StartPosition * startposition ) {};

	/**
	 * Callback when checkpoint is loaded
	 * @param checkpoint
	 */
	virtual void onCheckPoint( CheckPoint * checkpoint ) {};

	/**
	 * Callback when finish is loaded
	 * @param finish
	 */
	virtual void onFinish( Finish * finish ) {};

	/**
	 * Callback when hovercraft is loaded
	 * @param hovercraft
	 */
	virtual void onHoverCraft( Hovercraft * hovercraft ) {};

	/**
	 * Callback when track is loaded
	 * @param track
	 */
	virtual void onTrack( Track * track ) {};

	/**
	 * Callback when portal is loaded
	 * @param portal
	 */
	virtual void onPortal( Portal * portal ) {};

	/**
	 * Callback when boost is loaded
	 * @param boost
	 */
	virtual void onBoost( Boost * boost ) {};

	/**
	 * Callback when powerup spawn is loaded
	 * @param powerup spawn
	 */
	virtual void onPowerupSpawn( PowerupSpawn * powerupspawn ) {};

	/**
	 * Callback when reset spawn is loaded
	 * @param reset spawn
	 */
	virtual void onResetSpawn( ResetSpawn * spawn ) {};
};



}

#endif