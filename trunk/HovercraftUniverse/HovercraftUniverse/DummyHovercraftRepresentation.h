#ifndef DUMMYHOVERCRAFTREPRESENTATION_H_
#define DUMMYHOVERCRAFTREPRESENTATION_H_

#include "EntityRepresentation.h"
#include "DummyHovercraft.h"

#include <Moveable3DEmitter.h>

namespace HovUni {

/**
 * A dummy hovercraft representation.
 *
 * @author Kristof Overdulve
 */
	class DummyHovercraftRepresentation : public EntityRepresentation, public Moveable3DEmitter {
public:

	/**
	 * Constructor.
	 *
	 * @param hovercraft the hovercraft entity that this representation represents
	 * @param sceneMgr the Ogre scene manager
	 */
	DummyHovercraftRepresentation(DummyHovercraft * hovercraft, Ogre::SceneManager * sceneMgr);

	/**
	 * Destructor.
	 */
	~DummyHovercraftRepresentation(void);

	/**
	 * See Moveable3DEmitter for details
	 */
	void getUpdates(Ogre::Vector3 ** position, Ogre::Vector3 ** velocity, Ogre::Vector3 ** orientation);
};

}

#endif