#include "HoverCraftUniverseWorld.h"

#include "ServerLoader.h"
#include "CustomOgreMaxScene.h"

#include "HavokEntityType.h"
#include "PhantomTrackAction.h"

#include "Hovercraft.h"
#include "HavokHovercraft.h"

#include <Physics/Collide/Filter/Group/hkpGroupFilterSetup.h>

namespace HovUni {

HoverCraftUniverseWorld::HoverCraftUniverseWorld(hkReal timestep):
	AbstractHavokWorld(timestep), mStartPositions(0), mPowerupPositions(128), mResetPositions(32)
{
	mStart = HK_NULL;
	mFinish = HK_NULL;

}

HoverCraftUniverseWorld::~HoverCraftUniverseWorld(void)
{
	if ( mStart != HK_NULL ) {
		mStart->removeReference();
	}

	if ( mFinish != HK_NULL ) {
		mFinish->removeReference();
	}

	//TODO
	//delete checkpoints
	//delete characters
	//...
}

void HoverCraftUniverseWorld::postStep() {
	// Rotate the character
	hkStorageStringMap<HavokEntity*>::Iterator i = mCharactersMap.getIterator ();
	while ( mCharactersMap.isValid(i) ){
		HavokEntity * ch = mCharactersMap.getValue(i); 
		ch->postStep();	
		i = mCharactersMap.getNext(i);
	}
}

void HoverCraftUniverseWorld::preStep() {
	//SETUP CHARACTERS

	hkStorageStringMap<HavokEntity*>::Iterator i = mCharactersMap.getIterator ();
	while ( mCharactersMap.isValid(i) ){
		HavokEntity * ch = mCharactersMap.getValue(i); 
		ch->preStep();
		i = mCharactersMap.getNext(i);
	}
}

HavokEntity * HoverCraftUniverseWorld::getCharacter(const char * name) {
	if (name == 0 )
		return HK_NULL;

	HavokEntity * result = HK_NULL;
	mCharactersMap.get(name,&result);
	return result;
}

void HoverCraftUniverseWorld::addHovercraft( Hovercraft * entity, const hkString& hovercraft, const hkString& entityname, int pos ){
	HavokEntity * c = new HavokHovercraft(mPhysicsWorld,entity,hovercraft,entityname);
	c->load(mStartPositions[pos]);
	mCharactersMap.insert(entity->getName().c_str(),c);
}

}
