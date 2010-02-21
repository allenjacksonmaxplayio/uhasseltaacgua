#include "DummyHovercraftRepresentation.h"

namespace HovUni {

DummyHovercraftRepresentation::DummyHovercraftRepresentation(DummyHovercraft * hovercraft, 
		Ogre::SceneManager * sceneMgr) : EntityRepresentation(hovercraft, "cube.mesh", sceneMgr) {
	// Scale cube to represent a car a little bit more
	// TODO Normally the mesh should speak for itself and these things should not be necessary
	mOgreNode->scale(Ogre::Vector3(1.0, 0.5, 0.5));
}

DummyHovercraftRepresentation::~DummyHovercraftRepresentation(void) {
	// Empty
}

}