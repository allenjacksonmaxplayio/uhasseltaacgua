#include "EntityRepresentation.h"
#include <OgreMaxUtilities.hpp>
#include <OgreSubEntity.h>
#include <vector>
#include <iostream>

namespace HovUni {

EntityRepresentation::EntityRepresentation(Entity * entity, Ogre::String meshFile, Ogre::SceneManager * sceneMgr, Ogre::String resourceGroupName, bool visible, bool castShadows, 
										   Ogre::Real renderingDistance, Ogre::String materialFile, std::vector<Ogre::String> subMaterials)  :  mEntity(entity), mSceneMgr(sceneMgr) {
	// Create entity 
	mOgreEntity = mSceneMgr->createEntity(entity->getName(), meshFile, resourceGroupName);
	OgreMax::OgreMaxUtilities::SetObjectVisibility(mOgreEntity, visible ? OgreMax::Types::OBJECT_VISIBLE : OgreMax::Types::OBJECT_HIDDEN);
	mOgreEntity->setCastShadows(castShadows);
	mOgreEntity->setRenderingDistance(renderingDistance);
	if (!materialFile.empty()) {
		mOgreEntity->setMaterialName(materialFile);
	}

	// Set subentity materials
	for (unsigned int i = 0; i < subMaterials.size(); i++) {
		Ogre::SubEntity * subentity = mOgreEntity->getSubEntity(i);
		subentity->setMaterialName(subMaterials[i]);
	}

	// Create node and attach entity to it
	mOgreNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(entity->getName() + "Node");
	mOgreNode->attachObject(mOgreEntity);
}

EntityRepresentation::~EntityRepresentation() {
	// Empty
}

void EntityRepresentation::draw() {
	// Update the settings
	
	std::cout << mEntity->getName() << " " << mEntity->getCategory() << " " << mEntity->getPosition() << std::endl;

	mOgreNode->setPosition(mEntity->getPosition());
	mOgreNode->setOrientation(mEntity->getQuaternion());
}

}