#include "GameView.h"
#include <OgreMeshManager.h>
#include <OgreResourceGroupManager.h>
#include <GUIManager.h>

namespace HovUni {

// Define initial global ID
int GameView::mGlobalID = 1;

GameView::GameView(HUD * hud, Ogre::SceneManager * sceneMgr) : mHUD(hud), mSceneMgr(sceneMgr), mID(mGlobalID++) {
	// Create camera for this game view
	mCamera = mSceneMgr->createCamera("Camera" + mID);
	mCamera->setNearClipDistance(5);

	// Create camera rotation possibilities
	Ogre::SceneNode * node = mSceneMgr->getRootSceneNode()->createChildSceneNode(mCamera->getName() + "Node", 
		Ogre::Vector3(-400, 200, 400));
	node->yaw(Ogre::Degree(-45));
	node = node->createChildSceneNode(mCamera->getName() + "PitchNode");
	node->attachObject(mCamera);

	// TODO PUT IN MORE GENERIC FORMAT
	// Plane entity
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
		plane, 1500, 1500, 20, 20, true, 1, 5.0, 5.0, Ogre::Vector3::UNIT_Z);
	Ogre::Entity * ent = mSceneMgr->createEntity("GroundEntity", "ground");
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ent);

	// Light 
	Ogre::Light * light = mSceneMgr->createLight("Light1");
	light->setType(Ogre::Light::LT_POINT);
	light->setPosition(Ogre::Vector3(250, 150, 250));
	light->setDiffuseColour(Ogre::ColourValue::White);
	light->setSpecularColour(Ogre::ColourValue::White);

	// First camera viewpoint
	//Ogre::SceneNode * node = mSceneMgr->getRootSceneNode()->createChildSceneNode("CamNode1", Ogre::Vector3(-400, 200, 400));
	//node->yaw(Ogre::Degree(-45));
	//node = node->createChildSceneNode("PitchNode1");
	//node->attachObject(mCamera);

	// Second camera viewpoint
	//node = mSceneMgr->getRootSceneNode()->createChildSceneNode("CamNode2", Ogre::Vector3(0, 200, 400));
	//node = node->createChildSceneNode("PitchNode2");
}

GameView::~GameView() {
}

void GameView::addEntityRepresentation(EntityRepresentation * entityRep) {
	// Add to entity representations
	mEntityRepresentations.push_back(entityRep);
}

void GameView::removeEntityRepresentation(Ogre::String entityRep) {
	// Loop through list and remove if found
	for (std::vector<EntityRepresentation *>::const_iterator it = mEntityRepresentations.begin(); 
			it != mEntityRepresentations.end(); it++) {
		if ((*it)->getEntity()->getName() == entityRep) {
			// Erase from entity representations
			mEntityRepresentations.erase(it);
			break;
		}
	}
}

void GameView::draw() {
	//Activate the HUD if needed
	if (!mHUD->isActivated()) {
		mHUD->activate();
	}

	// Draw the entity representations
	drawEntityRepresentations();
	
	// TODO Draw the static objects

	// Draw the hud
	drawHUD();
}

void GameView::drawEntityRepresentations() {
	for (std::vector<EntityRepresentation *>::const_iterator it = mEntityRepresentations.begin(); 
			it != mEntityRepresentations.end(); it++) {
		(*it)->draw();
	}
}

void GameView::drawHUD() {
	//TODO: Make sure this is called once every render frame!
	//		Dont think it should be here?
	GUIManager::getSingletonPtr()->update();
}

}