#include "DefaultOgreMaxSceneCallback.h"

#include <OgreMaxUtilities.hpp>

#include <OgreAnimation.h>
#include <OgreSubEntity.h>
#include <OgreRoot.h>
#include <OgreBillboard.h>
#include <OgreMeshManager.h>
#include <OgreShadowCameraSetupFocused.h>
#include <OgreShadowCameraSetup.h>
#include <OgreShadowCameraSetupLiSPSM.h>
#include <OgreShadowCameraSetupPlaneOptimal.h>


namespace HovUni {

	DefaultOgreMaxSceneCallback::DefaultOgreMaxSceneCallback(Ogre::RenderWindow * window, Ogre::SceneManager * scenemanager):
	mSceneManager(scenemanager), mWindow(window)
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

void DefaultOgreMaxSceneCallback::addNodeAnimation( Ogre::SceneNode * node, std::vector<OgreMax::Types::NodeAnimation> * animation )
{
	if ( animation != 0 ){

		for ( std::vector<OgreMax::Types::NodeAnimation>::iterator i = animation->begin(); i != animation->end(); i++ ){
			//Get existing animation or create new one
			Ogre::Animation* animation;
			if (mSceneManager->hasAnimation(i->parameters.name)) { 
				animation = mSceneManager->getAnimation(i->parameters.name);
			} else {
				//Create animation
				animation = mSceneManager->createAnimation(i->parameters.name, i->parameters.length);
				animation->setInterpolationMode(i->parameters.interpolationMode);
				animation->setRotationInterpolationMode(i->parameters.rotationInterpolationMode);
			}

			//Create animation track for node
			Ogre::NodeAnimationTrack* animationTrack = animation->createNodeTrack(animation->getNumNodeTracks() + 1, node);

			for (std::vector<OgreMax::Types::KeyFrame>::const_iterator j = i->animationTrack.begin(); j != i->animationTrack.end(); j++ ){
				Ogre::TransformKeyFrame* keyFrame = animationTrack->createNodeKeyFrame(j->keyTime);
				keyFrame->setTranslate(j->translation);
				keyFrame->setRotation(j->rotation);
				keyFrame->setScale(j->scale);
			}

			//TODO??
			//Create a new animation state to track the animation
			/*if (GetAnimationState(params.name) == 0) {
				//No animation state has been created for the animation yet
				AnimationState* animationState = mSceneManager->createAnimationState(params.name);
				this->animationStates[params.name] = animationState;
				animationState->setEnabled(params.enable);
				animationState->setLoop(params.looping);
			}*/
		}

		OgreMax::OgreMaxUtilities::SetIdentityInitialState(node);
	}
	else {
		//set initial state
		node->setInitialState();
	}
}


void DefaultOgreMaxSceneCallback::onNode( OgreMax::Types::NodeParameters& nodeparameters, std::vector<OgreMax::Types::NodeAnimation> * animation, const OgreMax::Types::NodeParameters* parent){
	Ogre::String name = nodeparameters.name;
	
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

	addNodeAnimation(node,animation);

    //Set the node's visibility
	OgreMax::OgreMaxUtilities::SetNodeVisibility(node, nodeparameters.visibility);
}

void DefaultOgreMaxSceneCallback::onRootNode ( const Ogre::Vector3& position, const Ogre::Quaternion& rotation, const Ogre::Vector3& scale ){
	Ogre::SceneNode * scene = mSceneManager->getRootSceneNode();
	scene->setPosition(position);
	scene->setOrientation(rotation);
	scene->setScale(scale);
}


void DefaultOgreMaxSceneCallback::onLight( OgreMax::Types::LightParameters& parameters, const OgreMax::Types::Attachable * parent) {
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

	attachMovable(light,parent);
}

void DefaultOgreMaxSceneCallback::onEntity( OgreMax::Types::EntityParameters& entityparameters, const OgreMax::Types::Attachable * parent ){
    //Load the mesh
	bool isNewMesh = !Ogre::MeshManager::getSingleton().resourceExists(entityparameters.meshFile);
	Ogre::MeshPtr mesh = Ogre::MeshManager::getSingleton().load
        (
        entityparameters.meshFile,
        entityparameters.resourceGroupName,
        entityparameters.vertexBufferUsage, entityparameters.indexBufferUsage,
        entityparameters.vertexBufferShadowed, entityparameters.indexBufferShadowed
        );

    //Create entity
	Ogre::Entity* entity = this->mSceneManager->createEntity(entityparameters.name, entityparameters.meshFile);
    if (entityparameters.queryFlags != 0)
        entity->setQueryFlags(entityparameters.queryFlags);
    if (entityparameters.visibilityFlags != 0)
        entity->setVisibilityFlags(entityparameters.visibilityFlags);
	OgreMax::OgreMaxUtilities::SetObjectVisibility(entity, entityparameters.visibility);
    entity->setCastShadows(entityparameters.castShadows);
    entity->setRenderQueueGroup(entityparameters.renderQueue);
    entity->setRenderingDistance(entityparameters.renderingDistance);
	OgreMax::OgreMaxUtilities::SetCustomParameters(entity, entityparameters.customParameters);
    if (!entityparameters.materialFile.empty())
        entity->setMaterialName(entityparameters.materialFile);

    //Set subentity materials
    size_t subentityCount = std::min(entityparameters.subentities.size(), (size_t)entity->getNumSubEntities());
    for (size_t subentityIndex = 0; subentityIndex < subentityCount; subentityIndex++)
    {
		Ogre::SubEntity* subentity = entity->getSubEntity((unsigned int)subentityIndex);
        if (!entityparameters.subentities[subentityIndex].materialName.empty())
            subentity->setMaterialName(entityparameters.subentities[subentityIndex].materialName);
    }

	attachMovable(entity,parent);
}
void DefaultOgreMaxSceneCallback::onBillboardSet( OgreMax::Types::BillboardSetParameters& bilboardsetparameters, std::vector<OgreMax::Types::Billboard>& billboardset, std::vector<OgreMax::Types::CustomParameter>& customParameters, const OgreMax::Types::Attachable * parent ){

	//Create the particle system
	Ogre::BillboardSet* billboardSet = this->mSceneManager->createBillboardSet(bilboardsetparameters.name);
    if (bilboardsetparameters.queryFlags != 0)
        billboardSet->setQueryFlags(bilboardsetparameters.queryFlags);
    if (bilboardsetparameters.visibilityFlags != 0)
        billboardSet->setVisibilityFlags(bilboardsetparameters.visibilityFlags);
	OgreMax::OgreMaxUtilities::SetObjectVisibility(billboardSet, bilboardsetparameters.visibility);
    billboardSet->setRenderQueueGroup(bilboardsetparameters.renderQueue);
    billboardSet->setRenderingDistance(bilboardsetparameters.renderingDistance);
    if (!bilboardsetparameters.material.empty())
        billboardSet->setMaterialName(bilboardsetparameters.material);
    billboardSet->setDefaultWidth(bilboardsetparameters.width);
    billboardSet->setDefaultHeight(bilboardsetparameters.height);
	billboardSet->setBillboardType(bilboardsetparameters.billboardType);
    billboardSet->setBillboardOrigin(bilboardsetparameters.origin);
    billboardSet->setBillboardRotationType(bilboardsetparameters.rotationType);
	if (bilboardsetparameters.poolSize > 0)
        billboardSet->setPoolSize(bilboardsetparameters.poolSize);
    billboardSet->setAutoextend(bilboardsetparameters.autoExtendPool);
    billboardSet->setCullIndividually(bilboardsetparameters.cullIndividual);
    billboardSet->setSortingEnabled(bilboardsetparameters.sort);
    billboardSet->setUseAccurateFacing(bilboardsetparameters.accurateFacing);
	
	for ( std::vector<OgreMax::Types::Billboard>::iterator i = billboardset.begin(); i != billboardset.end(); i++ ){
		Ogre::Billboard* billboard = billboardSet->createBillboard(i->position, i->color);

		//Set rotation angle
		if (i->rotationAngle.valueRadians() != 0)
			billboard->setRotation(i->rotationAngle);

		//Set dimensions
		if (i->width != 0 && i->height != 0)
			billboard->setDimensions(i->width, i->height);

		//Set texture coordinate rectangle
		if (i->texCoordRectangle.width() != 0 && i->texCoordRectangle.height() != 0)
			billboard->setTexcoordRect(i->texCoordRectangle);
	}
	
	OgreMax::OgreMaxUtilities::SetCustomParameters(billboardSet, customParameters);

	attachMovable(billboardSet,parent);
}

void DefaultOgreMaxSceneCallback::onParticleSystem( OgreMax::Types::ParticleSystemParameters& parameters, const OgreMax::Types::Attachable * parent) {
	//Create the particle system
	Ogre::ParticleSystem* particleSystem = this->mSceneManager->createParticleSystem(parameters.name, parameters.file);
    if (parameters.queryFlags != 0)
        particleSystem->setQueryFlags(parameters.queryFlags);
    if (parameters.visibilityFlags != 0)
        particleSystem->setVisibilityFlags(parameters.visibilityFlags);
	OgreMax::OgreMaxUtilities::SetObjectVisibility(particleSystem, parameters.visibility);
	particleSystem->setRenderQueueGroup(parameters.renderQueue);
    particleSystem->setRenderingDistance(parameters.renderingDistance);

	attachMovable(particleSystem,parent);
}

void DefaultOgreMaxSceneCallback::onPlane( OgreMax::Types::PlaneParameters planeparameters, const OgreMax::Types::Attachable * parent) {
	/*
	TODO
	//Create movable plane if the name hasn't already been used
	Ogre::MovablePlane* movablePlane = 0;
    if (planeparameters.createMovablePlane)
    {
        String movablePlaneName;
		OgreMax::OgreMaxUtilities::CreateMovablePlaneName(movablePlaneName, parameters.planeName);
        if (this->movablePlanes.find(movablePlaneName) == this->movablePlanes.end())
        {
            movablePlane = new MovablePlane(movablePlaneName);
            this->movablePlanes[movablePlaneName] = movablePlane;
            movablePlane->normal = parameters.normal;
            movablePlane->d = parameters.distance;
        }
    }*/

    //Create plane mesh
	Ogre::Plane plane(planeparameters.normal, planeparameters.distance);
	Ogre::MeshManager::getSingleton().createPlane
        (
        planeparameters.planeName,
        planeparameters.resourceGroupName,
        plane,
        planeparameters.width, planeparameters.height,
        planeparameters.xSegments, planeparameters.ySegments,
        planeparameters.normals, planeparameters.numTexCoordSets,
        planeparameters.uTile, planeparameters.vTile,
        planeparameters.upVector,
        planeparameters.vertexBufferUsage, planeparameters.indexBufferUsage,
        planeparameters.vertexBufferShadowed, planeparameters.indexBufferShadowed
        );

    //Create plane entity
	Ogre::Entity* entity = this->mSceneManager->createEntity(planeparameters.name, planeparameters.planeName);
    if (planeparameters.queryFlags != 0)
        entity->setQueryFlags(planeparameters.queryFlags);
    if (planeparameters.visibilityFlags != 0)
        entity->setVisibilityFlags(planeparameters.visibilityFlags);
	OgreMax::OgreMaxUtilities::SetObjectVisibility(entity, planeparameters.visibility);
    entity->setCastShadows(planeparameters.castShadows);
    entity->setRenderQueueGroup(planeparameters.renderQueue);
    entity->setRenderingDistance(planeparameters.renderingDistance);
	OgreMax::OgreMaxUtilities::SetCustomParameters(entity, planeparameters.customParameters);
    if (!planeparameters.material.empty())
        entity->setMaterialName(planeparameters.material);

    //Attach plane entity and movable object to the node
	attachMovable(entity,parent);

	//TODO
    //if (movablePlane != 0)
    //    owner.Attach(movablePlane);
}

void DefaultOgreMaxSceneCallback::onCamera( OgreMax::Types::CameraParameters& params , const OgreMax::Types::Attachable * parent) {
   //Create the camera
	Ogre::Camera* camera = mSceneManager->createCamera(params.name);
    if (params.queryFlags != 0)
        camera->setQueryFlags(params.queryFlags);
    if (params.visibilityFlags != 0)
        camera->setVisibilityFlags(params.visibilityFlags);

	OgreMax::OgreMaxUtilities::SetObjectVisibility(camera, params.visibility);
	camera->setFOVy(params.fov);
    camera->setAspectRatio(params.aspectRatio);
    camera->setProjectionType(params.projectionType);

    camera->setNearClipDistance(params.nearClip);
    camera->setFarClipDistance(params.farClip);
	camera->setPosition(params.position);
	camera->setOrientation(params.orientation);
	camera->setDirection(params.direction);

	attachMovable(camera,parent);
}

void DefaultOgreMaxSceneCallback::onSkyBox( OgreMax::Types::SkyBoxParameters& parameters, std::vector<OgreMax::Types::NodeAnimation> * animation ) {
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
		addNodeAnimation(skyNode,animation);
	}
}

void DefaultOgreMaxSceneCallback::onSkyDome( OgreMax::Types::SkyDomeParameters& parameters, std::vector<OgreMax::Types::NodeAnimation> * animation) {
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
		addNodeAnimation(skyNode,animation);
	}
}

void DefaultOgreMaxSceneCallback::onSkyPlane( OgreMax::Types::SkyPlaneParameters& parameters, std::vector<OgreMax::Types::NodeAnimation> * animation) {
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
		addNodeAnimation(skyNode,animation);
	}
}

void DefaultOgreMaxSceneCallback::onClipping( Ogre::Real environmentNear, Ogre::Real environmentFar){
	mEnvironmentFar = environmentFar;
	mEnvironmentNear = environmentNear;
}

void DefaultOgreMaxSceneCallback::onFog ( OgreMax::Types::FogParameters& fogParameters ){

	Ogre::Real linearStart = fogParameters.linearStart * mEnvironmentFar;
	Ogre::Real linearEnd = fogParameters.linearEnd * mEnvironmentFar;
	mSceneManager->setFog (fogParameters.mode,fogParameters.color,fogParameters.expDensity,linearStart,linearEnd);
}

void DefaultOgreMaxSceneCallback::onAmbientColour( const Ogre::ColourValue& colour ){
	mSceneManager->setAmbientLight(colour);					
}

void DefaultOgreMaxSceneCallback::onBackgroundColour( const Ogre::ColourValue& backgroundColor ){
//    mViewport->setBackgroundColour(backgroundColor);
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
                int windowSize = (int)std::min(this->mWindow->getWidth(), this->mWindow->getHeight());

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
