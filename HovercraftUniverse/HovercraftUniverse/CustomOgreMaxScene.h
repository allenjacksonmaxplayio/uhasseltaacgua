#ifndef CUSTOMOGREMAXSCENE_INCLUDED
#define CUSTOMOGREMAXSCENE_INCLUDED

#include "OgreMaxTypes.hpp"
#include "OgreMaxPlatform.hpp"
#include "ProgressCalculator.hpp"
#include "Version.hpp"
#include "CustomOgreMaxSceneCallback.h"

namespace HovUni {

    /**
     * Manages the loading of a OgreMax .scene file.
	 * Use a CustomOgreMaxSceneCallback to set up your scene:
	 * CustomOgreMaxScene scene;
	 * CustomOgreMaxSceneCallback * callback = new MyCallback(someogrepointers);
	 * scene.load(file, OPTIONS, callback);
	 * @author PJ
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
         * @param fileNameOrContent [in] - The name of the file to load.
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
}

#endif
