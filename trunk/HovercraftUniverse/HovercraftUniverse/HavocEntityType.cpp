#include "HavocEntityType.h"

#include <Common/Base/hkBase.h>
#include <Common/Base/System/hkBaseSystem.h>
#include <Physics/Dynamics/World/hkpWorldObject.h>

namespace HovUni {

//the ID for our property randomly chosen
int HavocEntityType::ENITYTYPEPROPERTY = 15454;

HavocEntityType::Type HavocEntityType::getEntityType( hkpWorldObject * object ){
	//mostly read only field, ignore the MT check
	if ( object->hasProperty(ENITYTYPEPROPERTY) ){
		hkpPropertyValue p = object->getProperty(ENITYTYPEPROPERTY);		
		return (HavocEntityType::Type) p.getInt();
	} else {
		return NOTSET;
	}
}

void HavocEntityType::updateEntityType( hkpWorldObject * object, HavocEntityType::Type type ) {
	hkpPropertyValue p;
	p.setInt((int)type);
	object->editProperty(ENITYTYPEPROPERTY,p);
}

void HavocEntityType::setEntityType( hkpWorldObject * object, HavocEntityType::Type type ) {
	object->unlockPropertiesFromLoadedObject ();
	hkpPropertyValue p;
	p.setInt((int)type);
	object->addProperty(ENITYTYPEPROPERTY,p);	
}

}