#ifndef ENTITYMANAGER_H_
#define ENTITYMANAGER_H_

#include <vector>
#include "Entity.h"

using namespace std;

namespace HovUni {

/**
 * The entity manager contains all entities. They must be added to the entity manager, so that
 * the entity manager can update them at fixed frequencies or can search for them when queried.
 *
 * @author Kristof Overdulve
 */
class EntityManager {
protected:
	/** The entities that have been registered at the manager */
	vector<Entity *> mEntities;

public:
	
	/**
	 * Constructor.
	 */
	EntityManager();

	/**
	 * Destructor.
	 */
	virtual ~EntityManager();

	/**
	 * Register an entity with the entity manager.
	 *
	 * @param entity the entity that ought to be registered with the manager
	 */
	void registerEntity(Entity * entity);

	/**
	 * Releases an entity from the entity manager. TODO IDENTIFIER FOR THE ENTITIES?
	 */
	void releaseEntity();

	/**
	 * Returns the entity from the entity manager. TODO IDENTIFIER FOR THE ENTITIES?
	 *
	 */
	Entity * getEntity();

protected:

	/**
	 * Notify the representation manager of a new entity.
	 *
	 * @param entity the entity that is added to the manager
	 */
	void notifyRepresentationEntityAdded(Entity * entity);

	/**
	 * Notify the representation manager of a released entity.
	 */
	void notifyRepresentationEntityRemoved();

	/**
	 * Updates the entities.
	 */
	void updateEntities();
};

}

#endif /* ENTITYMANAGER_H_ */