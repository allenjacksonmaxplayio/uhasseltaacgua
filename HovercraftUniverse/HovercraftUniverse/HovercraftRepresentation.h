#ifndef HOVERCRAFTREPRESENTATION_H_
#define HOVERCRAFTREPRESENTATION_H_

#include "EntityRepresentation.h"
#include "Hovercraft.h"

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
		HovercraftRepresentation(Hovercraft * entity, Ogre::String mesh, Ogre::SceneManager * sceneMgr);

		/**
		 * Destructor.
		 */
		~HovercraftRepresentation();
	};

}

#endif