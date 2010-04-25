#include "HovercraftRepresentation.h"

#include "Hovercraft.h"
#include <HovSound.h>
#include <SoundManager.h>
#include <OgreParticleSystem.h>
#include <OgreSceneNode.h>

namespace HovUni {

const float HovercraftRepresentation::MAX_RPM = 6000.0f;
const float HovercraftRepresentation::MIN_RPM = 500.0f;

HovercraftRepresentation::HovercraftRepresentation(Hovercraft * entity, Ogre::SceneManager * sceneMgr, Ogre::String meshFile, Ogre::String resourceGroupName, bool visible, bool castShadows, 
												   Ogre::Real renderingDistance, Ogre::String materialFile, std::vector<Ogre::String> subMaterials, Ogre::SceneNode * node) 
			: EntityRepresentation(entity, meshFile,  sceneMgr, resourceGroupName, visible, castShadows, renderingDistance, materialFile, subMaterials, node), Moveable3DEmitter(EVENTGUID_HOVSOUND_EVENTS_HOVERCRAFT) {
   for ( std::vector<Ogre::String>::iterator i = subMaterials.begin(); i != subMaterials.end(); i++ ){
	   std::cout << *i << std::endl;
   }

   //Initialize sound
	setEventParameter(EVENTPARAMETER_HOVSOUND_EVENTS_HOVERCRAFT_RPM, 1000.0f);
	float load_min, load_max;
	getEventParameterRange(EVENTPARAMETER_HOVSOUND_EVENTS_HOVERCRAFT_LOAD, &load_min, &load_max);
    setEventParameter(EVENTPARAMETER_HOVSOUND_EVENTS_HOVERCRAFT_LOAD, load_max);

	//TODO: Don't know if this should be here...
	SoundManager::getSingletonPtr()->registerEmitter(this);
	startSound();

	//TODO: check if we have to delete these things ourselves, or if ogre will take care of that
	// (for example, when starting a new game)
	Ogre::ParticleSystem* pSystem = sceneMgr->createParticleSystem(entity->getName(), "Smokey");
	mParticleNode = node->createChildSceneNode();
	mParticleNode->attachObject(pSystem);

	this->getOgreEntity()->setCastShadows(true);
}

HovercraftRepresentation::~HovercraftRepresentation() {
	
}

void HovercraftRepresentation::getUpdates(Ogre::Vector3 ** position, Ogre::Vector3 ** velocity, Ogre::Vector3 ** orientation) {
	float part = ((Hovercraft*)mEntity)->getSpeed() / ((Hovercraft*)mEntity)->getMaximumSpeed();
	setEventParameter(EVENTPARAMETER_HOVSOUND_EVENTS_HOVERCRAFT_RPM, MIN_RPM + part * MAX_RPM);
	(*position) = &mEntity->getPosition();
	(*velocity) = &mEntity->getVelocity();
	(*orientation) = &mEntity->getOrientation();
}

}