#ifndef ASTEROIDREPRESENTATION_H_
#define ASTEROIDREPRESENTATION_H_

#include "EntityRepresentation.h"
#include "Asteroid.h"

namespace HovUni {

	/**
	 * Representation of an asteroid entity.
	 *
	 * @author Kristof Overdulve
	 */
	class AsteroidRepresentation : public EntityRepresentation
	{
	public:
		/**
		 * Constructor.
		 */
		AsteroidRepresentation(Asteroid * entity, Ogre::String mesh, Ogre::SceneManager * sceneMgr);

		/**
		 * Destructor.
		 */
		~AsteroidRepresentation(void);
	};

}

#endif