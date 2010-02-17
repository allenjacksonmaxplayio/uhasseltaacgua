#include "Ogre.h"
#include "OgreConfigFile.h"
#include "ExampleFrameListener.h"
#include "HavocWorldUpdater.h"
using namespace Ogre;

/** Base class which manages the standard startup of an Ogre application.
    Designed to be subclassed for specific examples if required.
*/
class ExampleApplication
{
public:
    /// Standard constructor
    ExampleApplication()
    {
        mFrameListener = 0;
		mHavoc = 0;
        mRoot = 0;
		mResourcePath = "./";
        mConfigPath = mResourcePath;
    }
    /// Standard destructor
    virtual ~ExampleApplication()
    {
		if (mHavoc)
			delete mHavoc;
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
	HavocWorldUpdater * mHavoc;

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


		mSceneMgr = mRoot->createSceneManager(ST_GENERIC, "primary");

		 // create the camera
        mCamera = mSceneMgr->createCamera("PlayerCam");

		// set its position, direction  
        mCamera->setPosition(Vector3(0,10,500));
        mCamera->lookAt(Vector3(0,0,0));

		mCamera->setNearClipDistance(5);

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
		mHavoc = new HavocWorldUpdater();
        mFrameListener= new ExampleFrameListener(mWindow, mCamera);
        mFrameListener->showDebugOverlay(true);
        mRoot->addFrameListener(mFrameListener);
		mRoot->addFrameListener(mHavoc);
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
        //MessageBox( NULL, e.what(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
    }
    return 0;
}