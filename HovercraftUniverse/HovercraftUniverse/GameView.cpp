#include "GameView.h"
#include <OgreMeshManager.h>
#include <OgreResourceGroupManager.h>

namespace HovUni {

// Define initial global ID
int GameView::mGlobalID = 1;

GameView::GameView(Ogre::SceneManager * sceneMgr) : mHUD(0), mSceneMgr(sceneMgr), mID(mGlobalID++) {
	// Create camera for this game view
	mRaceCam = new RaceCamera(mSceneMgr, mID);

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

void GameView::draw(Ogre::Real timeSinceLastFrame) {
	// Update the camera
	mRaceCam->update(timeSinceLastFrame);

	//Activate the HUD if needed
	if (mHUD) {
		if (!mHUD->isActivated()) {
			mHUD->activate();
		}
	}

	// Draw the entity representations
	drawEntityRepresentations();
	
	// TODO Draw the static objects

	// Draw the hud
	drawHUD();
}

void GameView::setHud(HUD* hud) {
	mHUD = hud;
}

void GameView::drawEntityRepresentations() {
	for (std::vector<EntityRepresentation *>::const_iterator it = mEntityRepresentations.begin(); 
			it != mEntityRepresentations.end(); it++) {
		(*it)->draw();
	}
}

void GameView::drawHUD() {

}

}