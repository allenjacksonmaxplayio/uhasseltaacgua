#ifndef CLIENTLOADER_H
#define CLIENTLOADER_H

#include "Loader.h"

namespace HovUni {

/**
 * TODO KRISTOF OF IEMAND ANDERS
 * Should load static geometry that doesn't change (entities the server wont send info about)
 */
class ClientLoader : public Loader
{
public:
	ClientLoader(void);

	~ClientLoader(void);

	virtual void StartedLoad(){
		//TODO notify server??
	}

	virtual void FinishedLoad( bool success ){
		//TODO notify server!!
	}

	virtual void UpdatedLoadProgress( Ogre::Real progress ){
		//TODO notify server??
	}

	virtual void onSceneUserData(const Ogre::String& userDataReference, const Ogre::String& userData){};

	virtual void onExternal( OgreMax::Types::ExternalItem& externalitem){};

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
	
	virtual void onEntity( OgreMax::Types::EntityParameters& entityparameters, const OgreMax::Types::Attachable * parent ){}

	virtual void onNode( OgreMax::Types::NodeParameters& nodeparameters, std::vector<OgreMax::Types::NodeAnimation> * animation, const OgreMax::Types::NodeParameters* parent){}
};

}

#endif