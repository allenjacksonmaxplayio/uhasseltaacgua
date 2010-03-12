#ifndef TRACKREPRESENTATION_H_
#define TRACKREPRESENTATION_H_

#include "EntityRepresentation.h"
#include "Track.h"

namespace HovUni {

	/**
	 * Representation of a track entity.
	 *
	 * @author Kristof Overdulve
	 */
	class TrackRepresentation : public EntityRepresentation
	{
	public:
		/**
		 * Constructor.
		 */
		TrackRepresentation(Track * entity, Ogre::String mesh, Ogre::SceneManager * sceneMgr);

		/**
		 * Destructor.
		 */
		~TrackRepresentation();
	};

}

#endif