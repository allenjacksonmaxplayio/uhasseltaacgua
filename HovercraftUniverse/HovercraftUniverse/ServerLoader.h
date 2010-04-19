#ifndef SERVERLOADER_H
#define SERVERLOADER_H

#include "Loader.h"
#include "UserDataCallback.h"
#include "UserDataFactory.h"

namespace HovUni {

class HoverCraftUniverseWorld;
class ServerCore;

/**
 * Loader for the server
 * @author Pieter-Jan Pintens
 */
class ServerLoader: public UserDataCallback, public Loader {
private:

	/**
	 * The local data factory
	 */
	UserDataFactory mUserDataFactory;

	/**
	 * Havok world
	 */
	HoverCraftUniverseWorld * mHovercraftWorld;

	/**
	 * Current external
	 */
	OgreMax::Types::ExternalItem * mExternalitem;

	/**
	 * A flag to state that the loader is working on hovercrafts
	 */
	bool mLoadingHovercrafts;

	/**
	 * Current player
	 */
	RacePlayer* mPlayer;

	Ogre::String mCurrentHovercraft;

	/**
	 * Current position
	 */
	int mPosition;

public:
	ServerLoader();

	~ServerLoader();

	virtual void load(const Ogre::String& filename);

	//Callbacks that need implementations

	virtual void onSceneUserData(const Ogre::String& userDataReference, const Ogre::String& userData);

	virtual void onExternal(OgreMax::Types::ExternalItem& externalitem);

	virtual void StartedLoad();

	virtual void FinishedLoad(bool success);

	virtual void onEntity(OgreMax::Types::EntityParameters& entityparameters, const OgreMax::Types::Attachable * parent);

	//Custom objects

	virtual void onAsteroid(Asteroid * asteroid);

	virtual void onStart(Start * start);

	virtual void onStartPosition(StartPosition * startposition);

	virtual void onCheckPoint(CheckPoint * checkpoint);

	virtual void onFinish(Finish * finish);

	virtual void onHoverCraft(Hovercraft * hovercraft);

	virtual void onTrack(Track * track);

	virtual void onPortal(Portal * portal);

	virtual void onBoost(SpeedBoost * boost);

	virtual void onPowerupSpawn(PowerupSpawn * powerupspawn);

	virtual void onResetSpawn(ResetSpawn * spawn);
};

}

#endif
