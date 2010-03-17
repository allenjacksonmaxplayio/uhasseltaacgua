#include "CheckPointRepresentation.h"

namespace HovUni {

CheckPointRepresentation::CheckPointRepresentation(CheckPoint * entity, Ogre::String mesh, Ogre::SceneManager * sceneMgr) : EntityRepresentation(entity, "CheckPoint0Geom.mesh",   sceneMgr) {
	// Empty
}

CheckPointRepresentation::~CheckPointRepresentation() {
	// Empty
}

}