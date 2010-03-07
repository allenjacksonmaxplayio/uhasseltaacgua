#include "Application.h"
#include "ApplicationFrameListener.h"
#include "Exception.h"
#include "HUD.h"
#include <HovSound.h>
#include <tinyxml/tinyxml.h>


namespace HovUni {

Ogre::SceneManager* Application::msSceneMgr = 0;

Application::Application(void) {
}

Application::~Application(void) {

}

void Application::go() {
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

void Application::createRoot() {
	mOgreRoot = new Ogre::Root();
	Ogre::LogManager::getSingleton().createLog("Client.log", true);

	//Test exception
	/*
	try {
		THROW(NetworkException, "Test exception");
	} catch (NetworkException e) {
		Ogre::LogManager::getSingleton().getDefaultLog()->stream() << e;
	}
	*/
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
	mOgreRoot->initialise(true, "Hovercraft Universe");
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
	TiXmlDocument doc("..\\GUIConfig.xml");
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
	SoundManager::init("..\\..\\Media\\HovSound\\", "HovSound.fev");
	mSoundManager = SoundManager::getSingletonPtr();

	//Start music
	mSoundManager->startAmbient(MUSICCUE_HOVSOUND_BACKGROUND_NORMAL);
	mSoundManager->updateListenerPosition(new Ogre::Vector3(-10.0f, 40.0f, 0.0f));

	// Server
	mServer = new ServerCore();

	// Client
	mClient = new ClientCore();
}

void Application::setupInputSystem() {
	mInputManager = InputManager::getSingletonPtr();
	mInputManager->initialise(mOgreRoot->getAutoCreatedWindow());
}

void Application::createFrameListener() {
	mFrameListener = new ApplicationFrameListener(mOgreRoot->getSceneManager("Default"), mEntityManager, mRepresentationManager, 
		mInputManager, mServer, mClient);
	mOgreRoot->addFrameListener(mFrameListener);
}

void Application::startRenderLoop() {
	mOgreRoot->startRendering();
}

}