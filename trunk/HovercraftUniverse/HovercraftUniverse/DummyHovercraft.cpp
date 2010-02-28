#include "DummyHovercraft.h"
#include "DummyHovercraftController.h"
#include "DummyHovercraftPlayerController.h"
#include "BasicEntityEvent.h"
#include <OgreLogManager.h>
#include <HovSound.h>
#include <SoundManager.h>

namespace HovUni {

DummyHovercraft::DummyHovercraft(void) : Entity("hovercraft", "vehicles", true, Ogre::Vector3(0.0, 40.0, 0.0), 
												Ogre::Vector3(0.0, 0.0, -1.0)), Moveable3DEmitter(EVENTGUID_HOVSOUND_EVENTS_HOVERCRAFT) {
	// Already initialized
	startSound();
	setEventParameter(EVENTPARAMETER_HOVSOUND_EVENTS_HOVERCRAFT_RPM, 1000.0f);
	float load_min, load_max;
	getEventParameterRange(EVENTPARAMETER_HOVSOUND_EVENTS_HOVERCRAFT_LOAD, &load_min, &load_max);
    setEventParameter(EVENTPARAMETER_HOVSOUND_EVENTS_HOVERCRAFT_LOAD, load_max);

	//I could make this automatic for all emitters...
	//SoundManager::getSingletonPtr()->registerEmitter(this);
}

DummyHovercraft::~DummyHovercraft(void) {
	// Empty
}

void DummyHovercraft::processControllerEventsInServer(ControllerEvent* event) {
	// Just forward for now
	sendEvent(*event);
}

void DummyHovercraft::processControllerEventsInOwner(ControllerEvent* event) {
	processEventsOwnerAndOther(event);
}

void DummyHovercraft::processControllerEventsInOther(ControllerEvent* event) {
	processEventsOwnerAndOther(event);
}

void DummyHovercraft::processEventsOwnerAndOther(ControllerEvent* event) {
	switch (event->getType()) {
		case BasicEntity:
			{
				BasicEntityEvent* e = dynamic_cast<BasicEntityEvent*>(event);

				// Process controls
				changePosition(mPosition + e->getDirection() * e->getTimeSinceLastFrame() * 100);
				changeOrientation(mOrientation + e->getOrientationChange());

				Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "Added " << e->getDirection();
				Ogre::LogManager::getSingleton().getDefaultLog()->stream() << "Updated position: " << getPosition() << " " << getOrientation() << "\n";
				break;
			}
		default:
			break;
	}
}


void DummyHovercraft::getUpdates(Ogre::Vector3 ** position, Ogre::Vector3 ** velocity, Ogre::Vector3 ** orientation) {
	(*position) = new Ogre::Vector3(getPosition());
	(*velocity) = 0;
	(*orientation) = 0;
}

}