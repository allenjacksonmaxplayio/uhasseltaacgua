// Test.cpp : Defines the entry point for the console application.
//

#include "DefaultOgreMaxSceneCallback.h"
#include "CustomOgreMaxScene.h"
#include "Ogre.h"
#include "OgreConfigFile.h"
#include "ExampleFrameListener.h"
using namespace OgreMax;
using namespace Ogre;
using namespace HovUni;

class ExampleApplication
{
public:
    /// Standard constructor
    ExampleApplication()
    {
        mFrameListener = 0;
        mRoot = 0;
		mResourcePath = "./";
        mConfigPath = mResourcePath;
    }
    /// Standard destructor
    virtual ~ExampleApplication()
    {
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
    Root *mRoot;

    Camera* mCamera;

    SceneManager* mSceneMgr;

    ExampleFrameListener* mFrameListener;

    RenderWindow* mWindow;

	Ogre::String mResourcePath;

	Ogre::String mConfigPath;

    // These internal methods package up the stages in the startup process
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

		mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC, "Default");	

		/////////////////////////////////////////////////////

		CustomOgreMaxScene * mScene = new CustomOgreMaxScene();

		HovUni::DefaultOgreMaxSceneCallback callback(mWindow,mSceneMgr);

		//CustomNotifier not;
		mScene->Load("SimpleTrack.scene",OgreMax::OgreMaxScene::NO_OPTIONS,&callback);

		delete mScene;

		/////////////////////////////////////////////////////

		mCamera = mSceneMgr->getCamera("Camera01");
		Ogre::Viewport * vp = mWindow->addViewport(mCamera);

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
         MessageBox( NULL, e.what(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
    }

    return 0;
}

