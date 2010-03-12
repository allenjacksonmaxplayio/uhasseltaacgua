#ifndef PORTALREPRESENTATION_H_
#define PORTALREPRESENTATION_H_

#include "EntityRepresentation.h"
#include "Portal.h"

namespace HovUni {

	/**
	 * Representation of a portal entity.
	 *
	 * @author Kristof Overdulve
	 */
	class PortalRepresentation : public EntityRepresentation
	{
	public:
		/**
		 * Constructor.
		 */
		PortalRepresentation(Portal * entity, Ogre::String mesh, Ogre::SceneManager * sceneMgr);

		/**
		 * Destructor.
		 */
		~PortalRepresentation();
	};

}

#endif