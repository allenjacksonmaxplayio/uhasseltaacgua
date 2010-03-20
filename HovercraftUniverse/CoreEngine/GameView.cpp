#include "GameView.h"
#include <OgreMeshManager.h>
#include <OgreResourceGroupManager.h>
#include "EntityManager.h"

namespace HovUni {

// Define initial global ID
int GameView::mGlobalID = 1;

GameView::GameView(Ogre::SceneManager * sceneMgr) : mHUD(0), mSceneMgr(sceneMgr), mID(mGlobalID++) {
	// Create camera for this game view
	mRaceCam = new RaceCamera(mSceneMgr, mID);

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
	updateHUD();
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

void GameView::updateHUD() {
	//Update hud objects to new values

	//Current entity
	Entity* currEnt = EntityManager::getClientSingletonPtr()->getTrackedEntity();

	if (currEnt != 0) {
		mHUD->updateDirection(currEnt->getOrientation(), (Ogre::Vector3(2, 0, 0) - currEnt->getPosition()), Ogre::Vector3(0.0f, 1.0f, 0.0f));
	}
}

}