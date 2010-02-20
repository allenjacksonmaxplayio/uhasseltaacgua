#include "EntityManager.h" 

namespace HovUni {

EntityManager::EntityManager() {
}

EntityManager::~EntityManager() {
}

void EntityManager::registerEntity(Entity * entity) {
	// Check for existence
	if (getEntity(entity->getName())) {
		// TODO Throw exception, already exists
	}

	// Add to entities and new entities
	mEntities.push_back(entity);
	mNewEntities.push_back(entity);
}

void EntityManager::releaseEntity(Ogre::String entityName) {
	// Check for existence
	for (std::vector<Entity *>::const_iterator it = mEntities.begin(); it != mEntities.end(); it++) {
		if ((*it)->getName() == entityName) {
			mEntities.erase(it);
			break;
		}
	}

	// TODO Throw exception, does not exist
}

Entity * EntityManager::getEntity(Ogre::String entityName) {
	// Search entity
	for (std::vector<Entity *>::const_iterator it = mEntities.begin(); it != mEntities.end(); it++) {
		if ((*it)->getName() == entityName) {
			// Return entity
			return (*it);
		}
	}

	// No such entity found, return 0
	return 0;
}

std::vector<Entity *> EntityManager::getEntities(Ogre::String categoryName) {
	std::vector<Entity *> results;

	// Search entities 
	for (std::vector<Entity *>::const_iterator it = mEntities.begin(); it != mEntities.end(); it++) {
		if ((*it)->getCategory() == categoryName) {
			// Add entity to list
			results.push_back(*it);
		}
	}

	// Return found list
	return results;
}

std::vector<Entity *> EntityManager::getNewEntities() { 
	std::vector<Entity *> entitiesToReturn = mNewEntities;
	mNewEntities.clear();

	return entitiesToReturn;
}

std::vector<Entity *> EntityManager::getRemovedEntities() { 
	std::vector<Entity *> entitiesToReturn = mRemovedEntities;
	mRemovedEntities.clear();

	return entitiesToReturn;
}

void EntityManager::updateEntities(Ogre::Real timeSinceLastFrame) {
	// Loop over entities and update them
	for (std::vector<Entity *>::const_iterator it = mEntities.begin(); it != mEntities.end(); it++) {
		(*it)->update(timeSinceLastFrame);
	}
}

EntityManager * EntityManager::getSingletonPtr(void) {
	if (!mEntityManager) {
		mEntityManager = new EntityManager();
	}

	return mEntityManager;
}

}