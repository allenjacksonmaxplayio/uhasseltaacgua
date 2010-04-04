#include "EntityPropertySystem.h"
#include "Entity.h"

namespace HovUni {

EntityPropertyMap::EntityPropertyMap( Entity * entity ):
	mEntity(entity){
}

EntityPropertyMap::~EntityPropertyMap(){
	
	//destroy all properties
	for ( PropertyMap::iterator i = mMap.begin(); i != mMap.end(); i++ ){
		delete i->second;
		i->second = 0;
	}
	mMap.clear();
}

bool EntityPropertyMap::addProperty( EntityProperty * property  ){	
	property->mEntity = mEntity;
	
	std::pair<PropertyMap::iterator,bool> r = mMap.insert(Property(property->getProperyType(),property));
	return r.second;
}

bool EntityPropertyMap::hasProperty( const Ogre::String& key ) const {
	return mMap.find(key) != mMap.end();
}

EntityProperty * EntityPropertyMap::getProperty( const Ogre::String& key ){
	PropertyMap::iterator i = mMap.find(key);
	if ( i == mMap.end() ){
		return 0;
	}	
	else {
		return i->second;
	}
}

bool EntityPropertyMap::removeProperty ( const Ogre::String& key, bool del ){

	PropertyMap::iterator i = mMap.find(key);
	if ( i == mMap.end() ){
		return false;
	}	
	else {
		mMap.erase(i);

		if ( del )
			delete i->second;

		return true;
	}
}

bool EntityPropertyMap::removeProperty ( EntityProperty * property, bool del ){
	return removeProperty(property->getProperyType(),del);
}

EntityProperty * EntityPropertyMap::removeProperty ( const Ogre::String& key ){
	PropertyMap::iterator i = mMap.find(key);
	if ( i == mMap.end() ){
		return 0;
	}	
	else {
		EntityProperty * result = i->second;
		mMap.erase(i);
		return result;
	}
}

EntityProperty * EntityPropertyMap::removeProperty ( EntityProperty * property ){
	PropertyMap::iterator i = mMap.find(property->getProperyType());
	if ( i == mMap.end() ){
		return 0;
	}	
	else {
		mMap.erase(i);
		return property;
	}
}

EntityProperty::EntityProperty(const Ogre::String& type):
	mType(type), mEntity(0)
{
}

EntityProperty::~EntityProperty(void)
{
}

Entity * EntityProperty::getEntity(){
	return mEntity;
}

const Ogre::String& EntityProperty::getProperyType() const {
	return mType;
}

}
