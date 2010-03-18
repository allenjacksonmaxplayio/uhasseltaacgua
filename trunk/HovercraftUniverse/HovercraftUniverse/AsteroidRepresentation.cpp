#include "AsteroidRepresentation.h"

namespace HovUni {

AsteroidRepresentation::AsteroidRepresentation(Asteroid * entity, Ogre::SceneManager * sceneMgr, Ogre::String meshFile, Ogre::String resourceGroupName, bool visible, bool castShadows, 
											   Ogre::Real renderingDistance, Ogre::String materialFile, std::vector<Ogre::String> subMaterials) 
											   : EntityRepresentation(entity, meshFile, sceneMgr, resourceGroupName, visible, castShadows, renderingDistance, materialFile, subMaterials) {
	// Empty
}

AsteroidRepresentation::~AsteroidRepresentation() {
	// Empty
}

}