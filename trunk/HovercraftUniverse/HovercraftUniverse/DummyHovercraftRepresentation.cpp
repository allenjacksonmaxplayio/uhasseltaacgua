#include "DummyHovercraftRepresentation.h"

#include <HovSound.h>
#include <SoundManager.h>

namespace HovUni {

DummyHovercraftRepresentation::DummyHovercraftRepresentation(DummyHovercraft * hovercraft, Ogre::SceneManager * sceneMgr, Ogre::String meshFile, Ogre::String resourceGroupName, 
															 bool visible, bool castShadows, Ogre::Real renderingDistance, Ogre::String materialFile, std::vector<Ogre::String> subMaterials) 
															 : EntityRepresentation(hovercraft, meshFile, sceneMgr, resourceGroupName, visible, castShadows, renderingDistance, materialFile, subMaterials), 
															   Moveable3DEmitter(EVENTGUID_HOVSOUND_EVENTS_HOVERCRAFT) {
	// Scale cube to represent a car a little bit more
	// TODO Normally the mesh should speak for itself and these things should not be necessary
	mOgreNode->scale(Ogre::Vector3(0.005, 0.005, 0.01));

	//Initialize sound
	setEventParameter(EVENTPARAMETER_HOVSOUND_EVENTS_HOVERCRAFT_RPM, 1000.0f);
	float load_min, load_max;
	getEventParameterRange(EVENTPARAMETER_HOVSOUND_EVENTS_HOVERCRAFT_LOAD, &load_min, &load_max);
    setEventParameter(EVENTPARAMETER_HOVSOUND_EVENTS_HOVERCRAFT_LOAD, load_max);

	//TODO: Don't know if this should be here...
	SoundManager::getSingletonPtr()->registerEmitter(this);
	startSound();
	Moveable3DEmitter::update();
}

DummyHovercraftRepresentation::~DummyHovercraftRepresentation(void) {
	// Empty
}

void DummyHovercraftRepresentation::getUpdates(Ogre::Vector3 ** position, Ogre::Vector3 ** velocity, Ogre::Vector3 ** orientation) {
	(*position) = new Ogre::Vector3(getEntity()->getPosition());
	(*velocity) = 0;
	(*orientation) = new Ogre::Vector3(getEntity()->getOrientation());
}

}