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
	 * Temporary values needed by some methods, set to default values to prevent errors if they would not be read
	 * The xml is structured in such a way that these will be filled (or not at all) before they are needed.
	 */
	Ogre::Real mEnvironmentNear; // = 10000.0f;
	Ogre::Real mEnvironmentFar; // = 1.0f;
	OgreMax::Types::UpAxis mUpAxis; // = OgreMax::Types::UP_AXIS_Y

protected:

	void attachMovable ( Ogre::MovableObject * movable, const OgreMax::Types::Attachable * attachable )  {
/*		if (this->node != 0){
            this->node->attachObject(object);
		}
        else if (this->entity != 0 && !this->boneName.empty())
        {
            //TODO: Modify Ogre to accept object->getName() when creating TagPoint
            Ogre::TagPoint* tagPoint = this->entity->attachObjectToBone(this->boneName, object);
            tagPoint->setPosition(this->attachPosition);
            tagPoint->setScale(this->attachScale);
            tagPoint->setOrientation(this->attachRotation);
        }
		else if (this->entity != 0){
			//add empty tagpoint this is allowed
            Ogre::SkeletonInstance* skeleton = this->entity->getSkeleton();
            Ogre::Bone* bone = skeleton->getBone(this->boneName);
            //TODO: Modify Ogre to accept name when creating TagPoint
            Ogre::TagPoint* tagPoint = skeleton->createTagPointOnBone(bone);
            tagPoint->setPosition(this->attachPosition);
            tagPoint->setScale(this->attachScale);
            tagPoint->setOrientation(this->attachRotation);
		}*/
	}

	/**
	 * Add node animation to given node
	 * @param node
	 * @param animation
	 */
	void addNodeAnimation( Ogre::SceneNode * node, std::vector<OgreMax::Types::NodeAnimation> * animation );

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

	//Scene info
	virtual void onSceneData( const OgreMax::Version& formatVersion, const OgreMax::Version& minOgreVersion, const OgreMax::Version& ogreMaxVersion, const Ogre::String& author, const Ogre::String& application, OgreMax::Types::UpAxis upAxis, Ogre::Real unitsPerMeter, const Ogre::String& unitType);

	//Sky systems

	virtual void onSkyBox( OgreMax::Types::SkyBoxParameters& skyBoxParameters, std::vector<OgreMax::Types::NodeAnimation> * animation );

    virtual void onSkyDome( OgreMax::Types::SkyDomeParameters& skyDomeParameters, std::vector<OgreMax::Types::NodeAnimation> * animation);

    virtual void onSkyPlane( OgreMax::Types::SkyPlaneParameters& skyPlaneParameters, std::vector<OgreMax::Types::NodeAnimation> * animation);

	//Enviroment

	virtual void onLoadClipping( Ogre::Real environmentNear, Ogre::Real environmentFar);

	virtual void onFog ( const OgreMax::Types::FogParameters& fog );

	virtual void onAmbientColour( const Ogre::ColourValue& colour );

	virtual void onShadowProperties( OgreMax::Types::ShadowParameters& parameter );

	virtual void onBackgroundColour( const Ogre::ColourValue& colour );

	//Nodes

	virtual void onRootNode ( const Ogre::Vector3& position, const Ogre::Quaternion& rotation, const Ogre::Vector3& scale );

	virtual void onNode( OgreMax::Types::NodeParameters& nodeparameters, std::vector<OgreMax::Types::NodeAnimation> * animation, const OgreMax::Types::NodeParameters* parent);

	//Movables

	virtual void onEntity( OgreMax::Types::EntityParameters& entityparameters, const OgreMax::Types::Attachable * parent );

	virtual void onLight(const OgreMax::Types::LightParameters& light, const OgreMax::Types::Attachable * parent);
        
	virtual void onCamera(const OgreMax::Types::CameraParameters& camera, const OgreMax::Types::Attachable * parent );

	virtual void onBillboardSet( OgreMax::Types::BillboardSetParameters& bilboardsetparameters, std::vector<OgreMax::Types::Billboard>& billboardset, std::vector<OgreMax::Types::CustomParameter>& customParameters, const OgreMax::Types::Attachable * parent );

	virtual void onParticleSystem( OgreMax::Types::ParticleSystemParameters& particleSystem, const OgreMax::Types::Attachable * parent);

	virtual void onPlane( OgreMax::Types::PlaneParameters planeparameters, const OgreMax::Types::Attachable * parent);
};

}

#endif
