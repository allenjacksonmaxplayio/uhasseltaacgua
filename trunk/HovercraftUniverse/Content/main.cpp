// Test.cpp : Defines the entry point for the console application.
//

#include "OgreMaxScene.hpp"
using namespace OgreMax;

#include "Ogre.h"
#include "OgreConfigFile.h"
#include "ExampleFrameListener.h"
// Static plugins declaration section
// Note that every entry in here adds an extra header / library dependency

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE || OGRE_PLATFORM == OGRE_PLATFORM_IPHONE
#   include "macUtils.h"
#endif

using namespace Ogre;


class CustomNotifier : public OgreMax::OgreMaxSceneCallback {

protected:
	
	TiXmlDocument doc;

public:

virtual void LoadingEntity(const OgreMaxScene* scene, OgreMax::Types::EntityParameters& parameters) {
	
	Ogre::Entity * ent = (Ogre::Entity*)parameters.extraData->object;

	if ( parameters.extraData->HasUserData() ){	
		printf("%s",parameters.extraData->userData.c_str());		
		
		/**
		 * Here comes the xml data of the object
		 */
		doc.Parse(parameters.extraData->userData.c_str());

		TiXmlElement * root = doc.RootElement();

		//print the name of the userdata class
		printf("%s",root->GetText());

		//do lookup in some database of userclasses and set up the data (=> pass the root of the xml file)
	
		//link the node to the extra data and other way arround => check volgende members van Movable eens:
		/*
		virtual void 	setUserAny (const Any &anything)
		virtual const Any & 	getUserAny (void) const
		UserObjectBindings & 	getUserObjectBindings ()
 		Return an instance of user objects binding associated with this class. 
		const UserObjectBindings & 	getUserObjectBindings () const
 		Return an instance of user objects binding associated with this class. 
		*/
	}
}

};

/** Base class which manages the standard startup of an Ogre application.
    Designed to be subclassed for specific examples if required.
*/
class ExampleApplication
{
public:
    /// Standard constructor
    ExampleApplication()
    {
		mScene = 0;
        mFrameListener = 0;
        mRoot = 0;
		// Provide a nice cross platform solution for locating the configuration files
		// On windows files are searched for in the current working directory, on OS X however
		// you must provide the full path, the helper function macBundlePath does this for us.
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
		mResourcePath = macBundlePath() + "/Contents/Resources/";
        mConfigPath = mResourcePath;
#else
		mResourcePath = "./";
        mConfigPath = mResourcePath;
#endif
    }
    /// Standard destructor
    virtual ~ExampleApplication()
    {
		if (mScene)
			delete mScene;
        if (mFrameListener)
            delete mFrameListener;
        if (mRoot)
            OGRE_DELETE mRoot;
    }

    /// Start the example
    virtual void go(void)
    {
        if (!setup())
            return;

        mRoot->startRendering();
    }

protected:
	OgreMaxScene * mScene;

    Root *mRoot;

    Camera* mCamera;

    SceneManager* mSceneMgr;

    ExampleFrameListener* mFrameListener;

    RenderWindow* mWindow;

	Ogre::String mResourcePath;

	Ogre::String mConfigPath;

    // These internal methods package up the stages in the startup process
    /** Sets up the application - returns false if the user chooses to abandon configuration. */
    virtual bool setup(void)
    {

		String pluginsPath = mConfigPath;
		// only use plugins.cfg if not static
		
        mRoot = OGRE_NEW Root(pluginsPath + "plugins.cfg", mConfigPath + "ogre.cfg", mResourcePath + "Ogre.log");
        setupResources();

        bool carryOn = configure();
        if (!carryOn) 
			return false;

		// Load resources
		loadResources();

		mScene = new OgreMaxScene();

		CustomNotifier not;

		mScene->Load("uglycube.scene",mWindow,OgreMax::OgreMaxScene::NO_OPTIONS,0,0,&not);
		
		mSceneMgr = mScene->GetSceneManager();
		mCamera = mSceneMgr->getCamera("Camera01");

		// Create one viewport, entire window
        Viewport* vp = mWindow->addViewport(mCamera);
        vp->setBackgroundColour(ColourValue(0,0,0));

        // Alter the camera aspect ratio to match the viewport
        mCamera->setAspectRatio(
            Real(vp->getActualWidth()) / Real(vp->getActualHeight()));


        // Set default mipmap level (NB some APIs ignore this)
        TextureManager::getSingleton().setDefaultNumMipmaps(5);

		// Create any resource listeners (for loading screens)
		createResourceListener();


        createFrameListener();

        return true;

    }

    /** Configures the application - returns false if the user chooses to abandon configuration. */
    virtual bool configure(void)
    {
        // Show the configuration dialog and initialise the system
        // You can skip this and use root.restoreConfig() to load configuration
        // settings if you were sure there are valid ones saved in ogre.cfg
        if(mRoot->showConfigDialog())
        {
            // If returned true, user clicked OK so initialise
            // Here we choose to let the system create a default rendering window by passing 'true'
            mWindow = mRoot->initialise(true);
            return true;
        }
        else
        {
            return false;
        }
    }

    virtual void createFrameListener(void)
    {
        mFrameListener= new ExampleFrameListener(mWindow, mCamera);
        mFrameListener->showDebugOverlay(true);
        mRoot->addFrameListener(mFrameListener);
    }

    /// Method which will define the source of resources (other than current folder)
    virtual void setupResources(void)
    {
        // Load resource paths from config file
        ConfigFile cf;
        cf.load(mResourcePath + "resources.cfg");

        // Go through all sections & settings in the file
        ConfigFile::SectionIterator seci = cf.getSectionIterator();

        String secName, typeName, archName;
        while (seci.hasMoreElements())
        {
            secName = seci.peekNextKey();
            ConfigFile::SettingsMultiMap *settings = seci.getNext();
            ConfigFile::SettingsMultiMap::iterator i;
            for (i = settings->begin(); i != settings->end(); ++i)
            {
                typeName = i->first;
                archName = i->second;
                ResourceGroupManager::getSingleton().addResourceLocation(
                    archName, typeName, secName);

            }
        }
    }

	/// Optional override method where you can create resource listeners (e.g. for loading screens)
	virtual void createResourceListener(void)
	{
	}

	/// Optional override method where you can perform resource group loading
	/// Must at least do ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	virtual void loadResources(void)
	{
		// Initialise, parse scripts etc
		ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	}

};

#define WIN32_LEAN_AND_MEAN
#include "windows.h"

INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
{
    // Create application object
    ExampleApplication app;
    try {
        app.go();
    } catch( Exception& e ) {
        fprintf(stderr, "An exception has occurred: %s\n",
                e.what());
    }

    return 0;
}

