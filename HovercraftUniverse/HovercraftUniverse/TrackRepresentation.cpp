#include "TrackRepresentation.h"

namespace HovUni {

TrackRepresentation::TrackRepresentation(Track * entity, Ogre::String mesh, Ogre::SceneManager * sceneMgr) : EntityRepresentation(entity, "EMPTY.mesh",   sceneMgr) {
	// Empty
}

TrackRepresentation::~TrackRepresentation() {
	// Empty
}

}