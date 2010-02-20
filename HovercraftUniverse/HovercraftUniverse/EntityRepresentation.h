#ifndef ENTITYREPRESENTATION_H_
#define ENTITYREPRESENTATION_H_

#include "Entity.h"
#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>

namespace HovUni {

// Forward declaration of entity due to circular include
class Entity;

/**
 * The entity representation is responsible for visualizing the entity and all of its 
 * effects. It manages 3D models, particles, decals, screen filters, sound, and so on.
 * It can look at, but cannot change the state of the entity.
 *
 * @author Kristof Overdulve
 */
class EntityRepresentation {
protected:

	/** The entity to which this representation applies */
	Entity * mEntity;

	/** The mesh to draw when presenting the representation */
	Ogre::String mMesh;

	/** The Ogre scene manager */
	Ogre::SceneManager * mSceneMgr;

	/** The Ogre graphical entity */
	Ogre::Entity * mOgreEntity;

	/** The scene node to draw and update */
	Ogre::SceneNode * mOgreNode;

public:

	/**
	 * Constructor.
	 *
	 * @param entity the entity that this representation visualizes
	 * @param mesh the mesh that this entity must draw
	 * @param sceneMgr the Ogre scene manager
	 */
	EntityRepresentation(Entity * entity, Ogre::String mesh, Ogre::SceneManager * sceneMgr);

	/**
	 * Destructor.
	 */ 
	virtual ~EntityRepresentation();

	/**
	 * Draws the representation.
	 */
	void draw();

	/**
	 * Returns the entity that this representation visualizes.
	 *
	 * @return the entity
	 */
	Entity * getEntity() { return mEntity; }

	/**
	 * Returns the Ogre entity associated with this representation.
	 *
	 * @return the Ogre entity
	 */
	Ogre::Entity * getOgreEntity() { return mOgreEntity; }

	/**
	 * Returns the Ogre scene node associated with this representation.
	 *
	 * @return the Ogre scene node
	 */
	Ogre::SceneNode * getOgreSceneNode() { return mOgreNode; }

};

}

#endif