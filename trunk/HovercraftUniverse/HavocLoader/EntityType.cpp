#include "EntityType.h"

#include <Common/Base/hkBase.h>
#include <Common/Base/System/hkBaseSystem.h>
#include <Physics/Dynamics/World/hkpWorldObject.h>

namespace HovUni {

//the ID for our property randomly chosen
int EntityType::ENITYTYPEPROPERTY = 15454;

EntityType::Type EntityType::getEntityType( hkpWorldObject * object ){
	//mostly read only field, ignore the MT check
	if ( object->hasProperty(ENITYTYPEPROPERTY) ){
		hkpPropertyValue p = object->getProperty(ENITYTYPEPROPERTY);		
		return (EntityType::Type) p.getInt();
	} else {
		return NOTSET;
	}
}

void EntityType::updateEntityType( hkpWorldObject * object, EntityType::Type type ) {
	hkpPropertyValue p;
	p.setInt((int)type);
	object->editProperty(ENITYTYPEPROPERTY,p);
}

void EntityType::setEntityType( hkpWorldObject * object, EntityType::Type type ) {
	hkpPropertyValue p;
	p.setInt((int)type);
	object->addProperty(ENITYTYPEPROPERTY,p);	
}

}