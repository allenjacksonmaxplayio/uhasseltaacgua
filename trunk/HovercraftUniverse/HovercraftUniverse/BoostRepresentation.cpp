#include "BoostRepresentation.h"
#include "Boost.h"

namespace HovUni {

BoostRepresentation::BoostRepresentation(Boost * entity, Ogre::String mesh, Ogre::SceneManager * sceneMgr) : EntityRepresentation(entity, "EMPTY.mesh",   sceneMgr) {
	// Empty
}

BoostRepresentation::~BoostRepresentation() {
	// Empty
}

}