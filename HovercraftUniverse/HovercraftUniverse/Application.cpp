#include "Application.h"
#include "ApplicationFrameListener.h"
#include "DummyHovercraft.h"
#include "DummyHovercraftRepresentation.h"

namespace HovUni {

Application::Application(void) {
}

Application::~Application(void) {
}

void Application::createCamera(void) {
	// Create camera
	mCamera = mSceneMgr->createCamera("PlayerCam");
	mCamera->setNearClipDistance(5);
}

void Application::createScene(void) {
	// Set ambient light
	mSceneMgr->setAmbientLight(ColourValue(0.25, 0.25, 0.25));
	

	// Create and store entity manager
	mEntityManager = EntityManager::getSingletonPtr();

	// TODO Create and store representation manager
	RepresentationManager::initialise(mEntityManager, mSceneMgr);
	mRepresentationManager = RepresentationManager::getSingletonPtr();

	// TODO Create and store input manager
	mInputManager = InputManager::getSingletonPtr();
	mInputManager->initialise(mWindow);

	// TODO Pass both to framelistener

	// TODO TEMP Create entities
	DummyHovercraft * hovercraft = new DummyHovercraft();
	DummyHovercraftRepresentation * hovercraftRep = new DummyHovercraftRepresentation(hovercraft, 
		mRepresentationManager->getSceneManager());

	mEntityManager->registerEntity(hovercraft);
	mRepresentationManager->addEntityRepresentation(hovercraftRep);

	
	// Cube entity
	Ogre::Entity * ent = mSceneMgr->createEntity("Cube", "cube.mesh");
	SceneNode * node = mSceneMgr->getRootSceneNode()->createChildSceneNode("CubeNode");
	node->translate(Vector3(0.0, 40.0, 0.0), Node::TS_PARENT);
	node->scale(Vector3(1.0, 0.5, 0.5));
	node->attachObject(ent);

	// Plane entity
	Ogre::Plane plane(Vector3::UNIT_Y, 0);
	MeshManager::getSingleton().createPlane("ground", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
		1500, 1500, 20, 20, true, 1, 5.0, 5.0, Vector3::UNIT_Z);
	ent = mSceneMgr->createEntity("GroundEntity", "ground");
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ent);

	// Light 
	Light * light = mSceneMgr->createLight("Light1");
	light->setType(Light::LT_POINT);
	light->setPosition(Vector3(250, 150, 250));
	light->setDiffuseColour(ColourValue::White);
	light->setSpecularColour(ColourValue::White);
	mSceneMgr->getRootSceneNode()->attachObject(light);

	// First camera
	node = mSceneMgr->getRootSceneNode()->createChildSceneNode("CamNode1", Vector3(-400, 200, 400));
	node->yaw(Degree(-45));
	node = node->createChildSceneNode("PitchNode1");
	node->attachObject(mCamera);

	// Second camera
	node = mSceneMgr->getRootSceneNode()->createChildSceneNode("CamNode2", Vector3(0, 200, 400));
	node = node->createChildSceneNode("PitchNode2");
}

void Application::createFrameListener(void) {
	// Create and configure frame listener
	mFrameListener = new ApplicationFrameListener(mWindow, mCamera, mSceneMgr, mEntityManager, 
		mRepresentationManager, mInputManager);
	mRoot->addFrameListener(mFrameListener);
	mFrameListener->showDebugOverlay(true);
}

}