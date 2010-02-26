#include "Application.h"
#include "ApplicationFrameListener.h"
#include "DummyHovercraft.h"
#include "DummyHovercraftPlayerController.h"
#include "DummyHovercraftRepresentation.h"
#include "HUD.h"

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
	msSceneMgr = mOgreRoot->createSceneManager(Ogre::ST_GENERIC, "Default");
	// TODO Create a Camera manager that creates cameras for each gameview, then add this on the fly
	//		to the viewports
	Ogre::Camera * cam = msSceneMgr->createCamera("Camera");
	cam->setNearClipDistance(5);
	Ogre::Viewport * vp = mOgreRoot->getAutoCreatedWindow()->addViewport(cam);

	// TODO Put somewhere else
	Ogre::SceneNode * node = msSceneMgr->getRootSceneNode()->createChildSceneNode("CamNode", Ogre::Vector3(-400, 200, 400));
	node->yaw(Ogre::Degree(-45));
	node = node->createChildSceneNode("PitchNode");
	node->attachObject(cam);

	// TODO Do the operations below belong here or as in separated methods
	// Set ambient light
	msSceneMgr->setAmbientLight(Ogre::ColourValue(0.25, 0.25, 0.25));
	
	// Initialise and store the GUIManager
	GUIManager::init("..\\..\\Media\\GUI", vp);
	mGUIManager = GUIManager::getSingletonPtr();

	// Create and store entity manager
	mEntityManager = EntityManager::getSingletonPtr();

	// Create and store representation manager
	RepresentationManager::initialise(mEntityManager, msSceneMgr);
	mRepresentationManager = RepresentationManager::getSingletonPtr();

	// Add single game view to representation manager
	// TODO Script or import from 3DS Max which and how many game views to have
	mRepresentationManager->addGameView(new GameView(new HUD(), msSceneMgr));

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