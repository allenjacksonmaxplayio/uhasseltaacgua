#ifndef FINISHREPRESENTATION_H_
#define FINISHREPRESENTATION_H_

#include "EntityRepresentation.h"
#include "Finish.h"
#include <vector>

namespace HovUni {

	/**
	 * Representation of a finish entity.
	 *
	 * @author Kristof Overdulve
	 */
	class FinishRepresentation : public EntityRepresentation
	{
	public:
		/**
		 * Constructor.
		 */
		FinishRepresentation(Finish * entity, Ogre::SceneManager * sceneMgr, Ogre::String meshFile, Ogre::String resourceGroupName, bool visible, bool castShadows, 
			Ogre::Real renderingDistance, Ogre::String materialFile, std::vector<Ogre::String> subMaterials);

		/**
		 * Destructor.
		 */
		~FinishRepresentation();
	};

}

#endif