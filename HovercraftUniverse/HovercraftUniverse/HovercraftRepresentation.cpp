#include "HovercraftRepresentation.h"

namespace HovUni {

HovercraftRepresentation::HovercraftRepresentation(Hovercraft * entity, Ogre::String mesh, Ogre::SceneManager * sceneMgr) : EntityRepresentation(entity, "EMPTY.mesh",   sceneMgr) {
	// Empty
}

HovercraftRepresentation::~HovercraftRepresentation() {
	// Empty
}

}