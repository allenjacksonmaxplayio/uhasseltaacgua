#include "StartRepresentation.h"

namespace HovUni {

StartRepresentation::StartRepresentation(Start * entity, Ogre::String mesh, Ogre::SceneManager * sceneMgr) : EntityRepresentation(entity, "EMPTY.mesh",   sceneMgr) {
	// Empty
}

StartRepresentation::~StartRepresentation() {
	// Empty
}

}