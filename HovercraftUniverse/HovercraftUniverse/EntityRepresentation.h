#ifndef ENTITYREPRESENTATION_H_
#define ENTITYREPRESENTATION_H_

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

public:

	/**
	 * Constructor.
	 *
	 * @param entity the entity that this representation visualizes
	 */
	EntityRepresentation(Entity * entity);

	/**
	 * Destructor.
	 */ 
	virtual ~EntityRepresentation();

	/**
	 * Returns the entity that this representation visualizes.
	 *
	 * @return the entity
	 */
	Entity * getEntity() { return mEntity; }

	/**
	 * Draws the representation.
	 */
	void draw();

};

}

#endif