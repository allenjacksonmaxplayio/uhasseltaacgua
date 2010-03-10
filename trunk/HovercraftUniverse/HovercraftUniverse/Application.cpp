#include "Application.h"
#include "ApplicationFrameListener.h"
#include "Exception.h"
#include "HUD.h"
#include "INIReader/INIReader.h"
#include <HovSound.h>
#include <tinyxml/tinyxml.h>
#include <iostream>


namespace HovUni {

Ogre::SceneManager* Application::msSceneMgr = 0;

Application::Application(void) {
}

Application::~Application(void) {

}

void Application::go() {
	parseIni();
	createRoot();
	defineResources();
	setupRenderSystem();
	createRenderWindow();
	initializeResourceGroups();
	setupInputSystem();
	setupScene();
	createFrameListener();
	startRenderLoop();
}

void Application::parseIni() {
	//TCHAR szDirectory[MAX_PATH] = "";
	//GetCurrentDirectory(sizeof(szDirectory) - 1, szDirectory);
	//std::string curDir (szDirectory);
	INIReader reader("HovercraftUniverse.ini");
	if (reader.ParseError() < 0) {
        cerr << "Error reading INI!";
    }
	//Get(section, name, defaultValue)
	mDataPath = reader.Get("Paths", "DataPath", "./data");
	mLogPath = reader.Get("Ogre", "LogFile", "Client.log");
	mOgreConfig = reader.Get("Ogre", "Resources", "resources.cfg");
	mOgrePlugins = reader.Get("Ogre", "Plugins", "plugins.cfg");

	//WARNING! Sets the current directory to the Data Folder, relative to current PWD.
	DWORD  retval=0;
	TCHAR  buffer[MAX_PATH]=TEXT(""); 
    TCHAR** lppPart={NULL};
	GetFullPathName(mDataPath.c_str(),MAX_PATH,buffer,lppPart);
	std::cout << "Changing Working Dir to " << buffer << std::endl;
	BOOL success = SetCurrentDirectory(buffer);

//	char absolutePath[MAX_PATH];
//	std::realpath("../../", absolutePath);
//	SetCurrentDirectory(absolutePath);
}

void Application::createRoot() {
	mOgreRoot = new Ogre::Root("plugins_debug.cfg", "ogre.cfg", mLogPath);
	std::cout << "Creating log at " << mLogPath << std::endl;
}

void Application::defineResources() {
	// Load config
	Ogre::ConfigFile cf;
	cf.load("resources.cfg");

	// Iterate over config
	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
	while (seci.hasMoreElements()) {
		// Read property
		Ogre::String secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap * settings = seci.getNext();
		
		// For all settings of that property, add them
		for (Ogre::ConfigFile::SettingsMultiMap::iterator it = settings->begin(); it != settings->end(); it++) {
			Ogre::String typeName = it->first;
			Ogre::String archName = it->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
		}
	}
}

void Application::setupRenderSystem() {
	if (!mOgreRoot->restoreConfig() && !mOgreRoot->showConfigDialog()) {
		// TODO Throw exception
	}
}

void Application::createRenderWindow() {
	mOgreRoot->initialise(true, "Hovercraft Universe"); //Make this configurable? Maybe that doesn't make much sense... (Dirk)
}

void Application::initializeResourceGroups() {
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void Application::setupScene() {
	// Create scene manager
	msSceneMgr = mOgreRoot->createSceneManager(Ogre::ST_GENERIC, "Default");

	// Get created window
	Ogre::RenderWindow * win = mOgreRoot->getAutoCreatedWindow();

	// TODO Do the operations below belong here or as in separated methods
	// Set ambient light
	msSceneMgr->setAmbientLight(Ogre::ColourValue(0.25, 0.25, 0.25));

	// Create and store entity manager
	mEntityManager = EntityManager::getClientSingletonPtr();

	// Create and store representation manager
	RepresentationManager::initialise(mEntityManager, msSceneMgr);
	mRepresentationManager = RepresentationManager::getSingletonPtr();

	//Get the GUI config file
	//Load and parse the config
	TiXmlDocument doc("gui/GUIConfig.xml");
	doc.LoadFile();

	TiXmlElement* root = doc.RootElement();

	// Add single game view to representation manager
	GameView * gv = new GameView(msSceneMgr);
	Ogre::Viewport * vp = win->addViewport(gv->getCamera()->getCamera());
	mRepresentationManager->addGameView(gv);

	// Initialise and store the GUIManager
	GUIManager::init(root->Attribute("mediaPath"), vp);
	mGUIManager = GUIManager::getSingletonPtr();

	//Set a HUD onto the GameView
	gv->setHud(new HUD(root->FirstChildElement("HUD")));

	// Initialise and store the SoundManager (dont remove trailing \)
	SoundManager::init("sound\\", "HovSound.fev");
	mSoundManager = SoundManager::getSingletonPtr();

	//Start music
	mSoundManager->startAmbient(MUSICCUE_HOVSOUND_BACKGROUND_NORMAL);
	mSoundManager->updateListenerPosition(new Ogre::Vector3(-10.0f, 40.0f, 0.0f));

	// Client
	mClient = new ClientCore("localhost");
}

void Application::setupInputSystem() {
	mInputManager = InputManager::getSingletonPtr();
	mInputManager->initialise(mOgreRoot->getAutoCreatedWindow());
}

void Application::createFrameListener() {
	mFrameListener = new ApplicationFrameListener(mOgreRoot->getSceneManager("Default"), mEntityManager, mRepresentationManager, 
		mInputManager, mClient);
	mOgreRoot->addFrameListener(mFrameListener);
}

void Application::startRenderLoop() {
	mOgreRoot->startRendering();
}

}