#include "DummyHovercraft.h"
#include "DummyHovercraftController.h"
#include "DummyHovercraftPlayerController.h"

namespace HovUni {

DummyHovercraft::DummyHovercraft(void) : Entity("hovercraft", "vehicles", Ogre::Vector3(0.0, 40.0, 0.0), 
												Ogre::Vector3(0.0, 0.0, 0.0), new DummyHovercraftPlayerController()) {
	// Already initialized
}

DummyHovercraft::~DummyHovercraft(void) {
	// Empty
}

void DummyHovercraft::processController(Ogre::Real timeSinceLastFrame) {
	// Cast to correct type
	DummyHovercraftController * hovercraftController = dynamic_cast<DummyHovercraftController *>(mController);

	// Process controls
	changePosition(mPosition + hovercraftController->getDirection() * timeSinceLastFrame * 100);
	changeOrientation(mOrientation + hovercraftController->getOrientationChange());
}

}