#ifndef DEFAULTOGREMAXSCENECALLBACK_H
#define DEFAULTOGREMAXSCENECALLBACK_H

#include "CustomOgreMaxScene.h"
#include <OgreSceneManager.h>
#include "UserDataFactory.h"

namespace HovUni {

class DefaultOgreMaxSceneCallback : public CustomOgreMaxSceneCallback
{
private:

	/**
	 * The viewport
	 */
	Ogre::Viewport * mViewport;

	/**
	 * The Scenemanager
	 */
	Ogre::SceneManager * mSceneManager;

	/**
	 * Temporary values
	 */
	Ogre::Real mEnvironmentNear; // = 10000.0f;
	Ogre::Real mEnvironmentFar; // = 1.0f;

protected:

	void parseExtraData( const OgreMax::Types::ObjectExtraDataPtr& extradata, Ogre::MovableObject * object ){
		if ( extradata->HasUserData() ){
			//UserDataFactory::getInstance().parseUserData(extradata->userData);
		}
	}

	void parseExtraData( const OgreMax::Types::ObjectExtraDataPtr& extradata, Ogre::SceneNode * node ){
		if ( extradata->HasUserData() ){
			//UserDataFactory::getInstance().parseUserData(extradata->userData);
		}
	}

public:

	/**
	 * Constructor
	 * @param viewport
	 * @param scenemanager
	 */
	DefaultOgreMaxSceneCallback(Ogre::Viewport * viewport, Ogre::SceneManager * scenemanager);

	/**
	 * Destructor
	 */
	virtual ~DefaultOgreMaxSceneCallback(void);

	//Sky

	virtual void onSkyBox( OgreMax::Types::SkyBoxParameters& skyBoxParameters );

    virtual void onSkyDome( OgreMax::Types::SkyDomeParameters& skyDomeParameters);

    virtual void onSkyPlane( OgreMax::Types::SkyPlaneParameters& skyPlaneParameters);

	//Enviroment

	virtual void onLoadClipping( Ogre::Real environmentNear, Ogre::Real environmentFar);

	virtual void onFog ( const OgreMax::Types::FogParameters& fog );

	virtual void onAmbientColour( const Ogre::ColourValue& colour );

	virtual void onShadowProperties( OgreMax::Types::ShadowParameters& parameter );

	virtual void onBackgroundColour( const Ogre::ColourValue& colour );

	//Movables

	virtual void onNode( const OgreMax::Types::NodeParameters& nodeparameters, const OgreMax::Types::NodeParameters* parent);

	virtual void onRootNode ( const Ogre::Vector3& position, const Ogre::Quaternion& rotation, const Ogre::Vector3& scale );

	virtual void onLight(const OgreMax::Types::LightParameters& light, const OgreMax::Types::NodeParameters * parent);
        
	virtual void onCamera(const OgreMax::Types::CameraParameters& camera, const OgreMax::Types::NodeParameters * parent);

};

}

#endif
