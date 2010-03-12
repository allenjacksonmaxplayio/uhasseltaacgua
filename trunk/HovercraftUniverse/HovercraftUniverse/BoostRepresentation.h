#ifndef BOOSTREPRESENTATION_H_
#define BOOSTREPRESENTATION_H_

#include "EntityRepresentation.h"
#include "Boost.h"

namespace HovUni {

	/**
	 * Representation of a boost entity.
	 *
	 * @author Kristof Overdulve
	 */
	class BoostRepresentation : public EntityRepresentation
	{
	public:
		/**
		 * Constructor.
		 */
		BoostRepresentation(Boost * entity, Ogre::String mesh, Ogre::SceneManager * sceneMgr);

		/**
		 * Destructor.
		 */
		~BoostRepresentation();
	};

}

#endif