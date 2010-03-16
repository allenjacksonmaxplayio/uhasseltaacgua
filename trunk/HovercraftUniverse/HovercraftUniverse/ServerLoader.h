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
class ServerLoader : public UserDataCallback, public Loader {
private:

	/**
	 * Havok world
	 */
	HoverCraftUniverseWorld * mHovercraftWorld;

	/**
	 * Server
	 */
	ServerCore * mServer;

	/**
	 * Current external
	 */
	OgreMax::Types::ExternalItem * mExternalitem;

public:
	ServerLoader(ServerCore * server);

	~ServerLoader();

	virtual void load ( const Ogre::String& filename );

	//Callbacks that need implementations

	virtual void onSceneUserData(const Ogre::String& userDataReference, const Ogre::String& userData);

	virtual void onExternal( OgreMax::Types::ExternalItem& externalitem);

	virtual void FinishedLoad( bool success );

	//Custom objects

	virtual void onAsteroid( Ogre::SharedPtr<Asteroid> asteroid );

	virtual void onStart( Ogre::SharedPtr<Start> start );

	virtual void onStartPosition( Ogre::SharedPtr<StartPosition> startposition );

	virtual void onCheckPoint( Ogre::SharedPtr<CheckPoint> checkpoint );

	virtual void onFinish( Ogre::SharedPtr<Finish> finish );

	virtual void onHoverCraft( Ogre::SharedPtr<Hovercraft> hovercraft );

	virtual void onTrack( Ogre::SharedPtr<Track> track );

	virtual void onPortal( Ogre::SharedPtr<Portal> portal );

	virtual void onBoost( Ogre::SharedPtr<SpeedBoost> boost );

	virtual void onPowerupSpawn( Ogre::SharedPtr<PowerupSpawn> powerupspawn );

	virtual void onResetSpawn( Ogre::SharedPtr<ResetSpawn> spawn );
};

}

#endif