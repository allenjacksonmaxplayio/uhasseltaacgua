#include "EntityManager.h" 

namespace HovUni {

EntityManager::EntityManager() {
}

EntityManager::~EntityManager() {
}

void EntityManager::registerEntity(Entity * entity) {
	// TODO Check for existence
	// TODO Register with representation manager
	// TODO Add to list
}

void EntityManager::releaseEntity() {
	// TODO Check for existence
	// TODO Release from representation manager
	// TODO Remove from list
}

Entity * EntityManager::getEntity() {
	// TODO Search entity
	// TODO Return entity

	return 0;
}

void EntityManager::notifyRepresentationEntityAdded(Entity * entity) {
	// TODO Notify
}

void EntityManager::notifyRepresentationEntityRemoved() {
	// TODO Notify
}

void EntityManager::updateEntities() {
	// TODO Loop over entities and update them
}

}