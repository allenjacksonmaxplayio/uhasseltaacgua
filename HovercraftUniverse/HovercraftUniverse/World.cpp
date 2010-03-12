#include "World.h"

namespace HovUni {

World * World::ms_world = 0;

World * World::getSingletonPtr(){
	return ms_world;
}

World& World::getSingleton() {
	assert(ms_world);
	return *ms_world;
}

World::World(void):
	mIsLoaded(false){
}

World::~World(void){
}

void World::create(const Ogre::String& map){
	ms_world = new World();
}
	
void World::destroy() {
	delete ms_world;
	ms_world = 0;
}

}