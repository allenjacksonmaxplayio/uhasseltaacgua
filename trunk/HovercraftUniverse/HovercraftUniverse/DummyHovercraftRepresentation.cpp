#include "DummyHovercraftRepresentation.h"

#include <HovSound.h>
#include <SoundManager.h>

namespace HovUni {

DummyHovercraftRepresentation::DummyHovercraftRepresentation(DummyHovercraft * hovercraft, 
		Ogre::SceneManager * sceneMgr) : EntityRepresentation(hovercraft, "cube.mesh", sceneMgr), Moveable3DEmitter(EVENTGUID_HOVSOUND_EVENTS_HOVERCRAFT) {
	// Scale cube to represent a car a little bit more
	// TODO Normally the mesh should speak for itself and these things should not be necessary
	mOgreNode->scale(Ogre::Vector3(0.5, 0.5, 1.0));

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
	(*orientation) = 0;
}

}