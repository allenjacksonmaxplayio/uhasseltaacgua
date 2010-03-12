#ifndef CHECKPOINTREPRESENTATION_H_
#define CHECKPOINTREPRESENTATION_H_

#include "EntityRepresentation.h"
#include "CheckPoint.h"

namespace HovUni {

	/**
	 * Representation of a checkpoint entity.
	 *
	 * @author Kristof Overdulve
	 */
	class CheckPointRepresentation : public EntityRepresentation
	{
	public:
		/**
		 * Constructor.
		 */
		CheckPointRepresentation(CheckPoint * entity, Ogre::String mesh, Ogre::SceneManager * sceneMgr);

		/**
		 * Destructor.
		 */
		~CheckPointRepresentation();
	};

}

#endif