/*
 * This code is based on code from www.ogremax.com 
 */


#ifndef CUSTOMOGREMAXSCENE_INCLUDED
#define CUSTOMOGREMAXSCENE_INCLUDED


//Includes---------------------------------------------------------------------
#include "OgreMaxTypes.hpp"
#include "OgreMaxPlatform.hpp"
#include "ProgressCalculator.hpp"
#include "Version.hpp"

namespace OgreMax {

namespace Types {

enum AttachableType {
	NODE,
	ENTITY
};

/**
 * Container for an attachables
 */
struct Attachable {
	AttachableType type;
	Ogre::String name;

	virtual ~Attachable(){};
};

/**
 * SceneNode: (Ogre::SceneNode)
 */
struct SceneNode : Attachable {
	SceneNode(){
		type = NODE;
	}
};

/**
 * Tagpoint (Ogre::TagePoint)
 * attached to an entity (ex. point at hand for holding gun)
 */
struct TagPoint : Attachable {
	TagPoint(){
		type = ENTITY;
	}

	Ogre::String tagName;
	Ogre::String boneName;
	Ogre::Vector3 attachPosition;
	Ogre::Quaternion attachRotation;
	Ogre::Vector3 attachScale;
};



/**
 * A Keyframe
 */
struct KeyFrame {
	Ogre::Real keyTime;
	Ogre::Real keyframe;
	Ogre::Vector3 translation;
	Ogre::Quaternion rotation;
	Ogre::Vector3 scale;
};

struct NodeAnimation {
	NodeAnimationParameters parameters;
	std::vector<KeyFrame> animationTrack;
};


/**
 * A Billboard
 */
struct Billboard {
    Ogre::Real width;
    Ogre::Real height;
    Ogre::Radian rotationAngle;

    Ogre::Vector3 position;
    Ogre::ColourValue color;
    Ogre::FloatRect texCoordRectangle;
};

}
}

namespace HovUni {

    class CustomOgreMaxSceneCallback;

    /**
     * Manages the loading of a OgreMax .scene file.
     */
    class CustomOgreMaxScene
    {

    public:
        CustomOgreMaxScene();

		virtual ~CustomOgreMaxScene();

        /**
         * Options that may be passed to Load()
         */
        typedef int LoadOptions;
        enum
        {
            NO_OPTIONS = 0,

            /** Skips the environment settings in the file. Skipping the environment also skips shadows */
            SKIP_ENVIRONMENT = 0x1,

            /** Skips the shadow settings in the file */
            SKIP_SHADOWS = 0x2,

            /** Skips the sky settings in the file */
            SKIP_SKY = 0x4,

            /** Skips the nodes in the file */
            SKIP_NODES = 0x8,

            /** Skips the externals in the file */
            SKIP_EXTERNALS = 0x10,

            /** Skips the terrain in the file */
            SKIP_TERRAIN = 0x20,

            /** Skips scene level query flags in the file */
            SKIP_QUERY_FLAG_ALIASES = 0x200,

            /** Skips scene level visibility flags in the file */
            SKIP_VISIBILITY_FLAG_ALIASES = 0x400,

            /** Skips scene level resource locations in the file */
            SKIP_RESOURCE_LOCATIONS = 0x800,

            /** Indicates animation states should not be created for node animation tracks */
            NO_ANIMATION_STATES = 0x1000,

            /**
             * Indicates scene 'externals' should not be stored. They will, however, still
             * be loaded and the CreatedExternal() scene callback will be called
             */
            NO_EXTERNALS = 0x2000,

            /**
             * By default, the OgreMaxScene::Load() checks to see if the file that was passed
             * in exists in the file system (outside of the configured resource locations).
             * This flag disables that logic
             */
            NO_FILE_SYSTEM_CHECK = 0x4000,

            /**
             * Indicates that a light should be created if the loaded scene doesn't contain a light
             * Any lights created as a result of setting the default lighting are not passed to
             * the scene callback
             */
            SET_DEFAULT_LIGHTING = 0x8000,

            /**
             * Indicates that the 'fileNameOrContent' parameter in Load() should be treated as the
             * scene XML. In other words, no file is loaded from Ogre's file system.
             */
            FILE_NAME_CONTAINS_CONTENT = 0x10000
        };


        /** Flags that define which name prefixes to set */
        typedef int WhichNamePrefix;
        enum
        {
            OBJECT_NAME_PREFIX = 0x1,
            NODE_NAME_PREFIX = 0x2,
            NODE_ANIMATION_NAME_PREFIX = 0x4,
            ALL_NAME_PREFIXES = OBJECT_NAME_PREFIX | NODE_NAME_PREFIX | NODE_ANIMATION_NAME_PREFIX
        };

        /**
         * Loads a scene from the specified file.
         * @param fileNameOrContent [in] - The name of the file to load. This file name can contain a directory path
         * or be a base name that exists within Ogre's resource manager. If the file contains a directory path,
         * the directory will be added to Ogre's resource manager as a resource location and the directory will be
         * set as a base resource location. If the file doesn't contain a directory path, and assuming
         * If the FILE_NAME_CONTAINS_CONTENT flag is specified as a load option, this parameter is treated
         * as though it is the scene file itself. That is, the string contains the scene file XML.
         * SetBaseResourceLocation() hasn't already been called elsewhere, no resource location configuration
         * will occur during the load
         * @param loadOptions [in] - Options used to specify the loading behavior. Optional.
		 * @param callback [in] - Pointer to a callback object. Optional.
         * @param defaultResourceGroupName [in] - The resource group name that is used by default when
         * creating new resources. Optional.
         */
        void Load ( const Ogre::String& fileNameOrContent, LoadOptions loadOptions = NO_OPTIONS, CustomOgreMaxSceneCallback * callback = 0,
            const Ogre::String& defaultResourceGroupName = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME
            );

        /**
         * Sets one or more name prefixes. This should be called before Load() is called
         * @param name [in] - The prefix. This may be null
         * @param prefixes [in] - Flags indicating which prefixes to set
         */
        void SetNamePrefix(const Ogre::String& name, WhichNamePrefix prefixes = ALL_NAME_PREFIXES);

        /** 
		 * Gets the base resource location 
		 */
        const Ogre::String& GetBaseResourceLocation() const;

        /**
         * Sets the base resource location, a directory, which all other resource locations
         * are considered to be relative to.
         * @param directory [in] - The base directory. If this is an empty string, resource
         * locations loaded from the scene file are not added to the Ogre resource group manager
         */
        void SetBaseResourceLocation(const Ogre::String& directory);

		/** 
		 * Gets the up axis vector 
		 */
        const Ogre::Vector3& GetUpVector() const;

    protected:
        /**
         * Loads a scene from the specified XML element
         * @param objectElement [in] - The 'scene' XML element
         */
        void Load ( TiXmlElement* objectElement, LoadOptions loadOptions = NO_OPTIONS, CustomOgreMaxSceneCallback * callback = 0, const Ogre::String& defaultResourceGroupName = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME );

        /**
         * Determines the name of an object stored in an XML element
         * @return If the XML element contains the 'name' attribute, that attribute's value is returned.
         */
        Ogre::String GetNewObjectName(const TiXmlElement* objectElement);

		void LoadObjectNames(const TiXmlElement* objectElement, const Ogre::String& elementName, std::vector<Ogre::String>& names);

        /** Updates the progress for the specified progress calculator. */
		void UpdateLoadProgress(OgreMax::ProgressCalculator* calculator, Ogre::Real amount);

        void LoadScene(const TiXmlElement* objectElement);
        
		//Load Resource DONE
        void LoadResourceLocations(const TiXmlElement* objectElement);

		//Node DONE
        void LoadNodes(const TiXmlElement* objectElement);
		void LoadNode(const TiXmlElement* objectElement, OgreMax::Types::NodeParameters * parent);

		//Load Entity DONE
        void LoadEntity(const TiXmlElement* objectElement, OgreMax::Types::Attachable * parent);
		void LoadBoneAttachments(const TiXmlElement* objectElement, OgreMax::Types::EntityParameters * entity);
        void LoadBoneAttachment(const TiXmlElement* objectElement, OgreMax::Types::EntityParameters * entity);

		//Load Light DONE
		void LoadLight(const TiXmlElement* objectElement, OgreMax::Types::Attachable * parent);
		void LoadLightRange(const TiXmlElement* objectElement, OgreMax::Types::LightParameters& light);
        void LoadLightAttenuation(const TiXmlElement* objectElement, OgreMax::Types::LightParameters& light);

		//Load Camera DONE
		void LoadCamera(const TiXmlElement* objectElement, OgreMax::Types::Attachable * parent);

		//Load ParticleSystem DONE
        void LoadParticleSystem(const TiXmlElement* objectElement, OgreMax::Types::Attachable * parent);
        
		//Load Plane DONE
        void LoadPlane(const TiXmlElement* objectElement, OgreMax::Types::Attachable * parent);
        
		//Bilboards DONE
		void LoadBillboardSet(const TiXmlElement* objectElement, OgreMax::Types::Attachable * parent);
		void LoadBillboard(const TiXmlElement* objectElement, std::vector<OgreMax::Types::Billboard>& billboardset);

		//animation DONE
		std::vector<OgreMax::Types::NodeAnimation> LoadNodeAnimations(const TiXmlElement* objectElement);
        OgreMax::Types::NodeAnimation LoadNodeAnimation(const TiXmlElement* objectElement);
		void LoadNodeAnimationKeyFrame(const TiXmlElement* objectElement, std::vector<OgreMax::Types::KeyFrame>& animationTrack);

		//External DONE
        void LoadExternals(const TiXmlElement* objectElement);
        void LoadExternalUserDatas(const TiXmlElement* objectElement);
		void LoadExternalItem(const TiXmlElement* objectElement );
		void LoadExternalUserData(const TiXmlElement* objectElement, OgreMax::Types::ExternalUserData& userData);

		//Enviroment DONE
        void LoadEnvironment(const TiXmlElement* objectElement);        		
        void LoadFog(const TiXmlElement* objectElement);
        void LoadSkyBox(const TiXmlElement* objectElement);
        void LoadSkyDome(const TiXmlElement* objectElement);
        void LoadSkyPlane(const TiXmlElement* objectElement);
        void LoadClipping(const TiXmlElement* objectElement, Ogre::Real& nearClip, Ogre::Real& farClip);
        void LoadShadows(const TiXmlElement* objectElement);

		//Render Textures TODO
		void LoadRenderTextures(const TiXmlElement* objectElement);
        void FinishLoadingRenderTextures();
		void GetRenderTextureObjects(OgreMax::Types::LoadedRenderTexture* loadedRenderTexture);
		void LoadRenderTextureMaterials ( const TiXmlElement* childElement, std::vector<OgreMax::Types::RenderTextureParameters::Material>& materials );

		//Terrain TODO
		void LoadTerrain(const TiXmlElement* objectElement);

		//void LoadLookTarget(const TiXmlElement* objectElement, Ogre::SceneNode* node, Ogre::Camera* camera);
        //void LoadTrackTarget(const TiXmlElement* objectElement, Ogre::SceneNode* node, Ogre::Camera* camera);

		/*
        void LoadInstancedGeometries(const TiXmlElement* objectElement);
        void LoadInstancedGeometry(const TiXmlElement* objectElement);
        void LoadInstancedGeometryEntity(const TiXmlElement* objectElement );
        void LoadStaticGeometries(const TiXmlElement* objectElement);
        void LoadStaticGeometry(const TiXmlElement* objectElement);
        void LoadStaticGeometryEntity(const TiXmlElement* objectElement);
		*/

		//Load Flags TODO
		void LoadQueryFlagAliases(const TiXmlElement* objectElement);
        void LoadVisibilityFlagAliases(const TiXmlElement* objectElement);

		Ogre::String CustomOgreMaxScene::getUniqueName();
  
    protected:
        LoadOptions loadOptions;

        CustomOgreMaxSceneCallback* callback;

		OgreMax::Types::UpAxis upAxis;

        Ogre::String defaultResourceGroupName;

        Ogre::String baseResourceLocation;

        bool loadedFromFileSystem;

        /** Tracks scene loading progress. */
		class LoadSceneProgressCalculator : public OgreMax::ProgressCalculator
        {
        public:
            LoadSceneProgressCalculator()
            {
                this->nodes = AddCalculator("nodes");
            }

        public:
            //Child calculators
            ProgressCalculator* nodes;
        };
        LoadSceneProgressCalculator loadProgress;

         //Various name prefixes
        Ogre::String objectNamePrefix;
        Ogre::String nodeNamePrefix;
        Ogre::String nodeAnimationNamePrefix;

		int mUniqueID;
    };

    /** A interface that receives notifications during the loading of the scene */
    class CustomOgreMaxSceneCallback
    {
    public:
        /**
		 * Destructor
		 */
		virtual ~CustomOgreMaxSceneCallback() {
		}

		/**
		 * Called when the scene file was found
		 * @param filename
		 * @param resourcegroupname
		 */
		virtual void onSceneFile( const Ogre::String& fileName, Ogre::String& resourceGroupName) = 0;

		/** 
		 * Called before a scene is to be loaded. 
		 * At this stage the xml has been parsed successfuly and is placed in memory.
		 */
        virtual void StartedLoad() = 0;

		/**
		 * When resource location loaded
		 * @param name
		 * @param type
		 * @param recursive
		 */
		virtual void onResourceLocation ( const Ogre::String& name, const Ogre::String& type, bool recursive) = 0;

		/**
		 * Called when al node info is loaded but before any child node is attached
		 * @param nodeparameters
		 * @param nodeanimation, 0 if no animation
		 * @param parent, 0 if rootnode
		 */
		virtual void onNode( OgreMax::Types::NodeParameters& nodeparameters, std::vector<OgreMax::Types::NodeAnimation> * nodeanimation, const OgreMax::Types::NodeParameters* parent) = 0;

		/**
		 * Called when info is found for the root node
		 * @param
		 */
		virtual void onRootNode ( const Ogre::Vector3& position, const Ogre::Quaternion& rotation, const Ogre::Vector3& scale ) = 0;

		virtual void onExternalUserData( OgreMax::Types::ExternalUserData& externalud)= 0;

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
		virtual void onSceneData( const OgreMax::Version& formatVersion, const OgreMax::Version& minOgreVersion, const OgreMax::Version& ogreMaxVersion, const Ogre::String& author, const Ogre::String& application, OgreMax::Types::UpAxis upAxis, Ogre::Real unitsPerMeter, const Ogre::String& unitType) = 0;

        /**
		 * Called when scene user data is loaded. Will only be called if there is user data
		 * @param userdataref
		 * @param userdata
		 */
        virtual void onSceneUserData(const Ogre::String& userDataReference, const Ogre::String& userData) = 0;

		/**
		 * Called when clipping info is loaded
		 * @param environmentNear, near clipping distance
		 * @param environmentFar, far clipping distance
		 */
		virtual void onClipping( Ogre::Real environmentNear, Ogre::Real environmentFar) = 0;

		/**
		 * Called when general shadow properties are loaded
		 * @param shadowparameters
		 */
		virtual void onShadowProperties( OgreMax::Types::ShadowParameters& shadowparameters ) = 0;

		/**
		 * Called when the genereal background color of the viewports are loaded
		 * @param colour
		 */
		virtual void onBackgroundColour( const Ogre::ColourValue& colour ) = 0;

		/**
		 * Called when the world ambient lightning color is loaded
		 * @param colour
		 */
		virtual void onAmbientColour( const Ogre::ColourValue& colour ) = 0;

		/**
		 * Called when the general fog is loaded 
		 * @param fogparameters
		 */
		virtual void onFog ( OgreMax::Types::FogParameters& fogparameters ) = 0;

		/**
		 * Called when the skybox is loaded
		 * @param skyBoxParameters
		 * @param animation, 0 if not defined
		 */
		virtual void onSkyBox( OgreMax::Types::SkyBoxParameters& skyBoxParameters, std::vector<OgreMax::Types::NodeAnimation> * animation ) = 0;

		/**
		 * Called when the skydome is loaded
		 * @param skyDomeParameters
		 * @param animation, 0 if not defined
		 */
        virtual void onSkyDome( OgreMax::Types::SkyDomeParameters& skyDomeParameters, std::vector<OgreMax::Types::NodeAnimation>* animation) = 0;

		/**
		 * Called when the skyplane is loaded
		 * @param skyPlaneParameters
		 * @param animation, 0 if not defined
		 */
        virtual void onSkyPlane( OgreMax::Types::SkyPlaneParameters& skyPlaneParameters, std::vector<OgreMax::Types::NodeAnimation> * animation) = 0;

		/**
		 * Called when external item is loaded
		 * @param externalitem
		 */
		virtual void onExternal( OgreMax::Types::ExternalItem& externalitem) = 0;

		/**
		 * Called when a light is loaded
		 * @param lightparameters
		 * @param parent, 0 if rootnode
		 */
		virtual void onLight( OgreMax::Types::LightParameters& lightparameters, const OgreMax::Types::Attachable * parent ) = 0;
        
		/**
		 * Called when a camera is loaded
		 * @param cameraparameters
		 * @param parent, 0 if rootnode
		 */
		virtual void onCamera(OgreMax::Types::CameraParameters& params, const OgreMax::Types::Attachable * parent ) = 0;
        
		/**
		 * Called when an ogre entity is loaded
		 * @param entityparameters
		 * @param parent
		 */
		virtual void onEntity( OgreMax::Types::EntityParameters& entityparameters, const OgreMax::Types::Attachable * parent ) = 0;
        
		/**
		 * Called when a particle system is loaded
		 * @param particleSystem
		 * @param parent
		 */
		virtual void onParticleSystem( OgreMax::Types::ParticleSystemParameters& particleSystem, const OgreMax::Types::Attachable * parent) = 0;
        
		/**
		 * Called when a billboardset is loaded
		 * @param bilboardsetparameters
		 * @param billboardset
		 * @param custom data for each billboard
		 * @param parent
		 */
		virtual void onBillboardSet( OgreMax::Types::BillboardSetParameters& bilboardsetparameters, std::vector<OgreMax::Types::Billboard>& billboardset, std::vector<OgreMax::Types::CustomParameter>& customParameters, const OgreMax::Types::Attachable * parent ) = 0;
        
		/**
		 * Called when a plane is loaded
		 * @param planeparameters
		 * @param parent
		 */
		virtual void onPlane( OgreMax::Types::PlaneParameters planeparameters, const OgreMax::Types::Attachable * parent) = 0;

        /**
         * Called after a scene is loaded.
         */
        virtual void FinishedLoad( bool success ) = 0;

 	    /** 
		 * Called when Progress is made
		 * @param progress
		 */
        virtual void UpdatedLoadProgress( Ogre::Real progress ) = 0;

    };

}

#endif
