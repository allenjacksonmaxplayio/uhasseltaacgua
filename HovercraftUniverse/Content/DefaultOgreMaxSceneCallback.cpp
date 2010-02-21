#include "DefaultOgreMaxSceneCallback.h"

#include <OgreAnimation.h>
#include <OgreRoot.h>
#include <OgreMaxUtilities.hpp>
#include <OgreShadowCameraSetupFocused.h>
#include <OgreShadowCameraSetup.h>
#include <OgreShadowCameraSetupLiSPSM.h>
#include <OgreShadowCameraSetupPlaneOptimal.h>


namespace HovUni {

DefaultOgreMaxSceneCallback::DefaultOgreMaxSceneCallback(Ogre::Viewport * viewport, Ogre::SceneManager * scenemanager):
	mSceneManager(scenemanager), mViewport(viewport)
{
	mEnvironmentNear = 10000.0f;
	mEnvironmentFar = 1.0f;
	mUpAxis = OgreMax::Types::UP_AXIS_Y;
}

DefaultOgreMaxSceneCallback::~DefaultOgreMaxSceneCallback(void)
{
}

void DefaultOgreMaxSceneCallback::onSceneData( const OgreMax::Version& formatVersion, const OgreMax::Version& minOgreVersion, const OgreMax::Version& ogreMaxVersion, const Ogre::String& author, const Ogre::String& application, OgreMax::Types::UpAxis upAxis, Ogre::Real unitsPerMeter, const Ogre::String& unitType) {
	mUpAxis = upAxis;
}


void DefaultOgreMaxSceneCallback::onNode( const OgreMax::Types::NodeParameters& nodeparameters, const OgreMax::Types::NodeParameters* parent){
	//Get Ogre parent
	Ogre::SceneNode* parentnode = 0;
	if ( parent == 0 ){
		parentnode = mSceneManager->getRootSceneNode();
	} else {
		parentnode = mSceneManager->getSceneNode(parent->name);
	}
	assert(parentnode != 0 );
	
	//create node
	Ogre::SceneNode* node = nodeparameters.name.empty() ? parentnode->createChildSceneNode() : parentnode->createChildSceneNode(nodeparameters.name);
	
	//set properties
	node->setPosition(nodeparameters.position);
	node->setOrientation(nodeparameters.orientation);
	node->setScale(nodeparameters.scale);

	//set initial state
    node->setInitialState();

    //Set the node's visibility
	OgreMax::OgreMaxUtilities::SetNodeVisibility(node, nodeparameters.visibility);
	
	//check for extra data
	parseExtraData(nodeparameters.extraData, node);
}

void DefaultOgreMaxSceneCallback::onRootNode ( const Ogre::Vector3& position, const Ogre::Quaternion& rotation, const Ogre::Vector3& scale ){
	Ogre::SceneNode * scene = mSceneManager->getRootSceneNode();
	scene->setPosition(position);
	scene->setOrientation(rotation);
	scene->setScale(scale);
}


void DefaultOgreMaxSceneCallback::onLight(const OgreMax::Types::LightParameters& parameters, const OgreMax::Types::NodeParameters * parent) {
	//Create the light
	Ogre::Light* light = mSceneManager->createLight(parameters.name);
	if (parameters.queryFlags != 0)
		light->setQueryFlags(parameters.queryFlags);
	if (parameters.visibilityFlags != 0)
		light->setVisibilityFlags(parameters.visibilityFlags);
	OgreMax::OgreMaxUtilities::SetObjectVisibility(light, parameters.visibility);
	light->setType(parameters.lightType);
	light->setCastShadows(parameters.castShadows);
	light->setPowerScale(parameters.power);
	light->setDiffuseColour(parameters.diffuseColor);
	light->setSpecularColour(parameters.specularColor);
	light->setPosition(parameters.position);
	light->setSpotlightFalloff(parameters.spotlightFalloff);
	light->setSpotlightInnerAngle(parameters.spotlightInnerAngle);
	light->setSpotlightOuterAngle(parameters.spotlightOuterAngle);
	light->setAttenuation(parameters.attenuationRange, parameters.attenuationConstant, parameters.attenuationLinear, parameters.attenuationQuadric);

	//Get Ogre parent
	Ogre::SceneNode* parentnode = 0;
	if ( parent == 0 ){
		parentnode = mSceneManager->getRootSceneNode();
	} else {
		parentnode = mSceneManager->getSceneNode(parent->name);
	}
	assert(parentnode);

	parentnode->attachObject(light);
}
        
void DefaultOgreMaxSceneCallback::onCamera( const OgreMax::Types::CameraParameters& params , const OgreMax::Types::NodeParameters * parent) {
   //Create the camera
	Ogre::Camera* camera = mSceneManager->createCamera(params.name);
    if (params.queryFlags != 0)
        camera->setQueryFlags(params.queryFlags);
    if (params.visibilityFlags != 0)
        camera->setVisibilityFlags(params.visibilityFlags);

	OgreMax::OgreMaxUtilities::SetObjectVisibility(camera, params.visibility);
	camera->setFOVy(Ogre::Radian(params.fov));
    camera->setAspectRatio(params.aspectRatio);
    camera->setProjectionType(params.projectionType);

    camera->setNearClipDistance(params.nearClip);
    camera->setFarClipDistance(params.farClip);
	camera->setPosition(params.position);
	camera->setOrientation(params.orientation);
	camera->setDirection(params.direction);

	//Get Ogre parent
	Ogre::SceneNode* parentnode = 0;
	if ( parent == 0 ){
		parentnode = mSceneManager->getRootSceneNode();
	} else {
		parentnode = mSceneManager->getSceneNode(parent->name);
	}
	assert(parentnode);

	parentnode->attachObject(camera);
}

void DefaultOgreMaxSceneCallback::onSkyBox( OgreMax::Types::SkyBoxParameters& parameters ) {
	//Create the sky
	mSceneManager->setSkyBox
		(
		parameters.enabled,
		parameters.material,
		parameters.distance,
		parameters.drawFirst,
		OgreMax::OgreMaxUtilities::GetOrientation(mUpAxis),
		parameters.resourceGroupName
		);

	Ogre::SceneNode * skyNode = mSceneManager->getSkyBoxNode();
	if (skyNode != 0)
	{
		skyNode->setOrientation(parameters.rotation);
		//TODO removed animation
		skyNode->setInitialState();
	}
}

void DefaultOgreMaxSceneCallback::onSkyDome( OgreMax::Types::SkyDomeParameters& parameters) {
	//Create the sky
	mSceneManager->setSkyDome
		(
		parameters.enabled,
		parameters.material,
		parameters.curvature,
		parameters.tiling,
		parameters.distance,
		parameters.drawFirst,
		OgreMax::OgreMaxUtilities::GetOrientation(mUpAxis),
		parameters.xSegments,
		parameters.ySegments,
		-1,
		parameters.resourceGroupName
		);

	Ogre::SceneNode * skyNode = mSceneManager->getSkyDomeNode();
	if (skyNode != 0)
	{
		skyNode->setOrientation(parameters.rotation);
		//TODO removed animation
		skyNode->setInitialState();
	}
}

void DefaultOgreMaxSceneCallback::onSkyPlane( OgreMax::Types::SkyPlaneParameters& parameters) {
	//Create the sky
	mSceneManager->setSkyPlane
		(
		parameters.enabled,
		parameters.plane,
		parameters.material,
		parameters.scale,
		parameters.tiling,
		parameters.drawFirst,
		parameters.bow,
		parameters.xSegments,
		parameters.ySegments,
		parameters.resourceGroupName
		);

	Ogre::SceneNode * skyNode = mSceneManager->getSkyPlaneNode();
	if (skyNode != 0) {
		skyNode->setOrientation(parameters.rotation);
		//TODO removed animation
		skyNode->setInitialState();
	}
}

void DefaultOgreMaxSceneCallback::onLoadClipping( Ogre::Real environmentNear, Ogre::Real environmentFar){
	mEnvironmentFar = environmentFar;
	mEnvironmentNear = environmentNear;
}

void DefaultOgreMaxSceneCallback::onFog ( const OgreMax::Types::FogParameters& fogParameters ){

	Ogre::Real linearStart = fogParameters.linearStart * mEnvironmentFar;
	Ogre::Real linearEnd = fogParameters.linearEnd * mEnvironmentFar;
	mSceneManager->setFog (fogParameters.mode,fogParameters.color,fogParameters.expDensity,linearStart,linearEnd);
}

void DefaultOgreMaxSceneCallback::onAmbientColour( const Ogre::ColourValue& colour ){
	mSceneManager->setAmbientLight(colour);					
}

void DefaultOgreMaxSceneCallback::onBackgroundColour( const Ogre::ColourValue& backgroundColor ){
    mViewport->setBackgroundColour(backgroundColor);
}

void DefaultOgreMaxSceneCallback::onNodeAnimation( const OgreMax::Types::NodeAnimationParameters& params, const OgreMax::Types::NodeParameters& node, const std::vector<OgreMax::Types::KeyFrame>& keyframes) {
	/*
	//Get Ogre node
	Ogre::SceneNode* ogreNode = mSceneManager->getSceneNode(node.name);
	assert(ogreNode);

    //Get existing animation or create new one
	Ogre::Animation* animation;
	if (mSceneManager->hasAnimation(params.name)) { 
		animation = mSceneManager->getAnimation(params.name);
	} else {
        //Create animation
        animation = mSceneManager->createAnimation(params.name, params.length);
        animation->setInterpolationMode(params.interpolationMode);
        animation->setRotationInterpolationMode(params.rotationInterpolationMode);
    }

    //Create animation track for node
	Ogre::NodeAnimationTrack* animationTrack = animation->createNodeTrack(animation->getNumNodeTracks() + 1, ogreNode);

	for (std::vector<OgreMax::Types::KeyFrame>::const_iterator i = keyframes.begin(); i != keyframes.end(); i++ ){
		Ogre::TransformKeyFrame* keyFrame = animationTrack->createNodeKeyFrame(keyTime);
		keyFrame->setTranslate(i->translation);
		keyFrame->setRotation(i->rotation);
		keyFrame->setScale(i->scale);
	}

    //Create a new animation state to track the animation
    /*if (GetAnimationState(params.name) == 0) {
        //No animation state has been created for the animation yet
        AnimationState* animationState = mSceneManager->createAnimationState(params.name);
        this->animationStates[params.name] = animationState;
        animationState->setEnabled(params.enable);
        animationState->setLoop(params.looping);
    }*/
}

void DefaultOgreMaxSceneCallback::onShadowProperties( OgreMax::Types::ShadowParameters& params ){

  //Set the shadow parameters
	if (params.shadowTechnique == Ogre::SHADOWTYPE_NONE) {
        //Turn off shadows
        this->mSceneManager->setShadowTechnique(Ogre::SHADOWTYPE_NONE);
    }
    else
    {
        //Turn on shadows

        this->mSceneManager->setShadowTechnique(params.shadowTechnique);
        this->mSceneManager->setShadowTextureSelfShadow(params.selfShadow);
        this->mSceneManager->setShadowColour(params.shadowColor);
		if (params.farDistance > 0){
			this->mSceneManager->setShadowFarDistance(params.farDistance);
		}

        //Set shadow texture parameters if necessary
        if (this->mSceneManager->isShadowTechniqueTextureBased())
        {
			Ogre::RenderSystem* renderSystem = Ogre::Root::getSingleton().getRenderSystem();

            //Determine texture size
            if (!renderSystem->getCapabilities()->hasCapability(Ogre::RSC_HWRENDER_TO_TEXTURE))
            {
                //Render to texture not supported, so ensure the shadow texture
                //size doesn't exceed the window size

                //Take minimum render window dimension as window size
                int windowSize = (int)std::min(this->mViewport->getWidth(), this->mViewport->getHeight());

                //Use the lesser of the texture and window sizes
                params.textureSize = std::min(params.textureSize, windowSize);
            }

            //If necessary, make sure the texture size is a power of two
			if (!OgreMax::OgreMaxUtilities::IsPowerOfTwo(params.textureSize) && !renderSystem->getCapabilities()->hasCapability(Ogre::RSC_NON_POWER_OF_2_TEXTURES)) {
				params.textureSize = OgreMax::OgreMaxUtilities::NextSmallestPowerOfTwo(params.textureSize);
            }

            if (params.pixelFormat == Ogre::PF_UNKNOWN) {
                //Choose a default format
				if (renderSystem->getName().find("GL") != Ogre::String::npos)
                {
	                //OpenGL performs better with a half-float format
	                params.pixelFormat = Ogre::PF_FLOAT16_R;
                }
                else
                {
	                //D3D is the opposite - if you ask for PF_FLOAT16_R you
	                //get an integer format instead. You can ask for PF_FLOAT16_GR
	                //but the precision doesn't work well
                    params.pixelFormat = Ogre::PF_FLOAT32_R;
                }
            }

            //Set texture size, count, pixel format
            this->mSceneManager->setShadowTextureSettings(params.textureSize, params.textureCount, params.pixelFormat);

            //Set other texture settings
            this->mSceneManager->setShadowDirLightTextureOffset(params.textureOffset);
            this->mSceneManager->setShadowTextureFadeStart(params.textureFadeStart);
            this->mSceneManager->setShadowTextureFadeEnd(params.textureFadeEnd);
            this->mSceneManager->setShadowTextureCasterMaterial(params.textureShadowCasterMaterial);
            this->mSceneManager->setShadowTextureReceiverMaterial(params.textureShadowReceiverMaterial);
        }

        //Set shadow camera setup
        Ogre::ShadowCameraSetupPtr shadowCameraSetupPtr;
        if (!params.cameraSetup.empty()) {
			Ogre::String typeLower = params.cameraSetup;
			Ogre::StringUtil::toLowerCase(typeLower);

			if (typeLower == "uniform") {
				shadowCameraSetupPtr = Ogre::ShadowCameraSetupPtr(new Ogre::DefaultShadowCameraSetup());
			}
			else if (typeLower == "uniformfocused") {
				shadowCameraSetupPtr = Ogre::ShadowCameraSetupPtr(new Ogre::FocusedShadowCameraSetup());
			}
			else if (typeLower == "lispsm") {
				shadowCameraSetupPtr = Ogre::ShadowCameraSetupPtr(new Ogre::LiSPSMShadowCameraSetup());
			}
			else if (typeLower == "planeoptimal")
			{
				shadowCameraSetupPtr = Ogre::ShadowCameraSetupPtr(new Ogre::PlaneOptimalShadowCameraSetup(new Ogre::MovablePlane(params.optimalPlane)));
			} 
			else {
				Ogre::StringUtil::StrStreamType errorMessage;
				errorMessage << "Invalid shadow camera setup specified: " << typeLower;
				OGRE_EXCEPT
					(
					Ogre::Exception::ERR_INVALIDPARAMS,
					errorMessage.str(),
					"OgreMaxScene::ParseShadowCameraSetup"
					);
			}
        }
        else {
            //Create the appropriate default setup
			shadowCameraSetupPtr = Ogre::ShadowCameraSetupPtr(new Ogre::DefaultShadowCameraSetup());
        }
	    this->mSceneManager->setShadowCameraSetup(shadowCameraSetupPtr);
	}
}

}
