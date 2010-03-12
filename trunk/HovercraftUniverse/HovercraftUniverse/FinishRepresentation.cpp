#include "FinishRepresentation.h"

namespace HovUni {

FinishRepresentation::FinishRepresentation(Finish * entity, Ogre::String mesh, Ogre::SceneManager * sceneMgr) : EntityRepresentation(entity, "EMPTY.mesh",   sceneMgr) {
	// Empty
}

FinishRepresentation::~FinishRepresentation() {
	// Empty
}

}