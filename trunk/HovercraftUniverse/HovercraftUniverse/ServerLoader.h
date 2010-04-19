#ifndef SERVERLOADER_H
#define SERVERLOADER_H

#include "Loader.h"
#include "EntityDescription.h"
#include "GameEntityDeclarations.h"

namespace HovUni {

class HoverCraftUniverseWorld;

/**
 * Loader for the server
 * @author Pieter-Jan Pintens
 */
class ServerLoader: public Loader {
private:

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

	/**
	 * Load given track
	 * @param filename
	 */
	virtual void load(const Ogre::String& filename);	

	//Callbacks that need implementations

	/**
	 * Callback when track loading done, after this step, the hovercrafts will be loaded
	 */
	virtual void FinishedLoad(bool success);

	/**
	 * Needed for Track
	 */
	virtual void onSceneUserData(const Ogre::String& userDataReference, const Ogre::String& userData);

	/**
	 * Needed for all other game items
	 */
	virtual void onExternal(OgreMax::Types::ExternalItem& externalitem);

	/**
	 * Needed to read hovercraft
	 */
	virtual void onEntity(OgreMax::Types::EntityParameters& entityparameters, const OgreMax::Types::Attachable * parent);

private:

	//Custom objects

	void parseUserData(const Ogre::String& data, const EntityDescription& description);

	virtual void onAsteroid(Asteroid * asteroid);

	virtual void onStartPosition(StartPosition * startposition);

	virtual void onCheckPoint(CheckPoint * checkpoint);

	virtual void onFinish(Finish * finish);

	virtual void onStart(Start * start);

	virtual void onHoverCraft(Hovercraft * hovercraft);

	virtual void onTrack(Track * track);

	virtual void onPortal(Portal * portal);

	virtual void onBoost(SpeedBoost * boost);

	virtual void onPowerupSpawn(PowerupSpawn * powerupspawn);

	virtual void onResetSpawn(ResetSpawn * spawn);
};

}

#endif
