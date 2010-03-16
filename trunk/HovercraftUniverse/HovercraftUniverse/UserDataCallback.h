#ifndef USERDATACALLBACK_H
#define USERDATACALLBACK_H

#include <OgreSharedPtr.h>

#include "Start.h"
#include "Finish.h"
#include "Asteroid.h"
#include "Hovercraft.h"
#include "CheckPoint.h"
#include "StartPosition.h"
#include "SpeedBoost.h"
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
	UserDataCallback(bool register = true);

	/**
	 * Destructor
	 * Deregisters automaticly from UserDataFactory
	 */
	virtual ~UserDataCallback();

	/**
	 * Callback when asteroid is loaded
	 * User must delete the object if not used.
	 * @param asteroid
	 * @param an object that has userbindings(eg Ogre Movable and SceneNode)
	 */
	virtual void onAsteroid( Asteroid * asteroid);

	/**
	 * Callback when start is loaded
	 * User must delete the object if not used.
	 * @param start
	 * @param an object that has userbindings(eg Ogre Movable and SceneNode)
	 */
	virtual void onStart(Start * start);

	/**
	 * Callback when startposition is loaded
	 * User must delete the object if not used.
	 * @param startposition
	 * @param an object that has userbindings(eg Ogre Movable and SceneNode)
	 */
	virtual void onStartPosition(StartPosition * startposition);

	/**
	 * Callback when checkpoint is loaded
	 * User must delete the object if not used.
	 * @param checkpoint
	 * @param an object that has userbindings(eg Ogre Movable and SceneNode)
	 */
	virtual void onCheckPoint(CheckPoint * checkpoint);

	/**
	 * Callback when finish is loaded
	 * User must delete the object if not used.
	 * @param finish
	 * @param an object that has userbindings(eg Ogre Movable and SceneNode)
	 */
	virtual void onFinish(Finish * finish);

	/**
	 * Callback when hovercraft is loaded
	 * User must delete the object if not used.
	 * @param hovercraft
	 * @param an object that has userbindings(eg Ogre Movable and SceneNode)
	 */
	virtual void onHoverCraft(Hovercraft * hovercraft);

	/**
	 * Callback when track is loaded
	 * User must delete the object if not used.
	 * @param track
	 * @param an object that has userbindings(eg Ogre Movable and SceneNode)
	 */
	virtual void onTrack(Track * track);

	/**
	 * Callback when portal is loaded
	 * User must delete the object if not used.
	 * @param portal
	 * @param an object that has userbindings(eg Ogre Movable and SceneNode)
	 */
	virtual void onPortal(Portal * portal);

	/**
	 * Callback when boost is loaded
	 * User must delete the object if not used.
	 * @param boost
	 * @param an object that has userbindings(eg Ogre Movable and SceneNode)
	 */
	virtual void onBoost(SpeedBoost * boost);

	/**
	 * Callback when powerup spawn is loaded
	 * User must delete the object if not used.
	 * @param powerup spawn
	 * @param an object that has userbindings(eg Ogre Movable and SceneNode)
	 */
	virtual void onPowerupSpawn(PowerupSpawn * powerupspawn);

	/**
	 * Callback when reset spawn is loaded
	 * User must delete the object if not used.
	 * @param reset spawn
	 * @param an object that has userbindings(eg Ogre Movable and SceneNode)
	 */
	virtual void onResetSpawn(ResetSpawn * spawn);
};



}

#endif