#ifndef USERDATACALLBACK_H
#define USERDATACALLBACK_H

#include <OgreSharedPtr.h>

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
	UserDataCallback(bool register = true);

	/**
	 * Destructor
	 * Deregisters automaticly from UserDataFactory
	 */
	virtual ~UserDataCallback();

	/**
	 * Callback when asteroid is loaded
	 * @param asteroid
	 * @param an object that has userbindings(eg Ogre Movable and SceneNode)
	 */
	virtual void onAsteroid(Ogre::SharedPtr<Asteroid> asteroid) {};

	/**
	 * Callback when start is loaded
	 * @param start
	 * @param an object that has userbindings(eg Ogre Movable and SceneNode)
	 */
	virtual void onStart(Ogre::SharedPtr<Start> start) {};

	/**
	 * Callback when startposition is loaded
	 * @param startposition
	 * @param an object that has userbindings(eg Ogre Movable and SceneNode)
	 */
	virtual void onStartPosition(Ogre::SharedPtr<StartPosition> startposition) {};

	/**
	 * Callback when checkpoint is loaded
	 * @param checkpoint
	 * @param an object that has userbindings(eg Ogre Movable and SceneNode)
	 */
	virtual void onCheckPoint(Ogre::SharedPtr<CheckPoint> checkpoint) {};

	/**
	 * Callback when finish is loaded
	 * @param finish
	 * @param an object that has userbindings(eg Ogre Movable and SceneNode)
	 */
	virtual void onFinish(Ogre::SharedPtr<Finish> finish) {};

	/**
	 * Callback when hovercraft is loaded
	 * @param hovercraft
	 * @param an object that has userbindings(eg Ogre Movable and SceneNode)
	 */
	virtual void onHoverCraft(Ogre::SharedPtr<Hovercraft> hovercraft) {};

	/**
	 * Callback when track is loaded
	 * @param track
	 * @param an object that has userbindings(eg Ogre Movable and SceneNode)
	 */
	virtual void onTrack(Ogre::SharedPtr<Track> track) {};

	/**
	 * Callback when portal is loaded
	 * @param portal
	 * @param an object that has userbindings(eg Ogre Movable and SceneNode)
	 */
	virtual void onPortal(Ogre::SharedPtr<Portal> portal) {};

	/**
	 * Callback when boost is loaded
	 * @param boost
	 * @param an object that has userbindings(eg Ogre Movable and SceneNode)
	 */
	virtual void onBoost(Ogre::SharedPtr<Boost> boost) {};

	/**
	 * Callback when powerup spawn is loaded
	 * @param powerup spawn
	 * @param an object that has userbindings(eg Ogre Movable and SceneNode)
	 */
	virtual void onPowerupSpawn(Ogre::SharedPtr<PowerupSpawn> powerupspawn) {};

	/**
	 * Callback when reset spawn is loaded
	 * @param reset spawn
	 * @param an object that has userbindings(eg Ogre Movable and SceneNode)
	 */
	virtual void onResetSpawn(Ogre::SharedPtr<ResetSpawn> spawn) {};
};



}

#endif