#ifndef BLA
#define BLA

ShadowCameraSetup* CustomOgreMaxScene::ParseShadowCameraSetup(const String& type, Plane optimalPlane)
{
/*    String typeLower = type;
    StringUtil::toLowerCase(typeLower);

    if (typeLower == "uniform")
        return new DefaultShadowCameraSetup;
    else if (typeLower == "uniformfocused")
        return new FocusedShadowCameraSetup;
    else if (typeLower == "lispsm")
        return new LiSPSMShadowCameraSetup;
    else if (typeLower == "planeoptimal")
    {
        //The plane optimal setup requires a plane.
        //Create one if it hasn't already been created
        if (this->shadowOptimalPlane == 0)
            this->shadowOptimalPlane = new MovablePlane("_shadowOptimalPlane");

        //Update plane
        *(Plane*)this->shadowOptimalPlane = optimalPlane;

        return new PlaneOptimalShadowCameraSetup(this->shadowOptimalPlane);
    }

    StringUtil::StrStreamType errorMessage;
    errorMessage << "Invalid shadow camera setup specified: " << type;

    OGRE_EXCEPT
        (
        Exception::ERR_INVALIDPARAMS,
	    errorMessage.str(),
	    "CustomOgreMaxScene::ParseShadowCameraSetup"
        );*/

	return 0;
}

//void CustomOgreMaxScene::FinishLoadingLookAndTrackTargets()
//{
   /* //Resolve look targets
    for (LookTargetList::iterator lookTarget = this->lookTargets.begin();
        lookTarget != this->lookTargets.end();
        ++lookTarget)
    {
        SceneNode* lookTargetNode = GetSceneNode(lookTarget->nodeName, false);

        //Get position
        Vector3 position;
        if (lookTarget->isPositionSet)
            position = lookTarget->position;
        else
        {
            lookTarget->relativeTo = Node::TS_WORLD;
            position = lookTargetNode->_getDerivedPosition();
        }

        //Set look at depending on whether we have a node or camera
        if (lookTarget->sourceNode != 0)
            lookTarget->sourceNode->lookAt(position, lookTarget->relativeTo, lookTarget->localDirection);
        else if (lookTarget->sourceCamera != 0)
            lookTarget->sourceCamera->lookAt(position);
    }
    this->lookTargets.clear();

    //Resolve track targets
    for (TrackTargetList::iterator trackTarget = this->trackTargets.begin();
        trackTarget != this->trackTargets.end();
        ++trackTarget)
    {
        SceneNode* trackTargetNode = GetSceneNode(trackTarget->nodeName, false);

        //Set tracking depending on whether we have a node or camera
        if (trackTarget->sourceNode != 0)
            trackTarget->sourceNode->setAutoTracking(true, trackTargetNode, trackTarget->localDirection, trackTarget->offset);
        else if (trackTarget->sourceCamera != 0)
            trackTarget->sourceCamera->setAutoTracking(true, trackTargetNode, trackTarget->offset);
    }
    this->trackTargets.clear();*/
//}

void CustomOgreMaxScene::LoadInstancedGeometries(const TiXmlElement* objectElement)
{
 /*   //Ensure instancing is supported
    if (!Root::getSingleton().getRenderSystem()->getCapabilities()->hasCapability(RSC_VERTEX_PROGRAM))
	{
		OGRE_EXCEPT
            (
            Exception::ERR_INVALIDPARAMS,
            "Instanced geometry is not supported by the current render system and/or video card",
            "CustomOgreMaxScene::LoadInstancedGeometry"
            );
	}

    //Read all the instanced geometries
    String elementName;
    const TiXmlElement* childElement = 0;
    while (childElement = OgreMaxUtilities::IterateChildElements(objectElement, childElement))
    {
        elementName = childElement->Value();

        if (elementName == "instancedGeometry")
            LoadInstancedGeometry(childElement);
    }*/
}

void CustomOgreMaxScene::LoadInstancedGeometry(const TiXmlElement* objectElement)
{
/*    String name = OgreMaxUtilities::GetStringAttribute(objectElement, "name");
    bool castShadows = OgreMaxUtilities::GetBoolAttribute(objectElement, "castShadows", true);
    ObjectVisibility visibility = OgreMaxUtilities::GetObjectVisibilityAttribute(objectElement, "visible");
    unsigned int batchCount = OgreMaxUtilities::GetUIntAttribute(objectElement, "batchCount", 0);
    String renderQueue = OgreMaxUtilities::GetStringAttribute(objectElement, "renderQueue");
    Real renderingDistance = OgreMaxUtilities::GetRealAttribute(objectElement, "renderingDistance", 0);
    Vector3 origin = Vector3::ZERO;
    Vector3 dimensions(1000000, 1000000, 1000000);
    const TiXmlElement* entitiesElement = 0;

    //Iterate over all the child elements
    String elementName;
    const TiXmlElement* childElement = 0;
    while (childElement = OgreMaxUtilities::IterateChildElements(objectElement, childElement))
    {
        elementName = childElement->Value();

        if (elementName == "origin")
            origin = OgreMaxUtilities::LoadXYZ(childElement);
        else if (elementName == "dimensions")
            dimensions = OgreMaxUtilities::LoadXYZ(childElement);
        else if (elementName == "entities")
            entitiesElement = childElement;
    }

    //Create the instanced geometry
    InstancedGeometry* instancedGeometry = this->sceneManager->createInstancedGeometry(name);
    instancedGeometry->setCastShadows(castShadows);
    OgreMaxUtilities::SetObjectVisibility(instancedGeometry, visibility);
    instancedGeometry->setOrigin(origin);
    instancedGeometry->setBatchInstanceDimensions(dimensions);
    if (!renderQueue.empty())
        instancedGeometry->setRenderQueueGroup(OgreMaxUtilities::ParseRenderQueue(renderQueue));
    instancedGeometry->setRenderingDistance(renderingDistance);

    //Add the entities
    childElement = 0;
    while (childElement = OgreMaxUtilities::IterateChildElements(entitiesElement, childElement))
    {
        elementName = childElement->Value();

        if (elementName == "entity")
            LoadInstancedGeometryEntity(childElement, instancedGeometry);
    }

    //Build the instanced geometry
    instancedGeometry->build();

    //Add additional batch instances
    for (unsigned int batchIndex = 0; batchIndex < batchCount; batchIndex++)
        instancedGeometry->addBatchInstance();*/
}

void CustomOgreMaxScene::LoadInstancedGeometryEntity(const TiXmlElement* objectElement)
{
/*    static const String TEMP_ENTITY_NAME("__instancedGeometryEntity");

    String meshFile = OgreMaxUtilities::GetStringAttribute(objectElement, "meshFile");
    Vector3 position = Vector3::ZERO;
    Quaternion rotation = Quaternion::IDENTITY;
    Vector3 scale = Vector3::UNIT_SCALE;
    std::vector<EntityParameters::Subentity> subentities;

    String elementName;
    const TiXmlElement* childElement = 0;
    while (childElement = OgreMaxUtilities::IterateChildElements(objectElement, childElement))
    {
        elementName = childElement->Value();

        if (elementName == "position")
            position = OgreMaxUtilities::LoadXYZ(childElement);
        else if (elementName == "rotation")
            rotation = OgreMaxUtilities::LoadRotation(childElement);
        else if (elementName == "scale")
            scale = OgreMaxUtilities::LoadXYZ(childElement);
        else if (elementName == "subentities")
            OgreMaxUtilities::LoadSubentities(childElement, subentities);
    }

    if (!meshFile.empty())
    {
        //Create temporary entity
        Entity* entity = OgreMaxUtilities::CreateEntity(this->sceneManager, TEMP_ENTITY_NAME, meshFile, subentities);

        //Add entity to the static geometry
        instancedGeometry->addEntity(entity, position, rotation, scale);

        //Destroy entity
        this->sceneManager->destroyEntity(entity);
    }*/
}

void CustomOgreMaxScene::LoadStaticGeometries(const TiXmlElement* objectElement)
{
/*    //Read all the static geometries
    String elementName;
    const TiXmlElement* childElement = 0;
    while (childElement = OgreMaxUtilities::IterateChildElements(objectElement, childElement))
    {
        elementName = childElement->Value();

        if (elementName == "staticGeometry")
            LoadStaticGeometry(childElement);
    }*/
}

void CustomOgreMaxScene::LoadStaticGeometry(const TiXmlElement* objectElement)
{
 /*   String name = OgreMaxUtilities::GetStringAttribute(objectElement, "name");
    bool castShadows = OgreMaxUtilities::GetBoolAttribute(objectElement, "castShadows", true);
    ObjectVisibility visibility = OgreMaxUtilities::GetObjectVisibilityAttribute(objectElement, "visible");
    String renderQueue = OgreMaxUtilities::GetStringAttribute(objectElement, "renderQueue");
    Real renderingDistance = OgreMaxUtilities::GetRealAttribute(objectElement, "renderingDistance", 0);
    Vector3 origin = Vector3::ZERO;
    Vector3 dimensions(1000000, 1000000, 1000000);
    const TiXmlElement* entitiesElement = 0;

    //Iterate over all the child elements
    String elementName;
    const TiXmlElement* childElement = 0;
    while (childElement = OgreMaxUtilities::IterateChildElements(objectElement, childElement))
    {
        elementName = childElement->Value();

        if (elementName == "origin")
            origin = OgreMaxUtilities::LoadXYZ(childElement);
        else if (elementName == "dimensions")
            dimensions = OgreMaxUtilities::LoadXYZ(childElement);
        else if (elementName == "entities")
            entitiesElement = childElement;
    }

    //Create the instanced geometry
    StaticGeometry* staticGeometry = this->sceneManager->createStaticGeometry(name);
    staticGeometry->setCastShadows(castShadows);
    OgreMaxUtilities::SetObjectVisibility(staticGeometry, visibility);
    staticGeometry->setOrigin(origin);
    staticGeometry->setRegionDimensions(dimensions);
    if (!renderQueue.empty())
        staticGeometry->setRenderQueueGroup(OgreMaxUtilities::ParseRenderQueue(renderQueue));
    staticGeometry->setRenderingDistance(renderingDistance);

    //Add the entities
    childElement = 0;
    while (childElement = OgreMaxUtilities::IterateChildElements(entitiesElement, childElement))
    {
        elementName = childElement->Value();

        if (elementName == "entity")
            LoadStaticGeometryEntity(childElement, staticGeometry);
    }

    //Build the static geometry
    staticGeometry->build();*/
}

void CustomOgreMaxScene::LoadStaticGeometryEntity(const TiXmlElement* objectElement)
{
 /*   static const String TEMP_ENTITY_NAME("__staticGeometryEntity");

    String meshFile = OgreMaxUtilities::GetStringAttribute(objectElement, "meshFile");
    Vector3 position = Vector3::ZERO;
    Quaternion rotation = Quaternion::IDENTITY;
    Vector3 scale = Vector3::UNIT_SCALE;
    std::vector<EntityParameters::Subentity> subentities;

    String elementName;
    const TiXmlElement* childElement = 0;
    while (childElement = OgreMaxUtilities::IterateChildElements(objectElement, childElement))
    {
        elementName = childElement->Value();

        if (elementName == "position")
            position = OgreMaxUtilities::LoadXYZ(childElement);
        else if (elementName == "rotation")
            rotation = OgreMaxUtilities::LoadRotation(childElement);
        else if (elementName == "scale")
            scale = OgreMaxUtilities::LoadXYZ(childElement);
        else if (elementName == "subentities")
            OgreMaxUtilities::LoadSubentities(childElement, subentities);
    }

    if (!meshFile.empty())
    {
        //Create temporary entity
        Entity* entity = OgreMaxUtilities::CreateEntity(this->sceneManager, TEMP_ENTITY_NAME, meshFile, subentities);
        
        //Add entity to the static geometry
        staticGeometry->addEntity(entity, position, rotation, scale);

        //Destroy entity
        this->sceneManager->destroyEntity(entity);
    }*/
}

void CustomOgreMaxScene::LoadResourceLocations(const TiXmlElement* objectElement)
{
    //Exit early if resource locations are not allowed
    if (!this->loadedFromFileSystem)
        return;

    size_t locationCount = 0;

    //Iterate over all the resource groups
    String elementName;
    const TiXmlElement* childElement = 0;
    while (childElement = OgreMaxUtilities::IterateChildElements(objectElement, childElement))
    {
        elementName = childElement->Value();

        if (elementName == "resourceLocation")
        {
            //Name
            Ogre::String name = OgreMaxUtilities::GetStringAttribute(childElement, "name");
            if (!this->baseResourceLocation.empty())
                Ogre::String name = OgreMaxUtilities::JoinPath(this->baseResourceLocation, name);

            //Type
            Ogre::String type = OgreMaxUtilities::GetStringAttribute(childElement, "type");

            //Recursive
            bool recursive = OgreMaxUtilities::GetBoolAttribute(childElement, "recursive", false);

			if ( this->callback )
				this->callback->onResourceLocation(name,type,recursive);
        }
    }
}


/*
    //Create movable plane if the name hasn't already been used
    MovablePlane* movablePlane = 0;
    if (parameters.createMovablePlane)
    {
        String movablePlaneName;
        OgreMaxUtilities::CreateMovablePlaneName(movablePlaneName, parameters.planeName);
        if (this->movablePlanes.find(movablePlaneName) == this->movablePlanes.end())
        {
            movablePlane = new MovablePlane(movablePlaneName);
            this->movablePlanes[movablePlaneName] = movablePlane;
            movablePlane->normal = parameters.normal;
            movablePlane->d = parameters.distance;
        }
    }

    //Create plane mesh
    Plane plane(parameters.normal, parameters.distance);
	MeshManager::getSingleton().createPlane
        (
        parameters.planeName,
        parameters.resourceGroupName,
        plane,
        parameters.width, parameters.height,
        parameters.xSegments, parameters.ySegments,
        parameters.normals, parameters.numTexCoordSets,
        parameters.uTile, parameters.vTile,
        parameters.upVector,
        parameters.vertexBufferUsage, parameters.indexBufferUsage,
        parameters.vertexBufferShadowed, parameters.indexBufferShadowed
        );

    //Create plane entity
    Entity* entity = this->sceneManager->createEntity(parameters.name, parameters.planeName);
    if (parameters.queryFlags != 0)
        entity->setQueryFlags(parameters.queryFlags);
    if (parameters.visibilityFlags != 0)
        entity->setVisibilityFlags(parameters.visibilityFlags);
    OgreMaxUtilities::SetObjectVisibility(entity, parameters.visibility);
    entity->setCastShadows(parameters.castShadows);
    entity->setRenderQueueGroup(parameters.renderQueue);
    entity->setRenderingDistance(parameters.renderingDistance);
    OgreMaxUtilities::SetCustomParameters(entity, parameters.customParameters);
    if (!parameters.material.empty())
        entity->setMaterialName(parameters.material);
    objectExtraData->object = entity;

    //Attach plane entity and movable object to the node
    owner.Attach(entity);
    if (movablePlane != 0)
        owner.Attach(movablePlane);

    //Add to loaded objects map
    this->loadedObjects[parameters.name] = entity;



   //Create the bilboard system
    BillboardSet* billboardSet = this->sceneManager->createBillboardSet(name);
    if (queryFlags != 0)
        billboardSet->setQueryFlags(queryFlags);
    if (visibilityFlags != 0)
        billboardSet->setVisibilityFlags(visibilityFlags);
    OgreMaxUtilities::SetObjectVisibility(billboardSet, visibility);
    billboardSet->setRenderQueueGroup(OgreMaxUtilities::ParseRenderQueue(renderQueue));
    billboardSet->setRenderingDistance(renderingDistance);
    if (!material.empty())
        billboardSet->setMaterialName(material);
    billboardSet->setDefaultWidth(width);
    billboardSet->setDefaultHeight(height);
    billboardSet->setBillboardType(OgreMaxUtilities::ParseBillboardType(type));
    billboardSet->setBillboardOrigin(OgreMaxUtilities::ParseBillboardOrigin(origin));
    billboardSet->setBillboardRotationType(OgreMaxUtilities::ParseBillboardRotationType(rotationType));
    if (poolSize > 0)
        billboardSet->setPoolSize(poolSize);
    billboardSet->setAutoextend(autoExtendPool);
    billboardSet->setCullIndividually(cullIndividual);
    billboardSet->setSortingEnabled(sort);
    billboardSet->setUseAccurateFacing(accurateFacing);

	billboardSet->setCommonDirection(commonDirection);
	billboardSet->setCommonUpVector(commonUpVector);


    //Create the particle system
    ParticleSystem* particleSystem = this->sceneManager->createParticleSystem(name, file);
    if (queryFlags != 0)
        particleSystem->setQueryFlags(queryFlags);
    if (visibilityFlags != 0)
        particleSystem->setVisibilityFlags(visibilityFlags);
    OgreMaxUtilities::SetObjectVisibility(particleSystem, visibility);
    particleSystem->setRenderQueueGroup(OgreMaxUtilities::ParseRenderQueue(renderQueue));
    particleSystem->setRenderingDistance(renderingDistance);


    //Attach particle system to the node
    owner.Attach(particleSystem);

    //Add to loaded objects map
    this->loadedObjects[name] = particleSystem;

bool CustomOgreMaxScene::AddResourceLocation(const ResourceLocation& resourceLocation)
{
    //Normalize the resource location by expanding the name to a full path
    ResourceLocation normalizedResourceLocation = resourceLocation;
    OgreMaxUtilities::MakeFullPath(normalizedResourceLocation.name);

    //Determine whether resource location has already been added
    bool isNewResourceLocation =
        this->resourceLocations.find(normalizedResourceLocation) == this->resourceLocations.end();

    //Add resource location if it's new
    if (isNewResourceLocation)
    {
        //Hold onto the resource location for later
        this->resourceLocations.insert(normalizedResourceLocation);
    }

    return isNewResourceLocation;
}

void CustomOgreMaxScene::CommitResourceLocations()
{
    //Count the number of uninitialized locations
    int newResourceLocationCount = 0;
    for (ResourceLocations::iterator resourceLocationIterator = this->resourceLocations.begin();
        resourceLocationIterator != this->resourceLocations.end();
        ++resourceLocationIterator)
    {
        if (!resourceLocationIterator->initialized)
        {
            newResourceLocationCount++;

            //Add resource location to Ogre
            ResourceGroupManager::getSingleton().addResourceLocation
                (
                resourceLocationIterator->name,
                resourceLocationIterator->type,
                this->defaultResourceGroupName,
                resourceLocationIterator->recursive
                );

            //The resource location is no longer uninitialized
            //This seems to fix a compiler error with GCC
            const_cast<ResourceLocation&>(*resourceLocationIterator).initialized = true;
        }
    }

    if (newResourceLocationCount > 0)
        ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void CustomOgreMaxScene::preRenderTargetUpdate(const RenderTargetEvent& e)
{
    RenderTargetMap::iterator renderTarget = this->renderTargets.find(e.source);
    if (renderTarget != this->renderTargets.end())
    {
        LoadedRenderTexture& loadedRenderTexture = *renderTarget->second;
        RenderTextureParameters& params = loadedRenderTexture.parameters;

        //Set scheme
        this->previousActiveScheme = MaterialManager::getSingleton().getActiveScheme();
        if (params.scheme.empty())
            MaterialManager::getSingleton().setActiveScheme(MaterialManager::DEFAULT_SCHEME_NAME);
        else
            MaterialManager::getSingleton().setActiveScheme(params.scheme);

        //Hide all the hidden objects
        if (loadedRenderTexture.renderObjectNode != 0 && params.hideRenderObject)
            loadedRenderTexture.renderObjectNode->setVisible(false, false);
        loadedRenderTexture.hiddenObjects.Hide();

        //Show all the exclusive objects
        loadedRenderTexture.exclusiveObjects.Show();

        //If render target is for a cube map texture, update cube face camera positions
        if (params.textureType == TEX_TYPE_CUBE_MAP)
        {
            //Get the position from which the cube map will be rendered
            Vector3 position;
            loadedRenderTexture.GetReferencePosition(position);

            //Set position into cube face cameras
            size_t faceCount = loadedRenderTexture.renderTexture->getNumFaces();
            for (size_t faceIndex = 0; faceIndex < faceCount; faceIndex++)
                loadedRenderTexture.cubeFaceCameras[faceIndex]->setPosition(position);
        }
    }
}

void CustomOgreMaxScene::postRenderTargetUpdate(const RenderTargetEvent& e)
{
    RenderTargetMap::iterator renderTarget = this->renderTargets.find(e.source);
    if (renderTarget != this->renderTargets.end())
    {
        LoadedRenderTexture& loadedRenderTexture = *renderTarget->second;
        RenderTextureParameters& params = loadedRenderTexture.parameters;

        //Restore scheme
        MaterialManager::getSingleton().setActiveScheme(this->previousActiveScheme);

        //Show all the hidden objects
        if (loadedRenderTexture.renderObjectNode != 0 && params.hideRenderObject)
            loadedRenderTexture.renderObjectNode->setVisible(true, false);
        loadedRenderTexture.hiddenObjects.Show();

        //Hide all the exclusive objects
        loadedRenderTexture.exclusiveObjects.Hide();
    }
}*/

    //Create scene manager
    /*if (this->sceneManager == 0)
    {
        //Create the scene manager
        String sceneManager = OgreMaxUtilities::GetStringAttribute(objectElement, "sceneManager", "generic");
        SceneType sceneType;
        if (OgreMaxUtilities::ParseSceneManager(sceneManager, sceneType))
            this->sceneManager = Root::getSingleton().createSceneManager(sceneType, this->sceneExtraData.id);
        else
            this->sceneManager = Root::getSingleton().createSceneManager(sceneManager, this->sceneExtraData.id);

        //Notify callback
        if (this->callback != 0)
            this->callback->CreatedSceneManager(this, this->sceneManager);
    }*/

    //Get the root node
    /*if (this->rootNode == 0)
        this->rootNode = this->sceneManager->getRootSceneNode();
	*/


   /** A interface that receives notifications during the loading of the scene */
    class OgreMaxSceneCallback
    {
    public:
        virtual ~OgreMaxSceneCallback() {}

		/**
		 * Called when the scene file was found
		 * @param filename
		 * @param resourcegroupname
		 */
		virtual void onSceneFile( const Ogre::String& fileName, Ogre::String& resourceGroupName) {}

		/** 
		 * Called before a scene is to be loaded. 
		 * At this stage the xml has been parsed successfuly and is placed in memory.
		 */
        virtual void StartedLoad() {}

		virtual void onNode( const OgreMax::Types::NodeParameters& params){ 	
			/*node->setPosition(parameters.position);

			node->setOrientation(parameters.orientation);	
			node->setScale(parameters.scale);

			//Set the initial state if it hasn't already been set
			if (!isInitialStateSet)
				node->setInitialState();
			OgreMaxUtilities::SetNodeVisibility(node, visibility);*/
		}


		virtual void onRootNode ( const OgreMax::Types::NodeParameters nodeparam){
/*
			 this->rootNode->setScale();
			 this->rootNode->setScale();
*/
		}


		virtual void onExternalUserData( const OgreMax::Types::ExternalUserData& externalud){
		}

		/**
		 * Called when the scene tag has been parsed, a check to Ogre version has been done here
		 * @param formatVersion, version of scene format
		 * @param minOgreVersion
		 * @param ogreMaxVersion
		 * @param author
		 * @param upaxis
		 * @param unitsPerMeter
		 * @param unitType
		 */
		virtual void onSceneData( const OgreMax::Version& formatVersion, const OgreMax::Version& minOgreVersion, const OgreMax::Version& ogreMaxVersion, const Ogre::String& author, const Ogre::String& application, Types::UpAxis upAxis, Ogre::Real unitsPerMeter, const Ogre::String& unitType) {}

        /**
		 * Called when scene user data is loaded. Will only be called if there is user data
		 */
        virtual void onSceneUserData(const Ogre::String& userDataReference, const Ogre::String& userData) {}


		virtual void onLoadClipping( Ogre::Real environmentNear, Ogre::Real environmentFar){
			//THIS IS THE CODE THAT USED TO BE IN OGREMAX SCENE, THIS CODE SHOULD NOT BE USED HERE BUT IS PLACED HERE FOR LATER
			/*
			NOTHING in de ogremax, look it up yourself
			*/
		}

		virtual void onShadowProperties( const OgreMax::Types::ShadowParameters& parameter ){
			//THIS IS THE CODE THAT USED TO BE IN OGREMAX SCENE, THIS CODE SHOULD NOT BE USED HERE BUT IS PLACED HERE FOR LATER
		/*
  //Set the shadow parameters
    if (params.shadowTechnique == SHADOWTYPE_NONE)
    {
        //Turn off shadows
        this->sceneManager->setShadowTechnique(SHADOWTYPE_NONE);
    }
    else
    {
        //Turn on shadows

        this->sceneManager->setShadowTechnique(params.shadowTechnique);
        this->sceneManager->setShadowTextureSelfShadow(params.selfShadow);
        this->sceneManager->setShadowColour(params.shadowColor);
        if (params.farDistance > 0)
            this->sceneManager->setShadowFarDistance(params.farDistance);

        //Set shadow texture parameters if necessary
        if (this->sceneManager->isShadowTechniqueTextureBased())
        {
            RenderSystem* renderSystem = Root::getSingleton().getRenderSystem();

            //Determine texture size
            if (!renderSystem->getCapabilities()->hasCapability(RSC_HWRENDER_TO_TEXTURE))
            {
                //Render to texture not supported, so ensure the shadow texture
                //size doesn't exceed the window size

                //Take minimum render window dimension as window size
                int windowSize = 4096;
                if (this->renderWindows->Start())
                {
                    do
                    {
                        RenderWindow* renderWindow = this->renderWindows->GetCurrent();
                        windowSize = (int)std::min(renderWindow->getWidth(), renderWindow->getHeight());
                    }while (this->renderWindows->MoveNext());
                }

                //Use the lesser of the texture and window sizes
                params.textureSize = std::min(params.textureSize, windowSize);
            }

            //If necessary, make sure the texture size is a power of two
            if (!OgreMaxUtilities::IsPowerOfTwo(params.textureSize) &&
                !renderSystem->getCapabilities()->hasCapability(RSC_NON_POWER_OF_2_TEXTURES))
            {
                params.textureSize = OgreMaxUtilities::NextSmallestPowerOfTwo(params.textureSize);
            }

            //Determine texture pixel format
            if (this->callback != 0)
                this->callback->CreatingShadowTextures(this, params);
            if (params.pixelFormat == PF_UNKNOWN)
            {
                //Choose a default format
                if (renderSystem->getName().find("GL") != String::npos)
                {
	                //OpenGL performs better with a half-float format
	                params.pixelFormat = PF_FLOAT16_R;
                }
                else
                {
	                //D3D is the opposite - if you ask for PF_FLOAT16_R you
	                //get an integer format instead. You can ask for PF_FLOAT16_GR
	                //but the precision doesn't work well
                    params.pixelFormat = PF_FLOAT32_R;
                }
            }

            //Set texture size, count, pixel format
            this->sceneManager->setShadowTextureSettings(params.textureSize, params.textureCount, params.pixelFormat);

            //Set other texture settings
            this->sceneManager->setShadowDirLightTextureOffset(params.textureOffset);
            this->sceneManager->setShadowTextureFadeStart(params.textureFadeStart);
            this->sceneManager->setShadowTextureFadeEnd(params.textureFadeEnd);
            this->sceneManager->setShadowTextureCasterMaterial(params.textureShadowCasterMaterial);
            this->sceneManager->setShadowTextureReceiverMaterial(params.textureShadowReceiverMaterial);
        }

        //Set shadow camera setup
        ShadowCameraSetupPtr shadowCameraSetupPtr;
        if (!params.cameraSetup.empty())
        {
            //Use the specified setup
            shadowCameraSetupPtr = ShadowCameraSetupPtr(ParseShadowCameraSetup(params.cameraSetup, params.optimalPlane));
        }
        else
        {
            //Create the appropriate default setup
            shadowCameraSetupPtr = ShadowCameraSetupPtr(new DefaultShadowCameraSetup());
        }
	    this->sceneManager->setShadowCameraSetup(shadowCameraSetupPtr);
		}
		*/
		}

		virtual void onBackgroundColour( const Ogre::ColourValue& colour ){
		//THIS IS THE CODE THAT USED TO BE IN OGREMAX SCENE, THIS CODE SHOULD NOT BE USED HERE BUT IS PLACED HERE FOR LATER
		/*
		            //Set all viewports to the specified background color
            if (this->renderWindows->Start())
            {
                do
                {
                    RenderWindow* renderWindow = this->renderWindows->GetCurrent();
                    unsigned short viewportCount = renderWindow->getNumViewports();
                    for (unsigned short viewportIndex = 0; viewportIndex < viewportCount; viewportIndex++)
                        renderWindow->getViewport(viewportIndex)->setBackgroundColour(backgroundColor);
                }while (this->renderWindows->MoveNext());
            }
		*/					
		}

		virtual void onAmbientColour( const Ogre::ColourValue& colour ){
		//THIS IS THE CODE THAT USED TO BE IN OGREMAX SCENE, THIS CODE SHOULD NOT BE USED HERE BUT IS PLACED HERE FOR LATER
		/*
		this->sceneManager->setAmbientLight(colour);
		*/					
		}

		virtual void onFog ( const OgreMax::Types::FogParameters& fog ){
			//THIS IS THE CODE THAT USED TO BE IN OGREMAX SCENE, THIS CODE SHOULD NOT BE USED HERE BUT IS PLACED HERE FOR LATER
/*
			Real linearStart = this->fogParameters.linearStart * this->environmentFar;
			Real linearEnd = this->fogParameters.linearEnd * this->environmentFar;
			this->sceneManager->setFog
            (
            this->fogParameters.mode,
            this->fogParameters.color,
            this->fogParameters.expDensity,
            linearStart,
            linearEnd
            );
*/
		}




        //Called when resource locations are loaded. Will only be called if there are resource locations
        //virtual void LoadingResourceLocations(const OgreMaxScene* scene) {}
        //virtual void LoadedResourceLocations(const OgreMaxScene* scene, const OgreMaxScene::ResourceLocations& resourceLocations) {}

        //Resource-based callbacks, called before a resource is created
        //The main purpose of these callbacks is to get the resource group name for the
        //resource being loaded, though other parameters may be modified as well
        virtual void onRenderTexture(const OgreMaxScene* scene, OgreMax::Types::RenderTextureParameters& renderTextureParameters) {}

       
		


        virtual void onSkyBox( OgreMax::Types::SkyBoxParameters& skyBoxParameters ) {
			//THIS IS THE CODE THAT USED TO BE IN OGREMAX SCENE, THIS CODE SHOULD NOT BE USED HERE BUT IS PLACED HERE FOR LATER

		   /*//Create the sky
			this->sceneManager->setSkyBox
				(
				parameters.enabled,
				parameters.material,
				parameters.distance,
				parameters.drawFirst,
				OgreMaxUtilities::GetOrientation(this->upAxis),
				parameters.resourceGroupName
				);
			this->skyNode = this->sceneManager->getSkyBoxNode();
			if (this->skyNode != 0)
			{
				this->skyNode->setOrientation(parameters.rotation);

				//Add animations
				if (animationsElement != 0)
				{
					LoadNodeAnimations(animationsElement, this->skyNode);
					OgreMaxUtilities::SetIdentityInitialState(this->skyNode);
				}
				else
					this->skyNode->setInitialState();
			}*/	
		}

        virtual void onSkyDome( OgreMax::Types::SkyDomeParameters& skyDomeParameters) {
			//THIS IS THE CODE THAT USED TO BE IN OGREMAX SCENE, THIS CODE SHOULD NOT BE USED HERE BUT IS PLACED HERE FOR LATER
			/*	
			 //Create the sky
			this->sceneManager->setSkyDome
				(
				parameters.enabled,
				parameters.material,
				parameters.curvature,
				parameters.tiling,
				parameters.distance,
				parameters.drawFirst,
				OgreMaxUtilities::GetOrientation(this->upAxis),
				parameters.xSegments,
				parameters.ySegments,
				-1,
				parameters.resourceGroupName
				);
			this->skyNode = this->sceneManager->getSkyDomeNode();
			if (this->skyNode != 0)
			{
				this->skyNode->setOrientation(parameters.rotation);

				//Add animations
				if (animationsElement != 0)
				{
					LoadNodeAnimations(animationsElement, this->skyNode);
					OgreMaxUtilities::SetIdentityInitialState(this->skyNode);
				}
				else
					this->skyNode->setInitialState();
			}*/
		}

		virtual void onExternal(const OgreMax::Types::ExternalItem& item) {
		}

        virtual void onSkyPlane( OgreMax::Types::SkyPlaneParameters& skyPlaneParameters) {
		//THIS IS THE CODE THAT USED TO BE IN OGREMAX SCENE, THIS CODE SHOULD NOT BE USED HERE BUT IS PLACED HERE FOR LATER
			/*
			  //Create the sky
				this->sceneManager->setSkyPlane
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
				this->skyNode = this->sceneManager->getSkyPlaneNode();
				if (this->skyNode != 0)
				{
					this->skyNode->setOrientation(parameters.rotation);

					//Add animations
					if (animationsElement != 0)
					{
						LoadNodeAnimations(animationsElement, this->skyNode);
						OgreMaxUtilities::SetIdentityInitialState(this->skyNode);
					}
					else
						this->skyNode->setInitialState();
				}
			*/
		}


        virtual void onEntity( OgreMax::Types::EntityParameters& parameters) {}
        virtual void onPlane( OgreMax::Types::PlaneParameters& parameters) {}

        /**
         * Called right before an Ogre animation is created. The parameters may be modified.
         * In particular modifying the length is useful in cases where there are multiple node animation
         * tracks on the animation, each of which starts and ends at different times.
         */
        virtual void LoadingNodeAnimation(const OgreMaxScene* scene, Types::NodeAnimationParameters& parameters) {}

		//MovableObject-creation callbacks
		virtual void onLight(const OgreMax::Types::LightParameters& light) {
		//THIS IS THE CODE THAT USED TO BE IN OGREMAX SCENE, THIS CODE SHOULD NOT BE USED HERE BUT IS PLACED HERE FOR LATER
/*
			//Set extra data owner object
			objectExtraData->object = light;

			//Create the light
			Light* light = this->sceneManager->createLight(parameters.name);
			if (queryFlags != 0)
				light->setQueryFlags(parameters.queryFlags);
			if (visibilityFlags != 0)
				light->setVisibilityFlags(parameters.visibilityFlags);
			OgreMaxUtilities::SetObjectVisibility(light, parameters.visibility);
			light->setType(OgreMaxUtilities::ParseLightType(parameters.type));
			light->setCastShadows(parameters.castShadows);
			light->setPowerScale(parameters.power);

			light->setDiffuseColour(parameters.diffuseColor);
			light->setSpecularColour(parameters.specularColor);

			light->setPosition(parameters.position);
			light->setSpotlightFalloff(parameters.spotlightFalloff);
			light->setSpotlightInnerAngle(parameters.spotlightInnerAngle);
			light->setSpotlightOuterAngle(parameters.spotlightOuterAngle);
			light->setAttenuation(parameters.attenuationRange, parameters.attenuationConstant, parameters.attenuationLinear, parameters.attenuationQuadric);


			//Attach light to the node
			owner.Attach(light);*/	
		}
        
		virtual void onCamera(OgreMax::Types::CameraParameters) {
//THIS IS THE CODE THAT USED TO BE IN OGREMAX SCENE, THIS CODE SHOULD NOT BE USED HERE BUT IS PLACED HERE FOR LATER
			/*
   //Create the camera
    Camera* camera = this->sceneManager->createCamera(name);
    if (queryFlags != 0)
        camera->setQueryFlags(queryFlags);
    if (visibilityFlags != 0)
        camera->setVisibilityFlags(visibilityFlags);
    OgreMaxUtilities::SetObjectVisibility(camera, visibility);
    camera->setFOVy(Radian(fov));
    camera->setAspectRatio(aspectRatio);
    camera->setProjectionType(OgreMaxUtilities::ParseProjectionType(projectionType));

    camera->setNearClipDistance(nearClip);
    camera->setFarClipDistance(farClip);
	camera->setPosition(paramaters.position);
	camera->setOrientation(paramaters.orientation);
	 camera->setDirection(paramaters.direction);

    //Set extra data owner object
    objectExtraData->object = camera;

    //Attach camera to the node
    owner.Attach(camera);
*/
		}
        
		virtual void onEntity( const OgreMax::Types::EntityParameters& parameters ) {
//THIS IS THE CODE THAT USED TO BE IN OGREMAX SCENE, THIS CODE SHOULD NOT BE USED HERE BUT IS PLACED HERE FOR LATER
/*
//Load the mesh
    bool isNewMesh = !MeshManager::getSingleton().resourceExists(parameters.meshFile);
    MeshPtr mesh = MeshManager::getSingleton().load
        (
        parameters.meshFile,
        parameters.resourceGroupName,
        parameters.vertexBufferUsage, parameters.indexBufferUsage,
        parameters.vertexBufferShadowed, parameters.indexBufferShadowed
        );

    //Notify callback if the mesh was just loaded
    if (isNewMesh && this->callback != 0)
        this->callback->CreatedMesh(this, mesh.getPointer());

    //Create entity
    Entity* entity = this->sceneManager->createEntity(parameters.name, parameters.meshFile);
    if (parameters.queryFlags != 0)
        entity->setQueryFlags(parameters.queryFlags);
    if (parameters.visibilityFlags != 0)
        entity->setVisibilityFlags(parameters.visibilityFlags);
    OgreMaxUtilities::SetObjectVisibility(entity, parameters.visibility);
    entity->setCastShadows(parameters.castShadows);
    entity->setRenderQueueGroup(parameters.renderQueue);
    entity->setRenderingDistance(parameters.renderingDistance);
    OgreMaxUtilities::SetCustomParameters(entity, parameters.customParameters);
    if (!parameters.materialFile.empty())
        entity->setMaterialName(parameters.materialFile);
    objectExtraData->object = entity;

    //Set subentity materials
    size_t subentityCount = std::min(parameters.subentities.size(), (size_t)entity->getNumSubEntities());
    for (size_t subentityIndex = 0; subentityIndex < subentityCount; subentityIndex++)
    {
        SubEntity* subentity = entity->getSubEntity((unsigned int)subentityIndex);
        if (!parameters.subentities[subentityIndex].materialName.empty())
            subentity->setMaterialName(parameters.subentities[subentityIndex].materialName);
    }

    //Attach entity to the owner
    owner.Attach(entity);

    //Load bone attachments
    if (boneAttachmentsElement != 0)
        LoadBoneAttachments(boneAttachmentsElement, entity);

    //Add to loaded objects map
    this->loadedObjects[parameters.name] = entity;

    //Notify callback
    if (this->callback != 0)
        this->callback->CreatedEntity(this, entity);*/
		}
        
		virtual void onParticleSystem(const OgreMaxScene* scene, Ogre::ParticleSystem* particleSystem) {

		}
        
		virtual void onBillboardSet(const OgreMaxScene* scene, Ogre::BillboardSet* billboardSet) {

		}
        
		virtual void onPlane(const OgreMaxScene* scene, const Ogre::Plane& plane, Ogre::Entity* entity) {
		}
        

        /**
         * Called after a scene is loaded.
         * @param success [in] - Indicates whether the scene was successfully loaded. False indicates an error occurred.
         */
        virtual void FinishedLoad(bool success) {}

        //Render texture creation callbacks
        virtual Ogre::Camera* GetRenderTextureCamera(const OgreMaxScene* scene, const OgreMax::Types::RenderTextureParameters& renderTextureParameters) {return 0;}

       // virtual void CreatedRenderTexture(const OgreMaxScene* scene, const OgreMax::Types::LoadedRenderTexture* renderTexture) {}

         // virtual void HandleObjectExtraData(Types::ObjectExtraDataPtr objectExtraData) {}

        //Progress callback
        virtual void UpdatedLoadProgress(const OgreMaxScene* scene, Ogre::Real progress) {}

        /**
         * Notifies the caller that shadow textures are about to be created
         * @param scene [in] - The scene that was loaded
         * @param parameters [in/out] - The shadow parameters that are in effect. Any of the texture-related
         * parameters can be modified. The most typical one to be modified is the texture pixel format.
         */
        //virtual void CreatingShadowTextures(const OgreMaxScene* scene, Types::ShadowParameters& shadowParameters) {}
    };


#endif