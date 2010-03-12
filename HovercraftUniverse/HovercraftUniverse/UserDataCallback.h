#ifndef USERDATACALLBACK_H
#define USERDATACALLBACK_H

#include <OgreSharedPtr.h>

#include "StartData.h"
#include "FinishData.h"
#include "AsteroidData.h"
#include "HovercraftData.h"
#include "CheckPointData.h"
#include "StartPositionData.h"
#include "BoostData.h"
#include "TrackData.h"
#include "PortalData.h"
#include "PowerupSpawnData.h"
#include "ResetSpawnData.h"

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
	 * @param an object that has userbindings (eg Ogre Movable and SceneNode)
	 */
	virtual void onAsteroid( Ogre::SharedPtr<AsteroidData> asteroid ) {};

	/**
	 * Callback when start is loaded
	 * @param start
	 * @param an object that has userbindings (eg Ogre Movable and SceneNode)
	 */
	virtual void onStart( Ogre::SharedPtr<StartData> start ) {};

	/**
	 * Callback when startposition is loaded
	 * @param startposition
	 * @param an object that has userbindings (eg Ogre Movable and SceneNode)
	 */
	virtual void onStartPosition( Ogre::SharedPtr<StartPositionData> startposition ) {};

	/**
	 * Callback when checkpoint is loaded
	 * @param checkpoint
	 * @param an object that has userbindings (eg Ogre Movable and SceneNode)
	 */
	virtual void onCheckPoint( Ogre::SharedPtr<CheckPointData> checkpoint ) {};

	/**
	 * Callback when finish is loaded
	 * @param finish
	 * @param an object that has userbindings (eg Ogre Movable and SceneNode)
	 */
	virtual void onFinish( Ogre::SharedPtr<FinishData> finish ) {};

	/**
	 * Callback when hovercraft is loaded
	 * @param hovercraft
	 * @param an object that has userbindings (eg Ogre Movable and SceneNode)
	 */
	virtual void onHoverCraft( Ogre::SharedPtr<HovercraftData> hovercraft ) {};

	/**
	 * Callback when track is loaded
	 * @param track
	 * @param an object that has userbindings (eg Ogre Movable and SceneNode)
	 */
	virtual void onTrack( Ogre::SharedPtr<TrackData> track ) {};

	/**
	 * Callback when portal is loaded
	 * @param portal
	 * @param an object that has userbindings (eg Ogre Movable and SceneNode)
	 */
	virtual void onPortal( Ogre::SharedPtr<PortalData> portal ) {};

	/**
	 * Callback when boost is loaded
	 * @param boost
	 * @param an object that has userbindings (eg Ogre Movable and SceneNode)
	 */
	virtual void onBoost( Ogre::SharedPtr<BoostData> boost ) {};

	/**
	 * Callback when powerup spawn is loaded
	 * @param powerup spawn
	 * @param an object that has userbindings (eg Ogre Movable and SceneNode)
	 */
	virtual void onPowerupSpawn( Ogre::SharedPtr<PowerupSpawnData> powerupspawn ) {};

	/**
	 * Callback when reset spawn is loaded
	 * @param reset spawn
	 * @param an object that has userbindings (eg Ogre Movable and SceneNode)
	 */
	virtual void onResetSpawn( Ogre::SharedPtr<ResetSpawnData> spawn ) {};
};



}

#endif