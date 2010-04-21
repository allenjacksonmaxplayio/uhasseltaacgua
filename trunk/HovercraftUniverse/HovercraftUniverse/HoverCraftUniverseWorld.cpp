#include "HoverCraftUniverseWorld.h"

#include "ServerLoader.h"
#include "CustomOgreMaxScene.h"

#include "HavokEntityType.h"
#include "PhantomTrackAction.h"

#include "GameEntities.h"

#include "Hovercraft.h"
#include "HavokHovercraft.h"
#include "OgreMaxTypes.hpp"
#include "PlanetGravityPhantom.h"
#include "HavokEntityType.h"
#include "CheckpointPhantom.h"
#include "StartPhantom.h"
#include "SpeedBoostPhantom.h"
#include "FinishPhantom.h"
#include "PortalPhantom.h"
#include "PowerupPhantom.h"


#include <Physics/Collide/Filter/Group/hkpGroupFilterSetup.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>
#include <Physics/Collide/Shape/Convex/Box/hkpBoxShape.h>
#include <Common/Base/Math/Matrix/hkTransform.h>

namespace {

hkpShape * setBox(const Ogre::Vector3& scale) {
	hkVector4 halfex;
	halfex.set(scale[0], scale[1], scale[2]);
	halfex.mul4(5.0f); //10 base scale, divided by 2 for half extend => 5.0
	return new hkpBoxShape(halfex);
}

void setBox(hkAabb& aabb, const Ogre::Vector3& position, const Ogre::Quaternion& rotation, const Ogre::Vector3& scale) {
	aabb.m_max.set(1, 1, 1);
	aabb.m_max.set(-1, -1, -1);

	hkVector4 t(position.x, position.y, position.z);
	hkQuaternion q(rotation.x, rotation.y, rotation.z, rotation.w);

	hkTransform tr(q, t);

	hkVector4 pos1;
	pos1.set(scale.x * 5, scale.y * 5, scale.z * 5);
	pos1.setTransformedPos(tr, pos1);

	hkVector4 pos2;
	pos2.set(scale.x * -5, scale.y * -5, scale.z * -5);
	pos2.setTransformedPos(tr, pos2);

	if (pos1(0) > pos2(0)) {
		aabb.m_max(0) = pos1(0);
		aabb.m_min(0) = pos2(0);
	} else {
		aabb.m_max(0) = pos2(0);
		aabb.m_min(0) = pos1(0);
	}

	if (pos1(1) > pos2(1)) {
		aabb.m_max(1) = pos1(1);
		aabb.m_min(1) = pos2(1);
	} else {
		aabb.m_max(1) = pos2(1);
		aabb.m_min(1) = pos1(1);
	}

	if (pos1(2) > pos2(2)) {
		aabb.m_max(2) = pos1(2);
		aabb.m_min(2) = pos2(2);
	} else {
		aabb.m_max(2) = pos2(2);
		aabb.m_min(2) = pos1(2);
	}
}
}

namespace HovUni {

HoverCraftUniverseWorld::HoverCraftUniverseWorld(hkReal timestep):
	AbstractHavokWorld(timestep)
{
}

HoverCraftUniverseWorld::~HoverCraftUniverseWorld(void)
{
}

void HoverCraftUniverseWorld::createStart( Start * start, OgreMax::Types::ExternalItem& externalitem ){
	mPhysicsWorld->markForWrite();

	//Create a phantom that handles this
	hkAabb aabb;
	setBox(aabb, externalitem.position, externalitem.rotation, externalitem.scale);
	StartPhantom * phantom = new StartPhantom(aabb, start);
	mPhysicsWorld->addPhantom(phantom);
	phantom->removeReference();

	mPhysicsWorld->unmarkForWrite();
}

void HoverCraftUniverseWorld::createFinish( Finish * finish, OgreMax::Types::ExternalItem& externalitem ){
	mPhysicsWorld->markForWrite();

	//Create a phantom that handles this
	hkAabb aabb;
	setBox(aabb, externalitem.position, externalitem.rotation, externalitem.scale);
	FinishPhantom * phantom = new FinishPhantom(aabb, finish);
	mPhysicsWorld->addPhantom(phantom);
	phantom->removeReference();

	mPhysicsWorld->unmarkForWrite();
}

void HoverCraftUniverseWorld::createCheckpoint( CheckPoint * checkpoint, OgreMax::Types::ExternalItem& externalitem ){
	mPhysicsWorld->markForWrite();

	//Create a phantom that handles this
	hkAabb aabb;
	setBox(aabb, externalitem.position, externalitem.rotation, externalitem.scale);
	CheckpointPhantom * checkpointphantom = new CheckpointPhantom(aabb, checkpoint);
	mPhysicsWorld->addPhantom(checkpointphantom);
	checkpointphantom->removeReference();

	mPhysicsWorld->unmarkForWrite();
}

void HoverCraftUniverseWorld::createPortal( Portal * portal, OgreMax::Types::ExternalItem& externalitem ){
	mPhysicsWorld->markForWrite();

	//Create a phantom that handles this
	hkAabb aabb;
	setBox(aabb, externalitem.position, externalitem.rotation, externalitem.scale);
	PortalPhantom * phantom = new PortalPhantom(aabb, portal);
	mPhysicsWorld->addPhantom(phantom);
	phantom->removeReference();

	mPhysicsWorld->unmarkForWrite();
}

void HoverCraftUniverseWorld::createBoost( SpeedBoost * boost, OgreMax::Types::ExternalItem& externalitem ){
	mPhysicsWorld->markForWrite();

	//Create a phantom that handles this
	hkpShape * shape = setBox(externalitem.scale);

	hkQuaternion r;
	r.set(externalitem.rotation.x, externalitem.rotation.y, externalitem.rotation.z, externalitem.rotation.w);

	hkVector4 t;
	t.set(externalitem.position[0], externalitem.position[1], externalitem.position[2]);

	hkTransform tr(r, t);

	SpeedBoostPhantom * phantom = new SpeedBoostPhantom(shape, tr, boost);
	mPhysicsWorld->addPhantom(phantom);
	phantom->removeReference();
	shape->removeReference();

	mPhysicsWorld->unmarkForWrite();
}

void HoverCraftUniverseWorld::createAsteroid( Asteroid * asteroid, OgreMax::Types::ExternalItem& externalitem ){
	mPhysicsWorld->markForWrite();

	//Get the entity name of the asteroid
	Ogre::String entityname = asteroid->getOgreEntity();

	// Find the planet
	hkpRigidBody* planetRigidBody = mPhysicsData->findRigidBodyByName(entityname.c_str());

	if (planetRigidBody == HK_NULL) {
		THROW(ParseException, "No such name found.");
	}

	//Set that it is a planet
	HavokEntityType::setEntityType(planetRigidBody, HavokEntityType::PLANET);

	//add gravity field PULL
	{
		hkAabb currentAabb;
		planetRigidBody->getCollidable()->getShape()->getAabb(planetRigidBody->getTransform(), 0.0f, currentAabb);

		// Scale up the planet's gravity field's AABB so it goes beyond the planet
		hkVector4 extents;
		extents.setSub4(currentAabb.m_max, currentAabb.m_min);
		hkInt32 majorAxis = extents.getMajorAxis();
		hkReal maxExtent = extents(majorAxis);
		maxExtent *= 0.4f;

		// Scale the AABB's extents
		hkVector4 extension;
		extension.setAll(maxExtent);
		currentAabb.m_max.add4(extension);
		currentAabb.m_min.sub4(extension);


		// Attach a gravity phantom to the planet so it can catch objects which come close
		PlanetGravityPhantom* gravityphantom = new PlanetGravityPhantom(asteroid, planetRigidBody, currentAabb);
		mPhysicsWorld->addPhantom(gravityphantom);
		gravityphantom->removeReference();
	}

	mPhysicsWorld->unmarkForWrite();
}



void HoverCraftUniverseWorld::postStep() {
}

void HoverCraftUniverseWorld::preStep() {
	//update characters
	hkStorageStringMap<HavokEntity*>::Iterator i = mCharactersMap.getIterator ();
	while ( mCharactersMap.isValid(i) ){
		HavokEntity * ch = mCharactersMap.getValue(i); 
		ch->update();
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

void HoverCraftUniverseWorld::addHovercraft( Hovercraft * entity, const hkString& hovercraft, const hkString& entityname, const hkVector4& pos ){
	HavokEntity * c = new HavokHovercraft(mPhysicsWorld,entity,hovercraft,entityname);
	c->load(pos);
	mCharactersMap.insert(entity->getName().c_str(),c);
}

}
