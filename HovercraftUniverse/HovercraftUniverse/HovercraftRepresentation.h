#ifndef HOVERCRAFTREPRESENTATION_H_
#define HOVERCRAFTREPRESENTATION_H_

#include "EntityRepresentation.h"
#include "Hovercraft.h"
#include <vector>

namespace HovUni {

	/**
	 * Representation of a hovercraft entity.
	 *
	 * @author Kristof Overdulve
	 */
	class HovercraftRepresentation : public EntityRepresentation
	{
	public:
		/**
		 * Constructor.
		 */
		HovercraftRepresentation(Hovercraft * entity, Ogre::SceneManager * sceneMgr, Ogre::String meshFile, Ogre::String resourceGroupName, bool visible, bool castShadows, 
			Ogre::Real renderingDistance, Ogre::String materialFile, std::vector<Ogre::String> subMaterials);

		/**
		 * Destructor.
		 */
		~HovercraftRepresentation();
	};

}

#endif