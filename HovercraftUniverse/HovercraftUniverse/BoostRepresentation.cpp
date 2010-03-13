#include "BoostRepresentation.h"

namespace HovUni {

BoostRepresentation::BoostRepresentation(SpeedBoost * entity, Ogre::String mesh, Ogre::SceneManager * sceneMgr) : EntityRepresentation(entity, "EMPTY.mesh",   sceneMgr) {
	// Empty
}

BoostRepresentation::~BoostRepresentation() {
	// Empty
}

}