#ifndef FINISHREPRESENTATION_H_
#define FINISHREPRESENTATION_H_

#include "EntityRepresentation.h"
#include "Finish.h"

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
		FinishRepresentation(Finish * entity, Ogre::String mesh, Ogre::SceneManager * sceneMgr);

		/**
		 * Destructor.
		 */
		~FinishRepresentation();
	};

}

#endif