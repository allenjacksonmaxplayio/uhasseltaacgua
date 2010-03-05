#ifndef PHYSICSLOADER_H
#define PHYSICSLOADER_H

#include "CustomOgreMaxSceneCallback.h"
#include "UserDataCallback.h"
#include "UserDataFactory.h"

namespace HovUni {

class HoverCraftUniverseWorld;

class PhysicsLoader : public UserDataCallback, public CustomOgreMaxSceneCallback {
private:

	char const * mPath;

	HoverCraftUniverseWorld * mHovercraftWorld;

	OgreMax::Types::ExternalItem * mExternalitem;

	OgreMax::Types::NodeParameters * mNodeparameters;

	OgreMax::Types::EntityParameters * mEntityparameters;

public:
	PhysicsLoader( HoverCraftUniverseWorld * world, char const * path );

	~PhysicsLoader();
	
	virtual void StartedLoad(){
		//TODO notify clients??
	}

	virtual void FinishedLoad( bool success );

	virtual void UpdatedLoadProgress( Ogre::Real progress ){
		//TODO notify clients??
	}

	//Objects to be parsed

	virtual void onSceneUserData(const Ogre::String& userDataReference, const Ogre::String& userData);

	virtual void onExternal( OgreMax::Types::ExternalItem& externalitem);

	virtual void onNode( OgreMax::Types::NodeParameters& nodeparameters, std::vector<OgreMax::Types::NodeAnimation> * animation, const OgreMax::Types::NodeParameters* parent);

	virtual void onEntity( OgreMax::Types::EntityParameters& entityparameters, const OgreMax::Types::Attachable * parent );

	//Custom objects

	virtual void onAsteroid( Ogre::SharedPtr<Asteroid> asteroid );

	virtual void onStart( Ogre::SharedPtr<Start> start );

	virtual void onStartPosition( Ogre::SharedPtr<StartPosition> startposition );

	virtual void onCheckPoint( Ogre::SharedPtr<CheckPoint> checkpoint );

	virtual void onFinish( Ogre::SharedPtr<Finish> finish );

	virtual void onHoverCraft( Ogre::SharedPtr<Hovercraft> hovercraft );

	virtual void onTrack( Ogre::SharedPtr<Track> track );

	virtual void onPortal( Ogre::SharedPtr<Portal> portal );

	virtual void onBoost( Ogre::SharedPtr<Boost> boost );

	virtual void onPowerupSpawn( Ogre::SharedPtr<PowerupSpawn> powerupspawn );

	virtual void onResetSpawn( Ogre::SharedPtr<ResetSpawn> spawn );

	//don't care about next

	virtual void onSceneData( const OgreMax::Version& formatVersion, const OgreMax::Version& minOgreVersion, const OgreMax::Version& ogreMaxVersion, const Ogre::String& author, const Ogre::String& application, OgreMax::Types::UpAxis upAxis, Ogre::Real unitsPerMeter, const Ogre::String& unitType) {}

	virtual void onSkyBox( OgreMax::Types::SkyBoxParameters& skyBoxParameters, std::vector<OgreMax::Types::NodeAnimation> * animation ) {}

	virtual void onSkyDome( OgreMax::Types::SkyDomeParameters& skyDomeParameters, std::vector<OgreMax::Types::NodeAnimation> * animation) {}

	virtual void onSkyPlane( OgreMax::Types::SkyPlaneParameters& skyPlaneParameters, std::vector<OgreMax::Types::NodeAnimation> * animation) {}

	virtual void onClipping( Ogre::Real environmentNear, Ogre::Real environmentFar){}

	virtual void onFog ( OgreMax::Types::FogParameters& fog ){}

	virtual void onAmbientColour( const Ogre::ColourValue& colour ){}

	virtual void onShadowProperties( OgreMax::Types::ShadowParameters& parameter ){}

	virtual void onBackgroundColour( const Ogre::ColourValue& colour ){}

	virtual void onRootNode ( const Ogre::Vector3& position, const Ogre::Quaternion& rotation, const Ogre::Vector3& scale ) {}

	virtual void onLight( OgreMax::Types::LightParameters& light, const OgreMax::Types::Attachable * parent) {}
        
	virtual void onCamera(OgreMax::Types::CameraParameters& params, const OgreMax::Types::Attachable * parent ) {}

	virtual void onBillboardSet( OgreMax::Types::BillboardSetParameters& bilboardsetparameters, std::vector<OgreMax::Types::Billboard>& billboardset, std::vector<OgreMax::Types::CustomParameter>& customParameters, const OgreMax::Types::Attachable * parent ) {}

	virtual void onParticleSystem( OgreMax::Types::ParticleSystemParameters& particleSystem, const OgreMax::Types::Attachable * parent) {}

	virtual void onPlane( OgreMax::Types::PlaneParameters planeparameters, const OgreMax::Types::Attachable * parent) {}

	virtual void onSceneFile( const Ogre::String& fileName, Ogre::String& resourceGroupName){}
	
	virtual void onResourceLocation ( const Ogre::String& name, const Ogre::String& type, bool recursive) {}

	virtual void onExternalUserData( OgreMax::Types::ExternalUserData& externalud) {}

};

}

#endif