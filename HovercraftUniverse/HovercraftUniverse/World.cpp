#include "World.h"

namespace HovUni {

World * World::ms_world = 0;

WorldLoader::WorldLoader( World * world ):
	mWorld(world)
{
}

WorldLoader::~WorldLoader(){
}

World * World::getSingletonPtr(){
	return ms_world;
}

World& World::getSingleton() {
	assert(ms_world);
	return *ms_world;
}

World::World(void):
	mIsLoaded(false)
{
}

World::~World(void)
{
}

void World::create(const Ogre::String& map, WorldLoader * loader){
	ms_world = new World();
	ms_world->load(map,loader);
}
	
void World::destroy() {
	ms_world->unload();
	delete ms_world;
	ms_world = 0;
}

void World::load( const Ogre::String& map, WorldLoader * loader ) {
	mIsLoaded = true;

	//SET UP LOADER

	//HAVOC
}

void World::unload() {
	mIsLoaded = false;

	//UNLOAD WORLD


	//STOP HAVOC

}

}