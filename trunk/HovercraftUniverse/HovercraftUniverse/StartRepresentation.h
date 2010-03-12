#ifndef STARTREPRESENTATION_H_
#define STARTREPRESENTATION_H_

#include "EntityRepresentation.h"
#include "Start.h"

namespace HovUni {

	/**
	 * Representation of a start entity.
	 *
	 * @author Kristof Overdulve
	 */
	class StartRepresentation : public EntityRepresentation
	{
	public:
		/**
		 * Constructor.
		 */
		StartRepresentation(Start * entity, Ogre::String mesh, Ogre::SceneManager * sceneMgr);

		/**
		 * Destructor.
		 */
		~StartRepresentation();
	};

}

#endif