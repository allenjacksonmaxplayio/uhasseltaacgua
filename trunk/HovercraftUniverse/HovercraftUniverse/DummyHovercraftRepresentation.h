#ifndef DUMMYHOVERCRAFTREPRESENTATION_H_
#define DUMMYHOVERCRAFTREPRESENTATION_H_

#include "EntityRepresentation.h"
#include "DummyHovercraft.h"

namespace HovUni {

/**
 * A dummy hovercraft representation.
 *
 * @author Kristof Overdulve
 */
	class DummyHovercraftRepresentation : public EntityRepresentation {
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
};

}

#endif