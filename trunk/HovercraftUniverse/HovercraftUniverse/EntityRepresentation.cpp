#include "EntityRepresentation.h"

namespace HovUni {

EntityRepresentation::EntityRepresentation(Entity * entity, Ogre::String mesh, Ogre::SceneManager * sceneMgr) 
			:  mEntity(entity), mMesh(mesh), mSceneMgr(sceneMgr) {
	// Create entity and scene node
	mOgreEntity = mSceneMgr->createEntity(entity->getName(), mMesh);
	mOgreNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(entity->getName() + "Node");
	mOgreNode->attachObject(mOgreEntity);
}

EntityRepresentation::~EntityRepresentation() {
	// Empty
}

void EntityRepresentation::draw() {
	// Update the settings
	mOgreNode->setPosition(mEntity->getPosition());
	mOgreNode->setOrientation(mEntity->getQuaternion());
}

}