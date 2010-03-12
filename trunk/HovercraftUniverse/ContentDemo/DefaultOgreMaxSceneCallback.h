#ifndef DEFAULTOGREMAXSCENECALLBACK_H
#define DEFAULTOGREMAXSCENECALLBACK_H

#include "CustomOgreMaxScene.h"
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>

namespace HovUni {

/**
 * This is a default implementation that will load a scene file.
 * It will also attach user data to ogre scene nodes and movables like this:
 * mNode->getUserObjectBindings().setUserAny("userdata",Ogre::Any(asteroid));
 */
class DefaultOgreMaxSceneCallback : public CustomOgreMaxSceneCallback
{
private:

	/**
	 * The viewport
	 */
	Ogre::RenderWindow * mWindow;

	/**
	 * The Scenemanager
	 */
	Ogre::SceneManager * mSceneManager;

	/**
	 * Temporary values needed by some methods, set to default values to prevent errors if they would not be read
	 * The xml is structured in such a way that these will be filled (or not at all) before they are needed.
	 */
	Ogre::Real mEnvironmentNear; // = 10000.0f;
	Ogre::Real mEnvironmentFar; // = 1.0f;
	OgreMax::Types::UpAxis mUpAxis; // = OgreMax::Types::UP_AXIS_Y

	/**
	 * Used while parsing custom data
	 */
	Ogre::SceneNode * mNode;
	Ogre::MovableObject * mMovable;

protected:

	void attachMovable ( Ogre::MovableObject * movable, const OgreMax::Types::Attachable * attachable );

	/**
	 * Add node animation to given node
	 * @param node
	 * @param animation
	 */
	void addNodeAnimation( Ogre::SceneNode * node, std::vector<OgreMax::Types::NodeAnimation> * animation );

public:

	/**
	 * Constructor
	 * @param viewport
	 * @param scenemanager
	 */
	DefaultOgreMaxSceneCallback(Ogre::RenderWindow * mWindow, Ogre::SceneManager * scenemanager);

	/**
	 * Destructor
	 */
	virtual ~DefaultOgreMaxSceneCallback(void);


	virtual void onSceneFile( const Ogre::String& fileName, Ogre::String& resourceGroupName){
	}
	
	virtual void onResourceLocation ( const Ogre::String& name, const Ogre::String& type, bool recursive) {
	}

	virtual void StartedLoad(){
	}

	virtual void onExternalUserData( OgreMax::Types::ExternalUserData& externalud) {
	}

	virtual void onSceneUserData(const Ogre::String& userDataReference, const Ogre::String& userData) {
		//TODO parse Track usedata
	}

	virtual void onExternal( OgreMax::Types::ExternalItem& externalitem){
	}

	virtual void FinishedLoad( bool success ){
	}

	virtual void UpdatedLoadProgress( Ogre::Real progress ){
	}

	//Scene info
	virtual void onSceneData( const OgreMax::Version& formatVersion, const OgreMax::Version& minOgreVersion, const OgreMax::Version& ogreMaxVersion, const Ogre::String& author, const Ogre::String& application, OgreMax::Types::UpAxis upAxis, Ogre::Real unitsPerMeter, const Ogre::String& unitType);

	//Sky systems

	virtual void onSkyBox( OgreMax::Types::SkyBoxParameters& skyBoxParameters, std::vector<OgreMax::Types::NodeAnimation> * animation );

    virtual void onSkyDome( OgreMax::Types::SkyDomeParameters& skyDomeParameters, std::vector<OgreMax::Types::NodeAnimation> * animation);

    virtual void onSkyPlane( OgreMax::Types::SkyPlaneParameters& skyPlaneParameters, std::vector<OgreMax::Types::NodeAnimation> * animation);

	//Enviroment

	virtual void onClipping( Ogre::Real environmentNear, Ogre::Real environmentFar);

	virtual void onFog ( OgreMax::Types::FogParameters& fog );

	virtual void onAmbientColour( const Ogre::ColourValue& colour );

	virtual void onShadowProperties( OgreMax::Types::ShadowParameters& parameter );

	virtual void onBackgroundColour( const Ogre::ColourValue& colour );

	//Nodes

	virtual void onRootNode ( const Ogre::Vector3& position, const Ogre::Quaternion& rotation, const Ogre::Vector3& scale );

	virtual void onNode( OgreMax::Types::NodeParameters& nodeparameters, std::vector<OgreMax::Types::NodeAnimation> * animation, const OgreMax::Types::NodeParameters* parent);

	//Movables

	virtual void onEntity( OgreMax::Types::EntityParameters& entityparameters, const OgreMax::Types::Attachable * parent );

	virtual void onLight( OgreMax::Types::LightParameters& light, const OgreMax::Types::Attachable * parent);
        
	virtual void onCamera(OgreMax::Types::CameraParameters& params, const OgreMax::Types::Attachable * parent );

	virtual void onBillboardSet( OgreMax::Types::BillboardSetParameters& bilboardsetparameters, std::vector<OgreMax::Types::Billboard>& billboardset, std::vector<OgreMax::Types::CustomParameter>& customParameters, const OgreMax::Types::Attachable * parent );

	virtual void onParticleSystem( OgreMax::Types::ParticleSystemParameters& particleSystem, const OgreMax::Types::Attachable * parent);

	virtual void onPlane( OgreMax::Types::PlaneParameters planeparameters, const OgreMax::Types::Attachable * parent);
};

}

#endif
