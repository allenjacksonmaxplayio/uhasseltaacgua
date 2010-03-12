#include "PortalRepresentation.h"

namespace HovUni {

PortalRepresentation::PortalRepresentation(Portal * entity, Ogre::String mesh, Ogre::SceneManager * sceneMgr) : EntityRepresentation(entity, "EMPTY.mesh",   sceneMgr) {
	// Empty
}

PortalRepresentation::~PortalRepresentation() {
	// Empty
}

}