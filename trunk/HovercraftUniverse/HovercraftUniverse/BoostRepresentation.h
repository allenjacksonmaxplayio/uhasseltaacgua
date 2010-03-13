#ifndef BOOSTREPRESENTATION_H_
#define BOOSTREPRESENTATION_H_

#include "EntityRepresentation.h"
#include "SpeedBoost.h"

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
		BoostRepresentation(SpeedBoost * entity, Ogre::String mesh, Ogre::SceneManager * sceneMgr);

		/**
		 * Destructor.
		 */
		~BoostRepresentation();
	};

}

#endif