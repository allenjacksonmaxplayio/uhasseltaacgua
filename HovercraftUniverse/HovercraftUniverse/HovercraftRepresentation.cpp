#include "HovercraftRepresentation.h"

namespace HovUni {

HovercraftRepresentation::HovercraftRepresentation(Hovercraft * entity, Ogre::SceneManager * sceneMgr, Ogre::String meshFile, Ogre::String resourceGroupName, bool visible, bool castShadows, 
												   Ogre::Real renderingDistance, Ogre::String materialFile, std::vector<Ogre::String> subMaterials, Ogre::SceneNode * node) 
			: EntityRepresentation(entity, meshFile,  sceneMgr, resourceGroupName, visible, castShadows, renderingDistance, materialFile, subMaterials, node) {
	// Empty

   for ( std::vector<Ogre::String>::iterator i = subMaterials.begin(); i != subMaterials.end(); i++ ){
	   std::cout << *i << std::endl;
   }
}

HovercraftRepresentation::~HovercraftRepresentation() {
	// Empty
}

}