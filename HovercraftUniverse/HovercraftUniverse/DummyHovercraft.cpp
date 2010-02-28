#include "DummyHovercraft.h"
#include "DummyHovercraftController.h"
#include "DummyHovercraftPlayerController.h"
#include "BasicEntityEvent.h"
#include <OgreLogManager.h>

namespace HovUni {

DummyHovercraft::DummyHovercraft(void) : Entity("hovercraft", "vehicles", true, Ogre::Vector3(0.0, 40.0, 0.0), 
												Ogre::Vector3(0.0, 0.0, -1.0)) {
	// Already initialized
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

}