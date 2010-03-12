#include "CheckPointRepresentation.h"

namespace HovUni {

CheckPointRepresentation::CheckPointRepresentation(CheckPoint * entity, Ogre::String mesh, Ogre::SceneManager * sceneMgr) : EntityRepresentation(entity, "EMPTY.mesh",   sceneMgr) {
	// Empty
}

CheckPointRepresentation::~CheckPointRepresentation() {
	// Empty
}

}