#include "AsteroidRepresentation.h"

namespace HovUni {

AsteroidRepresentation::AsteroidRepresentation(Asteroid * entity, Ogre::String mesh, Ogre::SceneManager * sceneMgr) : EntityRepresentation(entity, "EMPTY.mesh",   sceneMgr) {
	// Empty
}

AsteroidRepresentation::~AsteroidRepresentation() {
	// Empty
}

}